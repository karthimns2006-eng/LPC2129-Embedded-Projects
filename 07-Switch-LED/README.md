Switch Press Counter Using LPC2129

📌 Project Overview

This project demonstrates a switch press counter using the LPC2129 (ARM7) microcontroller. Each time the switch is pressed, the counter increments and its binary equivalent is displayed on 8 active-low LEDs.

🎯 Objectives

- Interface a switch with the LPC2129 microcontroller.
- Display the switch press count in binary using LEDs.
- Understand GPIO input and output configuration.
- Implement switch debouncing using a software delay.

🛠️ Hardware and Software

- Microcontroller: LPC2129 (ARM7)
- Programming Language: Embedded C
- IDE: Keil µVision
- Hardware: LPC2129 development board, 8 LEDs, and a push-button switch

⚙️ Working Principle

- P0.0 to P0.7 are configured as output pins for the LEDs.
- P1.16 is configured as the switch input.
- Each switch press increments the counter.
- The counter value is displayed in binary on the active-low LEDs.
- A delay is used for switch debouncing.

💻 Source Code

File: "swpresscount_binaryprinton8alleds.c"

🖼️ Hardware Output

Add your hardware photo inside the "Images" folder.

"Switch Press Counter Output" (Images/Switch_LED.jpeg)

🎥 Project Demonstration

Add your demonstration video inside the "Video" folder.

"Watch the Switch Press Counter Demo" (Video/Switch_LED.mp4)

📚 Key Learnings

- GPIO input and output configuration
- Binary number representation
- Switch interfacing
- Active-low LED operation
- Software debouncing

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "GPIO" "LED Interfacing"