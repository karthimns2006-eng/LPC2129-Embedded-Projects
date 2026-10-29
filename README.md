# LPC2129-Embedded-Projects
LPC2129-based Embedded C projects covering GPIO, LED patterns, switch interfacing, LCD, interrupts, and digital clock applications.

LPC2129 Embedded C Projects

This repository is a collection of 8 hands-on Embedded C projects developed using the LPC2129 (ARM7) microcontroller and Keil µVision IDE. Each project was designed and tested on LPC hardware to strengthen practical knowledge in microcontroller programming, GPIO configuration, LED and LCD interfacing, external interrupts, and software-based control logic.

Instead of focusing only on simulation, these projects were implemented to understand how Embedded C interacts with real hardware, how peripherals are configured through registers, and how different embedded concepts work in practice.

---

Project Collection

01. Binary Print

Implemented binary counting from 0 to 255 using 8 active-low LEDs connected to the LPC2129. The project demonstrates GPIO output configuration, bitwise operations, and binary number representation through hardware.

02. Digital Clock

Developed a digital clock and date display using a 16×2 LCD. The project covers LCD initialization, command and data transmission, time formatting, and continuous display updates using Embedded C.

03. EINT0 LCD

Implemented External Interrupt (EINT0) handling using the LPC2129's Vectored Interrupt Controller (VIC). The interrupt count is displayed on the LCD, providing practical experience with Interrupt Service Routines (ISR) and interrupt-driven programming.

04. Electronic Dice

Built a two-player electronic dice game using push-button switches and a 16×2 LCD. The project generates dice values from 1 to 6, displays rolling effects, and demonstrates GPIO input handling with Embedded C.

05. LED Patterns

Created multiple LED lighting sequences using 8 active-low LEDs, including left-to-right, right-to-left, ends-to-center, and center-to-ends patterns. The project focuses on bit manipulation, GPIO control, and timing.

06. LED Toggle

Implemented both single LED blinking and alternate LED toggling using software delays. The project demonstrates active-low LED operation, GPIO register manipulation, and basic embedded timing concepts.

07. Switch Press Counter

Designed a switch-controlled binary counter where every push-button press increments a counter and displays its binary equivalent on LEDs. The implementation includes switch debouncing and real-time GPIO input/output handling.

08. Traffic Light Control

Developed a four-road traffic light controller using red, yellow, and green LEDs. The project follows a sequential timing algorithm to simulate real traffic signal operation using Embedded C and GPIO control.

---

Technologies Used

- Microcontroller: LPC2129 (ARM7)
- Programming Language: Embedded C
- Development Environment: Keil µVision
- Hardware Interfaces: GPIO, 16×2 LCD, Active-Low LEDs, Push Buttons, External Interrupts (EINT)

---

Key Learning Outcomes

These projects helped me gain practical experience in:

- Register-level programming
- GPIO input and output configuration
- Bitwise operations and masking
- LCD interfacing in 8-bit mode
- External interrupt handling using VIC
- Switch debouncing techniques
- Software delay implementation
- Sequential control logic for embedded systems
- Hardware testing and debugging on the LPC2129 development board

This repository reflects my hands-on learning journey in Embedded Systems through practical LPC2129 implementations using Embedded C.