/*
Write an Embedded C program to display a digital clock (HH:MM:SS) 
and date (DD/MM/YYYY) on a 16×2 LCD. 
Initialize the LCD, display a welcome message, 
and continuously update the time and date using nested loops.
*/
#include <LPC21xx.h>

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


//FUNCTION PROTOTYPES
void delay_us(unsigned int);
void delay_ms(unsigned int);

void WriteLCD(unsigned char);
void CmdLCD(unsigned char);
void InitLCD(void);
void CharLCD(unsigned char);
void StrLCD(char *);
void IntLCD(int);

void digitalclock_update(unsigned int,unsigned int,
												 unsigned int,unsigned int,
												 unsigned int,unsigned int);
void digitalclock_display(unsigned int,unsigned int,
												  unsigned int,unsigned int,
												  unsigned int,unsigned int);

unsigned int hour,min,sec,date,month,year; // Variables to store time and date values

// Main function entry point
int main()  
{
  InitLCD();                              // Initialize LCD module and GPIO pins
  StrLCD(":DIGITAL  CLOCK:");             // Display title on first LCD line
  CmdLCD(0xC0);                           // Move cursor to beginning of second line
  StrLCD("---  DISPLAY ---");             // Display welcome message on second line
  delay_ms(1000);                         // Wait for 1 second
  CmdLCD(0x01);                           // Clear LCD screen
	
	// Initialize the digital clock with intial values
	//digitalclock_update(year,month,date,hour,min,sec); 
	digitalclock_update(2026,9,22,10,10,0);
	// Infinite loop
  while(1)                                
	{
		// Pass the initialized year, month, date, hour, minute, and second values to start the digital clock display
		digitalclock_display(year,month,date,hour,min,sec);
	}
}


/* Delay for microseconds */
void delay_us(unsigned int dlyUS)
{
	dlyUS *= 12;		// Scale the input value.
	                // Each loop iteration consumes ~5 CPU cycles.
	                // 5 cycles × 12 iterations = 60 cycles = 1 µs (for 60 MHz CPU).

	while(dlyUS--);  // Decrement then dlyUS value until it reaches 0.
}

/* Delay for milliseconds */
void delay_ms(unsigned int dlyMS)
{
	dlyMS *= 12000;	// Each ms = 1,000 µs, so 12 × 1,000 = 12,000 iterations per ms.
	                // Each iteration ~5 cycles ? 5 × 12,000 = 60,000 cycles = 1 ms.

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

// Function to update clock and calendar values
void digitalclock_update(unsigned int yr,unsigned int mo,
												 unsigned int da,unsigned int ho,
												 unsigned int mi, unsigned int se)
{
	year = yr;      // Store input year into global year variable
  month = mo;     // Store input month into global month variable
  date = da;      // Store input date into global date variable
  hour = ho;      // Store input hour into global hour variable
  min = mi;       // Store input minute into global minute variable
  sec = se;       // Store input second into global second variable
}

// Function to display digital clock on LCD
void digitalclock_display(unsigned int yr,unsigned int mo,
												  unsigned int da,unsigned int ho,
												  unsigned int mi, unsigned int se)
{
	for(yr=year; yr<2030; yr++)   // Loop through years until 2029
	{
		for(mo=month; mo<=12; mo++) // Loop through current month to December
		{
			for(da=date; da<31; da++) // Loop through current date to 30
			{
				for(ho=hour; ho<24; ho++) // Loop through current hour to 23
				{
					for(mi=min; mi<60; mi++) // Loop through current minute to 59
					{
						for(se=sec; se<60; se++) // Loop through current second to 59
						{
						CmdLCD(0x80); 					// Move cursor to beginning of first line
						CharLCD((ho/10) + 48); 	// Display hour tens digit
						CharLCD((ho%10) + 48); 	// Display hour units digit
						CharLCD(':');           // Display ':' separator
						CharLCD((mi/10) + 48);  // Display minute tens digit
						CharLCD((mi%10) + 48);  // Display minute units digit
						CharLCD(':');           // Display ':' separator
						CharLCD((se/10) + 48);  // Display second tens digit
						CharLCD((se%10) + 48);  // Display second units digit
						CmdLCD(0xC0); 					// Move cursor to beginning of second line
						CharLCD((da/10) + 48);  // Display date tens digit
						CharLCD((da%10) + 48);  // Display date units digit
						CharLCD('/');           // Display '/' separator
						CharLCD((mo/10) + 48); 	// Display month tens digit
						CharLCD((mo%10) + 48); 	// Display month units digit
						CharLCD('/');           // Display '/' separator
						IntLCD(yr);             // Display year value
						delay_ms(1000);         // Wait for 1 second before updating
						}
					}
				}
			}
		}
	}
}

