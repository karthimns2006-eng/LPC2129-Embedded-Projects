Binary Print Using LPC2129

📌 Project Overview

This project demonstrates binary counting using the LPC2129 (ARM7) microcontroller. The programs display binary count values from 0 to 255 using GPIO output pins, helping to understand binary number representation and direct port manipulation in Embedded C.

🎯 Objectives

- Display decimal numbers from 0 to 255 in binary format.
- Understand GPIO output configuration and port manipulation.
- Implement continuous binary counting with software delays.
- Explore different GPIO pin configurations on the LPC2129.

🛠️ Hardware and Software Requirements

- Microcontroller: LPC2129 (ARM7)
- Programming Language: Embedded C
- IDE: Keil µVision
- Hardware: LPC2129 development board and LEDs

⚙️ Project Implementations

1. Binary Print on 8 Active-Low LEDs

Source file: "binaryprint_on8alleds.c"

- Configures P0.0 to P0.7 as GPIO outputs.
- Displays binary count values from 0 to 255 on 8 active-low LEDs.
- Uses a software delay between successive count values.
- Repeats the counting sequence continuously.

2. Binary Print Using Multiple GPIO Port Pins

Source file: "binaryprint_portpins.c"

- Configures P0.8 to P0.15 and P1.16 to P1.23 as output pins.
- Displays the same 8-bit count value on both configured port-pin groups.
- Uses the IOPIN registers for GPIO output manipulation.
- Repeats the count from 0 to 255 with a software delay.

💻 Concepts Covered

- Binary number representation
- GPIO direction configuration using "IODIR"
- GPIO output manipulation using "IOPIN"
- Bitwise operators and bit masking
- Software delay implementation
- Continuous counting using loops

🖼️ Hardware Output

The hardware image demonstrates the LPC2129 development board and the binary counting output.

"Binary Print Hardware Output" (Images/Binary_Print.jpeg)

🎥 Project Demonstration

The demonstration video shows the binary counting project running on the hardware.

"View Binary Print Demo" (Video/Binary_Print.mp4)

📚 Key Learnings

- Practical Embedded C programming using LPC2129.
- Configuring GPIO pins as outputs.
- Displaying binary values through LED interfaces.
- Using bitwise operations for port manipulation.
- Debugging and testing microcontroller programs.

<video src="Video/Binary_Print.mp4" controls width="600"></video>

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "GPIO" "LED Interfacing"