LED Patterns Using LPC2129

📌 Project Overview

This project demonstrates four different LED patterns using the LPC2129 (ARM7) microcontroller and eight active-low LEDs connected to Port 0. The patterns are programmed using Embedded C and bitwise operations.

🎯 Objectives

- Interface eight active-low LEDs with the LPC2129.
- Implement different LED blinking sequences.
- Understand bitwise operations and bit manipulation.
- Configure GPIO pins as output pins.
- Generate delays to control LED patterns.

🛠️ Hardware and Software Requirements

- Microcontroller: LPC2129 (ARM7)
- Output: 8 active-low LEDs
- Programming Language: Embedded C
- IDE: Keil µVision

🔌 Hardware Connections

LPC2129 Pin| Connection
P0.0 – P0.7| 8 Active-Low LEDs

⚙️ LED Patterns Implemented

1. Left to Right

LEDs glow one by one from left to right.

2. Right to Left

LEDs glow one by one from right to left.

3. Ends to Center

Two LEDs glow simultaneously, moving from both ends towards the center.

4. Center to Ends

Two LEDs glow simultaneously, moving from the center towards both ends.

All four patterns repeat continuously with a software delay between LED transitions.

💻 Concepts Covered

- GPIO configuration using "IODIR0"
- Port manipulation using "IOPIN0"
- Active-low LED interfacing
- Bitwise NOT ("~") and shift ("<<") operators
- Bit masking
- Loops and software delay functions

🖼️ Hardware Output

Hardware images are available in the "Images" folder.

🎥 Project Demonstration

The LED pattern demonstration video is available in the "Video" folder.

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "GPIO" "LED Interfacing" "Bitwise Operations"