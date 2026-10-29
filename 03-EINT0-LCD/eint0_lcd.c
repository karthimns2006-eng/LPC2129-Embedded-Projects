//eint0_lcd.c
//Write an ECP to demonstrate External interrupt 0 in LPC2129?
#include <LPC21xx.h>

#define PORT0 0
#define PORT1 1

#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3

#define EINT0_PIN      1    //select the one port pin which will give support for EINT0
#define EINT0_VIC_CHNO 14	     //assign the EINT0 channel number
//#define EINT0_LED      9      //toggle one LED for every interrupt, so select one port pin

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

void CfgPortPinFunc(unsigned int,unsigned int,unsigned int);

/*
synatx to define ISR in keil ARM CC Compiler
void isr_name(void) __irq
{

}
*/
unsigned int int_count=0;

void eint0_isr(void) __irq
{
	int_count++;
	CmdLCD(0xC0);
	StrLCD("Int.Count:");
	IntLCD(int_count);
	
	//clear eint0 status (through EXTINT SFR)
	EXTINT = 1<<0;
	
	//clear eint0 status in VIC (through VICVectAddr )
	VICVectAddr = 0;
}	


void Enable_EINT0(void)
{
	//configure P0.16 as EINT0 input pin
	CfgPortPinFunc(PORT0,EINT0_PIN,FUNC4);
	
	//configure VIC (Vector Interrupt controller)
	//def External interrupts (EINT0/EINT1/EINT2/EINT3) 
	//is IRQ types (by using VICIntSelect SFR)
	//VICIntSelect = 0x00000000; //by default IRQ type is selcted
	
	//enable EINT0 via VIC (by using VICIntEnable SFR)
	VICIntEnable = 1<<EINT0_VIC_CHNO;
	//enable vectored irq slot 0 for EINT0 (0-15 based on requirement � by using VICVectCntl0 SFR)
	VICVectCntl0 = (1<<5)|EINT0_VIC_CHNO;
	//load isr address into slot 0 (0-15 based on requirement � by using VICVectAddr0 SFR)
	VICVectAddr0 = (unsigned int)eint0_isr;
	
	//configure External Interrupts Peripheral
	//configure EINT0/EINT1/EINT2/EINT3 as edge triggered (use EXTMODE SFR)
	EXTMODE = 1<<0; //EINT0 selected for edge trigger
	//def EINT0/EINT1/EINT2/EINT3 is Falling Edge Triggerd (use EXTPOLAR SFR)
	//EXTPOLAR = 1<<0;	//raising edge	
}


unsigned int count;

int main()
{
	Enable_EINT0();
	InitLCD();
	while(1)
	{
		CmdLCD(0x80);
		StrLCD("Count:");
		IntLCD(count++); 
		delay_ms(1000);
	}		
}

void CfgPortPinFunc(unsigned int portNo, unsigned int pinNo, unsigned int pinFunc)
{
    // Check if the selected port is Port 0
    if(portNo == 0)
    {
        // Configure pins P0.0 to P0.15 using PINSEL0
        if(pinNo <= 15)
        {
            PINSEL0 = ((PINSEL0 & ~(3 << (pinNo * 2))) |
                       (pinFunc << (pinNo * 2)));
        }

        // Configure pins P0.16 to P0.31 using PINSEL1
        else if(pinNo >= 16 && pinNo <= 31)
        {
            PINSEL1 = ((PINSEL1 & ~(3 << ((pinNo - 16) * 2))) |
                       (pinFunc << ((pinNo - 16) * 2)));
        }
    }

    // Code for Port 1 configuration can be added here
    /*
    else if(portNo == 1)
    {
    }
    */
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


