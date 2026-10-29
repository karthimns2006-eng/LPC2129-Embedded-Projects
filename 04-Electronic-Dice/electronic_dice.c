/*
electronic_dice.c
Write an Embedded C program to display a digital clock (HH:MM:SS) 
and date (DD/MM/YYYY) on a 16�2 LCD. 
Initialize the LCD, display a welcome message, 
and continuously update the time and date using nested loops.
*/
#include <LPC21xx.h>

#include <stdlib.h>

/*LCD CONNECTION DETAILS
LCD is operated in 8-bit mode.

LPC2148 Pin          LCD Pin
-----------------------------
P0.8  - P0.15   -->  D0 - D7
P0.16           -->  RS
P0.17           -->  RW
P0.18           -->  EN

RS = Register Select
RS = 0 --> Command Register
RS = 1 --> Data Register

RW = Read/Write
RW = 0 --> Write operation
RW = 1 --> Read operation

EN = Enable
A High-to-Low pulse on EN causes the LCD to latch the data/command.
*/

#define LCD_DATA   8        // LCD D0 starts from P0.8
#define LCD_RS     16       // LCD RS connected to P0.16
#define LCD_RW     17       // LCD RW connected to P0.17
#define LCD_EN     18       // LCD EN connected to P0.18

#define SW1_AL 16 //P1.16
#define SW2_AL 17 //P1.17


//FUNCTION PROTOTYPES
void delay_us(unsigned int);
void delay_ms(unsigned int);

void WriteLCD(unsigned char);
void CmdLCD(unsigned char);
void InitLCD(void);
void CharLCD(unsigned char);
void StrLCD(char *);
void IntLCD(int);


// Main function entry point
int main()
{
    unsigned char diceFace = 0;   // Stores current dice value
    unsigned int seed;            // Seed value for random number generation

    InitLCD();                    // Initialize LCD

    StrLCD("Electronic Dice");    // Display project title

    while(1)                      // Infinite loop
    {
        // Display Player 1 prompt
        CmdLCD(0xC0);
        StrLCD("Player1: ");
        IntLCD(0);

        // Wait until Player 1 switch is pressed
        while(((IOPIN1 >> SW1_AL) & 1) == 1);

        // Check if switch is pressed
        if(((IOPIN1 >> SW1_AL) & 1) == 0)
        {
            // Generate random numbers while switch is held down
            while(((IOPIN1 >> SW1_AL) & 1) == 0)
            {
                diceFace = ((rand() % 6) + 1); // Generate dice value 1 to 6
                srand(seed++);                 // Update random seed

                // Display rolling dice value
                CmdLCD(0xC0);
                StrLCD("Player1: ");
                IntLCD(diceFace);

                delay_ms(20);                  // Small delay for rolling effect
            }

            // Display final dice value for Player 1
            CmdLCD(0xC0);
            StrLCD("Player1: ");
            IntLCD(diceFace);

            delay_ms(500);                     // Display result for 500 ms
        }

        // Display Player 2 prompt
        CmdLCD(0xC0);
        StrLCD("Player2: ");
        IntLCD(0);

        // Wait until Player 2 switch is pressed
        while(((IOPIN1 >> SW2_AL) & 1) == 1);

        // Check if switch is pressed
        if(((IOPIN1 >> SW2_AL) & 1) == 0)
        {
            // Generate random numbers while switch is held down
            while(((IOPIN1 >> SW2_AL) & 1) == 0)
            {
                diceFace = ((rand() % 6) + 1); // Generate dice value 1 to 6
                srand(seed++);                 // Update random seed

                // Display rolling dice value
                CmdLCD(0xC0);
                StrLCD("Player2: ");
                IntLCD(diceFace);

                delay_ms(20);                  // Small delay for rolling effect
            }

            // Display final dice value for Player 2
            CmdLCD(0xC0);
            StrLCD("Player2: ");
            IntLCD(diceFace);

            delay_ms(500);                     // Display result for 500 ms
        }
    }
}

