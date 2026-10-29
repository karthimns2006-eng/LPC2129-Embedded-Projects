Digital Clock and Calendar Using LPC2129

📌 Project Overview

This project demonstrates a digital clock and calendar using the LPC2129 microcontroller and a 16×2 LCD. The display shows the time in HH:MM:SS format and the date in DD/MM/YYYY format using Embedded C programming.

🎯 Objectives

- Display time and date on a 16×2 LCD.
- Interface the LCD with the LPC2129 microcontroller.
- Implement time and date updates using nested loops.
- Understand LCD commands, data transmission, and GPIO control.

🛠️ Hardware and Software Requirements

- Microcontroller: LPC2129
- Display: 16×2 LCD
- Programming Language: Embedded C
- IDE: Keil µVision
- Development Board: LPC2129 board

⚙️ Hardware Connections

LPC2129 Pin| LCD Pin
P0.8 – P0.15| D0 – D7
P0.16| RS
P0.17| RW
P0.18| EN

The LCD operates in 8-bit mode.

💻 Working Principle

1. Initializes the LCD and GPIO pins.
2. Displays a welcome message.
3. Initializes the clock with the starting date and time: 22/09/2026, 10:10:00.
4. Displays the time on the first LCD line and the date on the second line.
5. Uses nested loops and software delays to update the displayed values.

📚 Concepts Covered

- Embedded C programming
- LPC2129 GPIO configuration
- 16×2 LCD interfacing
- LCD command and data functions
- Functions and global variables
- Nested loops and software delays
- Time and date formatting

🖼️ Hardware Output

The hardware images are available in the "Images" folder.

🎥 Project Demonstration

The project demonstration video is available in the "Video" folder.

[▶ Watch Digital Clock Demo](Digital_Clock.mp4)

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "16×2 LCD" "GPIO Interfacing"