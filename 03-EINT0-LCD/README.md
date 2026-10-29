External Interrupts and LCD Interfacing Using LPC2129

📌 Project Overview

This project demonstrates external interrupt handling using the LPC2129 (ARM7) microcontroller. It includes three Embedded C programs to explore EINT0, EINT1, LED control, and LCD interfacing.

🎯 Objectives

- Understand external interrupts in the LPC2129.
- Configure interrupt pins using the Pin Connect Block.
- Enable and handle interrupts using the Vectored Interrupt Controller (VIC).
- Display interrupt counts on a 16×2 LCD.
- Control LEDs using external interrupt events.

🛠️ Hardware and Software Requirements

- Microcontroller: LPC2129
- Display: 16×2 LCD (for LCD-based implementation)
- Output: LEDs
- Programming Language: Embedded C
- IDE: Keil µVision

⚙️ Project Implementations

1. EINT0 and EINT1 Interrupts

Source file: "eint0_eint1_test.c"

- Configures EINT0 and EINT1.
- Uses the VIC to enable both interrupts.
- Toggles separate LEDs when the corresponding interrupt service routines execute.
- Clears interrupt status flags after handling the interrupts.

2. EINT0 with LCD

Source file: "eint0_lcd.c"

- Configures EINT0 and its interrupt service routine.
- Increments an interrupt counter when EINT0 occurs.
- Displays the interrupt count on a 16×2 LCD.
- Demonstrates LCD interfacing and interrupt handling together.

3. EINT0 with LED

Source file: "eint0_test.c"

- Configures EINT0 as an external interrupt input.
- Uses the VIC to handle the interrupt.
- Toggles an LED whenever the interrupt service routine executes.
- Demonstrates interrupt-driven LED control.

🔌 LCD Connections

LPC2129 Pin| LCD Pin
P0.8 – P0.15| D0 – D7
P0.16| RS
P0.17| RW
P0.18| EN

The LCD is configured in 8-bit mode.

📚 Concepts Covered

- External interrupts (EINT0 and EINT1)
- Interrupt Service Routines (ISR)
- Vectored Interrupt Controller (VIC)
- Pin Connect Block and "PINSEL" registers
- Interrupt status clearing using "EXTINT"
- GPIO and LED interfacing
- 16×2 LCD interfacing
- Embedded C functions and bitwise operations

🖼️ Hardware Output

Project hardware images are available in the "Images" folder.

🎥 Project Demonstration

Demonstration videos are available in the "Video" folder.

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "External Interrupts" "VIC" "GPIO" "LCD Interfacing"