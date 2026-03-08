# Uploading Code to 8051 (AT89S52) Development Board

This guide explains how to upload a compiled program (`.hex` file) to an **AT89S52 8051 microcontroller board** using **ProgISP** and a **USBasp programmer**.

# 1. Required Materials

Before starting, ensure you have the following:

* **AT89S52 development board** (with in-built USB programmer)
* **USB A-to-B cable**
* **Computer with ProgISP installed**
* **Compiled `.hex` file** generated from **Keil µVision**
* **Power source**

  * 9V adapter **or**
  * USB power supply



# 2. Board Setup

1. Connect the **AT89S52 board** to your computer using the **USB A-to-B cable**.

2. Verify that the **Power LED on the board turns ON**.

3. If the board is **not detected**, install the **USBasp driver**.

4. Ensure the board **jumper is set to `PROG` mode**.


# 3. Open ProgISP

1. Launch the **ProgISP** software.

2. In the **Chip selection**, choose:

```
AT89S52
```

3. Under **Programmer**, select:

```
USBasp
```

4. Click **Connect**.

5. The status window should display:

```
Connected Successfully
```

---

# 4. Load the Program

1. Click **Load Flash**.

2. Select the **`.hex` file** generated from **Keil µVision**.

3. The selected file path will appear in the **Flash Input box**.

---

# 5. Burn the Code to the Microcontroller

Follow the sequence below:

### 1. Erase the chip

Click:

```
Erase
```

Wait until the status shows:

```
Chip Erase OK
```

### 2. Program the chip

Click:

```
Program
```

Wait until the status shows:

```
Verify OK
or
Program Successful
```

At this stage, the **firmware has been successfully written to the AT89S52 microcontroller**.

---

# 6. Run the Robot

1. Close the **ProgISP** software.

2. Disconnect the **USB cable**.

3. Move the board **jumper from `PROG` to `RUN`**.

4. Power the board using:

* **9V adapter**
* **Robot battery pack**

5. Once powered, the **microcontroller begins executing the uploaded program**.

The robot should now:

* Respond to **Bluetooth commands**, or
* Operate in **autonomous mode** depending on the program.

---

# Troubleshooting

If the program upload fails, check the following common issues.

### Chip Not Detected

Possible causes:

* USBasp driver not installed
* Loose USB cable connection

Solution:

* Reinstall the **USBasp driver**
* Reconnect the **USB cable**

---

### Verify Error During Programming

Possible causes:

* Unstable power supply
* Poor USB connection

Solution:

* Ensure **stable power**
* Check the **USB cable and ports**

---

### Robot Not Moving After Upload

Possible cause:

* Jumper still in **PROG mode**

Solution:

* Switch jumper to **RUN mode**

---

### Bluetooth Not Responding

Possible cause:

* Baud rate mismatch

Solution:

Ensure the **baud rate is set to 9600 bps** in:

* The **Bluetooth application**
* The **8051 program code**

---

# Notes

* Always compile your code in **Keil µVision** to generate the `.hex` file before uploading.
* Ensure the **jumper is in PROG mode while uploading** and **RUN mode while executing**.
* Keep a **stable power supply** to avoid programming errors.

---
