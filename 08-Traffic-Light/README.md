Traffic Light Control System Using LPC2129

📌 Project Overview

This project implements a four-road traffic light control system using the LPC2129 (ARM7) microcontroller. Each road's traffic signals operate in sequence using Embedded C programming and software delays.

🎯 Objectives

- Control traffic signals for four roads.
- Understand GPIO output configuration.
- Implement sequential signal control using Embedded C.
- Use software delays to control signal timing.

🛠️ Hardware and Software

- Microcontroller: LPC2129 (ARM7)
- Programming Language: Embedded C
- IDE: Keil µVision
- Hardware: LPC2129 development board and red, yellow, and green LEDs

⚙️ Working Principle

- P1.16 to P1.27 are configured as output pins.
- Each road has red, yellow, and green signal outputs.
- Each road receives a green signal for 10 seconds, followed by a yellow signal for 3 seconds.
- The remaining three roads display red signals.
- The sequence repeats continuously for all four roads.

💻 Source Code

File: "trafficlightcontrol_AHleds.c"

🖼️ Hardware Output

Add your hardware photo inside the "Images" folder.

"Traffic Light Hardware Output" (Images/Traffic_Light.jpeg)

🎥 Project Demonstration

Add your demonstration video inside the "Video" folder.

"Watch the Traffic Light Demo" (Video/Traffic_Light.mp4)

📚 Key Learnings

- GPIO direction and output control
- Bitwise operations
- Sequential traffic signal control
- Function-based Embedded C programming
- Software delay implementation

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "GPIO" "Traffic Light Control"