/* Delay for microseconds */
void delay_us(unsigned int dlyUS)
{
	dlyUS *= 12;		// Scale the input value.
	                // Each loop iteration consumes ~5 CPU cycles.
	                // 5 cycles � 12 iterations = 60 cycles = 1 �s (for 60 MHz CPU).

	while(dlyUS--);  // Decrement then dlyUS value until it reaches 0.
}

/* Delay for milliseconds */
void delay_ms(unsigned int dlyMS)
{
	dlyMS *= 12000;	// Each ms = 1,000 �s, so 12 � 1,000 = 12,000 iterations per ms.
	                // Each iteration ~5 cycles ? 5 � 12,000 = 60,000 cycles = 1 ms.

	while(dlyMS--); // Decrement the dlyMS value until it reaches 0.
}

//This function places one byte on LCD D0-D7 and generates an Enable pulse.
void WriteLCD(unsigned char byte)
{
    //RW = 0 --> Select LCD WRITE operation.
    IOCLR0 = 1 << LCD_RW;

		// Place the byte on P0.8 - P0.15.
    IOPIN0 = (IOPIN0 & ~(0xFF << LCD_DATA)) | (byte << LCD_DATA);

    //EN = 1 --> Start LCD Enable pulse.
    IOSET0 = 1 << LCD_EN;
    //Small delay to satisfy LCD Enable pulse width.
    delay_us(1);

		//EN = 0 --> High-to-Low transition latches the byte into the LCD.
    IOCLR0 = 1 << LCD_EN;

		//Wait for LCD internal operation to complete.
    delay_ms(2);
}

//Sends a COMMAND to the LCD.
void CmdLCD(unsigned char cmd)
{
    //RS = 0 --> Select LCD Instruction/Command Register.
    IOCLR0 = 1 << LCD_RS;

		//Send command byte to LCD.
    WriteLCD(cmd);
}

//Initializes GPIO pins and configures the LCD for 8-bit operation.
void InitLCD(void)
{
		//Configure LCD data lines and control signals as OUTPUT pins.
    IODIR0 |= (0xFF << LCD_DATA)
            | (1 << LCD_RS)
            | (1 << LCD_RW)
            | (1 << LCD_EN);


    //LCD requires a delay after power is applied
    //before initialization commands are sent.
    delay_ms(15);

    //Standard HD44780 8-bit initialization sequence.
		// Send Function Set command 0x30.
    CmdLCD(0x30);
    delay_ms(4);

    // Wait at least approximately 100 us.
    delay_us(100);

		//Send Function Set again.
    CmdLCD(0x30);
    delay_us(100);

		//Send Function Set for the third time.
    CmdLCD(0x30);

		//8-bit interface, 2-line display, 5x8 character font
    CmdLCD(0x38);

		//display on cursor off
    CmdLCD(0x0C);

		//Clear Display
    CmdLCD(0x01);

		//Cursor moves to the right after every character is written
    CmdLCD(0x06);
}


/***************************************************************************
 *                           CharLCD()
 *
 * Displays one character on the LCD.
 ***************************************************************************/

void CharLCD(unsigned char asciiVal)
{
    //RS = 1 -->Select LCD Data Register.
    IOSET0 = 1 << LCD_RS;
		//Write ASCII value into LCD DDRAM.
    WriteLCD(asciiVal);
}

//Displays a string on LCD.
void StrLCD(char *s)
{
    while(*s)          // Check for end of string
    {
        CharLCD(*s++); // Display character and move to next
				//delay_ms(500);
		}
}

//Displays an integer number (+/-) on LCD.
void IntLCD(int n)
{
    signed int i = 0;
    unsigned char a[10];   // Array to store digits

    // Check for negative number
    if(n < 0)
    {
        CharLCD('-');      // Display minus sign
        n = -n;            // Convert to positive number
    }

    // If number is zero
    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        // Extract digits and store in reverse order
        while(n > 0)
        {
            a[i++] = (n % 10) + 48;  // Convert digit to ASCII
            n /= 10;                 // Remove last digit
        }

        // Display digits in correct order
        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}
