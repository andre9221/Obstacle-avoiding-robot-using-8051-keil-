// C Code Determining Robot’s Ranges of Movements to be uploaded in keil for
// 8051
// contect in git-andre9221 for the full connection details.

#include <reg52.h>

// --- Pin Definitions ---
sbit IN1 = P1 ^ 0; // Left Motor Fwd
sbit IN2 = P1 ^ 1; // Left Motor Rev
sbit IN3 = P1 ^ 2; // Right Motor Fwd
sbit IN4 = P1 ^ 3; // Right Motor Rev

sbit TRIG = P2 ^ 0;
sbit ECHO = P2 ^ 1;
sbit IR_L = P2 ^ 2;
sbit IR_R = P2 ^ 3;

// --- Global State Variables ---
char bt_cmd = 's';
bit autonomous = 0;

// --- Function Prototypes ---
void serial_init(void);
void delay_ms(unsigned int ms);
unsigned int get_ultrasonic_distance(void);
void robot_MOVE_FORWARD(void);
void robot_MOVE_BACKWARD(void);
void robot_TURN_LEFT(void);
void robot_TURN_RIGHT(void);
void robot_STOP(void);
void robot_PIVOT_BACK_LEFT(void);
void robot_PIVOT_BACK_RIGHT(void);
void handle_obstacle(void);
bit is_left_blocked(void);
bit is_right_blocked(void);

// --- Motor Functions (FIXED FOR REVERSED LEFT MOTOR) ---

// BOTH wheels forward
void robot_MOVE_FORWARD() {
  // Left Motor is reversed
  IN1 = 0;
  IN2 = 1; // Left Fwd
  // Right Motor is correct
  IN3 = 1;
  IN4 = 0; // Right Fwd
}
// BOTH wheels reverse
void robot_MOVE_BACKWARD() {
  // Left Motor is reversed
  IN1 = 1;
  IN2 = 0; // Left Rev
  // Right Motor is correct
  IN3 = 0;
  IN4 = 1; // Right Rev
}
// Left wheel reverse, Right wheel forward
void robot_TURN_LEFT() {
  // Left Motor is reversed
  IN1 = 1;
  IN2 = 0; // Left Rev
  // Right Motor is correct
  IN3 = 1;
  IN4 = 0; // Right Fwd
}
// Left wheel forward, Right wheel reverse
void robot_TURN_RIGHT() {
  // Left Motor is reversed
  IN1 = 0;
  IN2 = 1; // Left Fwd
  // Right Motor is correct
  IN3 = 0;
  IN4 = 1; // Right Rev
}
// BOTH wheels stop
void robot_STOP() {
  IN1 = 0;
  IN2 = 0;
  IN3 = 0;
  IN4 = 0;
}
// Pivot backward and to the left (around left wheel)
void robot_PIVOT_BACK_LEFT(void) {
  // Left motor is stopped
  IN1 = 0;
  IN2 = 0; // Left Stop
  // Right motor is correct
  IN3 = 0;
  IN4 = 1; // Right Rev
}
// Pivot backward and to the right (around right wheel)
void robot_PIVOT_BACK_RIGHT(void) {
  // Left Motor is reversed
  IN1 = 1;
  IN2 = 0; // Left Rev
  // Right motor is stopped
  IN3 = 0;
  IN4 = 0; // Right Stop
}

// --- Delay Function ---
void delay_ms(unsigned int ms) {
  unsigned int i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 112; j++)
      ;
  }
}

// --- Sensor Functions ---
unsigned int get_ultrasonic_distance(void) {
  unsigned int time;
  TMOD = (TMOD & 0xF0) | 0x01;
  TRIG = 1;
  delay_ms(1);
  TRIG = 0;
  while (ECHO == 0)
    ;
  TR0 = 1;
  while (ECHO == 1)
    ;
  TR0 = 0;
  time = (TH0 * 256) + TL0;
  time = (time * 1.085);
  TH0 = 0;
  TL0 = 0;
  return (time / 58);
}
bit is_left_blocked(void) { return (IR_L == 0); }
bit is_right_blocked(void) { return (IR_R == 0); }

// --- Smart Avoidance Functions ---
// (This logic is 100% clean, it calls the fixed motor functions)
void handle_obstacle(void) {
  robot_STOP();
  delay_ms(100);
  robot_MOVE_BACKWARD();
  delay_ms(400);
  robot_STOP();
  delay_ms(100);

  if (!is_right_blocked()) {
    robot_TURN_RIGHT();
    delay_ms(500);
  } else if (!is_left_blocked()) {
    robot_TURN_LEFT();
    delay_ms(500);
  } else {
    robot_TURN_RIGHT();
    delay_ms(1000);
  }
  robot_STOP();
}

// --- Main Program ---
void main(void) {
  unsigned int distance;
  bit left_blocked, right_blocked;

  serial_init();
  EA = 1;
  ES = 1;
  robot_STOP();

  while (1) {
    distance = get_ultrasonic_distance();
    left_blocked = is_left_blocked();
    right_blocked = is_right_blocked();

    if (autonomous) {
      // --- Autonomous Mode ---
      // (This logic is 100% clean, it calls the fixed motor functions)
      if (distance < 20 || left_blocked || right_blocked) {
        handle_obstacle();
      } else {
        robot_MOVE_FORWARD();
      }
    } else {
      // --- Manual Mode (CLEAN AND LOGICAL) ---
      // (This logic is 100% clean, it calls the fixed motor functions)
      switch (bt_cmd) {

      case 'f': // FORWARD
        if (distance < 20 || left_blocked || right_blocked) {
          handle_obstacle();
        } else {
          robot_MOVE_FORWARD();
        }
        break;

      case 'b': // BACKWARD
        robot_MOVE_BACKWARD();
        break;

      case 'l': // LEFT
        if (left_blocked) {
          robot_PIVOT_BACK_RIGHT();
          delay_ms(100);
        } else {
          robot_TURN_LEFT();
        }
        break;

      case 'r': // RIGHT
        if (right_blocked) {
          robot_PIVOT_BACK_LEFT();
          delay_ms(100);
        } else {
          robot_TURN_RIGHT();
        }
        break;

      case 's': // STOP
        robot_STOP();
        break;
      }
    }
    delay_ms(50);
  }
}

// --- Serial Port Setup (9600 Baud) ---
void serial_init(void) {
  TMOD = (TMOD & 0x0F) | 0x20;
  TH1 = 0xFD;
  SCON = 0x50;
  TR1 = 1;
}

// --- Serial Interrupt Service Routine ---
void serial_ISR(void) interrupt 4 {
  if (RI == 1) {
    char cmd = SBUF;
    RI = 0;

    if (cmd == 'a') {
      autonomous = 1;
      bt_cmd = 's';
    } else if (cmd == 'm') {
      autonomous = 0;
      bt_cmd = 's';
    } else {
      bt_cmd = cmd;
    }
  }
}
