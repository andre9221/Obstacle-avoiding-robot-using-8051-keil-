# 🤖 Ultrasonic Obstacle Avoiding Robot using 8051

> A dual-mode (manual + autonomous) delivery robot built on the AT89S52 (8051) microcontroller, designed for hospital medicine delivery use cases.

**Team:** Andrea. A (24BCE1142) 

---

## 📌 Overview

This robot operates in two modes switchable via Bluetooth:

- **Manual Mode** — controlled via smartphone app or voice commands over HC-05 Bluetooth
- **Autonomous Mode** — self-navigating using ultrasonic + IR sensors with a "Smart Turn" algorithm

A key application is contact-free medicine delivery between hospital rooms.

---

## 🧰 Components

| Component | Qty | Purpose |
|---|---|---|
| AT89S52 (8051) Microcontroller Board | 1 | Central control unit |
| L293D Motor Driver Module | 1 | Controls direction & speed of DC motors |
| HC-05 Bluetooth Module | 1 | Wireless communication with smartphone |
| HC-SR04 Ultrasonic Sensor | 1 | Front obstacle detection (2–400 cm range) |
| IR Obstacle Sensor Module | 2 | Side obstacle detection (left & right) |
| DC Geared Motor (6–12V, 100 RPM) | 2 | Drives the wheels |
| Robot Chassis with Caster Wheel | 1 | Physical frame |
| 9V Battery / Power Bank | 1 | Powers logic and motor circuits |
| Breadboard (Medium) | 1 | Circuit assembly |
| Jumper Wires | ~20–25 | Pin-to-pin connections |

---

## 🧠 How It Works

### Autonomous Mode
1. Ultrasonic sensor continuously measures distance ahead
2. IR sensors detect side obstacles
3. If obstacle detected within 20 cm → robot stops, reverses, checks sides
4. Turns toward the open side ("Smart Turn" logic)
5. Resumes forward motion once path is clear

### Manual Mode
- Commands sent via Bluetooth serial from a smartphone
- Safety override: robot ignores forward commands if obstacle is detected and auto-avoids instead

### Bluetooth Commands
| Key | Action |
|---|---|
| `f` | Forward |
| `b` | Backward |
| `l` | Turn Left |
| `r` | Turn Right |
| `s` | Stop |
| `a` | Switch to Autonomous Mode |
| `m` | Switch to Manual Mode |

---

## 📐 Distance Formula

```
Distance (cm) = Time (µs) / 58
```

---

## 💻 Code

The full C code is in [`main.c`](./main.c). Compiled using **Keil µVision** and flashed via **ProgISP** over USBasp.

### Flashing the Code

1. Compile in Keil µVision → generate `.hex` file
2. Connect board via USB A-to-B cable, set jumper to **PROG**
3. Open ProgISP → select `AT89S52` + `USBasp` → Connect
4. Load Flash → select `.hex` → Erase → Program
5. Set jumper to **RUN**, power the board → robot is live

---

## 📷 Demo

<!-- Add a photo or video of your robot here -->
> 📸 Photos of the working model are in the [`/media`](./media) folder.  
> 🎥 Demo video: [Link here]

---

## 🔋 Power Setup

The robot uses a **dual-power configuration** to prevent microcontroller resets when motors draw current:
- **Logic circuit** → 5V regulated supply (for 8051, HC-05, sensors, L293D logic)
- **Motor circuit** → 6–9V supply (for DC motors via L293D)
- Both circuits share a **common ground**

> ⚠️ In the working model, a USB-connected power bank was used instead of two separate batteries.

---

## 📁 Repo Structure

```
📦 obstacle-avoiding-robot-8051
├── obstacleavoidingcode.c             # Full C source code
├── README.md           # This file
├── report.pdf
├── media/
│   ├── robot_front.png
│   ├── robot_side.png
│   └── robot_top.png
└── pin diag/
   └── basicpindiag.png

```

---

## 📚 References

- [Nevon Projects – Obstacle Avoider Robot](https://nevonprojects.com/obstacle-avoider-robotic-vehicle-project/)
- [Circuit Digest – Edge Avoiding Robot using 8051](https://circuitdigest.com/microcontroller-projects/edge-avoiding-robot-using-8051)
- [IJIREEICE Paper](https://ijireeice.com/wp-content/uploads/2021/06/IJIREEICE.2021.9538.pdf)
- [Learn Electronics India – Obstacle Detection using 8051](https://www.learnelectronicsindia.com/post/obstacle-detection-system-using-8051-microcontroller)

---

## 📄 License

This project was submitted as part of coursework at **VIT Chennai**. For academic and educational use only. This is a self made project, any misuse is strictly prohibited.
