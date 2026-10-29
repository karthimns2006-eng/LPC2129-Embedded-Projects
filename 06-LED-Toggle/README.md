LED Toggle Using LPC2129

📌 Project Overview

This project demonstrates LED control using the LPC2129 (ARM7) microcontroller and Embedded C. It includes two programs: toggling alternate LEDs on Port 0 and blinking an active-low LED with a software delay.

🎯 Objectives

- Configure GPIO pins as output pins.
- Toggle alternate LED patterns continuously.
- Control an active-low LED using GPIO registers.
- Understand bitwise operations and software delays.

🛠️ Hardware and Software Requirements

- Microcontroller: LPC2129 / LPC21xx
- Output: LEDs
- Programming Language: Embedded C
- IDE: Keil µVision

⚙️ Project Implementations

1. Alternate LED Toggle

Source file: "alternate_leds_toggle.c"

- Configures P0.8 to P0.15 as output pins.
- Alternates between the bit patterns "0x55" and "0xAA".
- Uses the "IOPIN0" register to update the output pattern.
- Adds a software delay between pattern changes.

2. Single LED Toggle

Source file: "led_toggle.c"

- Configures P0.8 as an output pin.
- Controls an active-low LED using "IOCLR0" and "IOSET0".
- Turns the LED ON and OFF with a software delay.
- Repeats the blinking sequence continuously.

🔌 Hardware Connections

Program| LPC21xx Pins
Alternate LED Toggle| P0.8 – P0.15
Single LED Toggle| P0.8

📚 Concepts Covered

- GPIO direction configuration using "IODIR0"
- GPIO output control using "IOPIN0", "IOCLR0", and "IOSET0"
- Active-low LED interfacing
- Bitwise operators and bit masking
- Hexadecimal and binary patterns
- Software delay functions and infinite loops

🖼️ Hardware Output

Hardware images are available in the "Images" folder.

🎥 Project Demonstration

Demonstration videos are available in the "Video" folder.

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "GPIO" "LED Interfacing"