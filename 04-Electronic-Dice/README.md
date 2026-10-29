Electronic Dice Game Using LPC2129

📌 Project Overview

This project implements an electronic dice game using the LPC2129 (ARM7) microcontroller and a 16×2 LCD. Two push buttons allow Player 1 and Player 2 to roll a virtual dice, with the result displayed on the LCD.

🎯 Objectives

- Generate dice values from 1 to 6.
- Interface a 16×2 LCD with the LPC2129.
- Use push buttons as player inputs.
- Display rolling values and the final dice result.
- Understand GPIO input handling and Embedded C programming.

🛠️ Hardware and Software Requirements

- Microcontroller: LPC2129
- Display: 16×2 LCD
- Input: Two push buttons
- Programming Language: Embedded C
- IDE: Keil µVision

🔌 Hardware Connections

LCD Connections

LPC2129 Pin| LCD Pin
P0.8 – P0.15| D0 – D7
P0.16| RS
P0.17| RW
P0.18| EN

Push Button Inputs

- Player 1: P1.16
- Player 2: P1.17

⚙️ Working Principle

1. Initializes the LCD and displays the project title.
2. Waits for Player 1 to press and release the push button.
3. Generates dice values from 1 to 6 while the button is held.
4. Displays the final dice value on the LCD.
5. Repeats the same process for Player 2.
6. Continues the game in an infinite loop.

📚 Concepts Covered

- Embedded C programming
- LPC2129 GPIO interfacing
- LCD initialization and display functions
- Push button input handling
- Random number generation using "rand()"
- Loops, conditional statements, and software delays

🖼️ Hardware Output

Project hardware images are available in the "Images" folder.

🎥 Project Demonstration

The demonstration video is available in the "Video" folder.

🏷️ Technologies

"LPC2129" "ARM7" "Embedded C" "Keil µVision" "16×2 LCD" "GPIO" "Push Button Interfacing"