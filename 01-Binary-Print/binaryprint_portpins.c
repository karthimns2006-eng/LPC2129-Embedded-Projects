/*
Write an Embedded C Program (ECP) for LPC21xx to configure GPIO pins 
P0.8 to P0.15 and P1.16 to P1.23 as output pins and simultaneously 
display an 8-bit binary count from 0 to 255 on both ports with a delay 
of 500 ms using the IOPIN register.
*/
#include <LPC21xx.h>

/* Delay for milliseconds */
void delay_ms(unsigned int dlyMS)
{
	dlyMS *= 12000;	// Each ms = 1,000 µs, so 12 × 1,000 = 12,000 iterations per ms.
	                // Each iteration ~5 cycles --> 5 × 12,000 = 60,000 cycles = 1 ms.

	while(dlyMS--); // Decrement the dlyMS value until it reaches 0.
}

int main()
{
		// Declare counter variable
		unsigned int  count;

		// Configure P0.8 to P0.15 as GPIO outputs
		IODIR0|=0xFF<<8;
		// Configure P1.16 to P1.23 as GPIO outputs
		IODIR1|=0xFF<<16;
while(1)
   for(count = 0; count <= 255; count++)
   {
      // Display counter value on P0.8 to P0.15
			IOPIN0=((IOPIN0&~(0xFF<<8))|(count<<8));
		
      // Display the same counter value on P1.16 to P1.23
			IOPIN1=((IOPIN1&~(0xFF<<16))|(count<<16));

      // Generate 500 ms delay
			delay_ms(50);
    }
	 //while(1);
}

