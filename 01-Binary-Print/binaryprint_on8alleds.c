/*
Write an Embedded C Program (ECP) for LPC2129 to display the binary equivalent of 
decimal numbers from 0 to 255 on 8 Active-Low LEDs connected to pins P0.0 to P0.7. 
The binary count should increment continuously from 0 to 255 with a delay of 1 second 
between successive numbers. After reaching 255, the count should restart from 0 and 
continue indefinitely.
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
		unsigned char  count;

		// Configure P0.0 to P0.7 as GPIO outputs
		IODIR0|=0xFF<<0;


	while(1)
	{
		 for(count = 0; count <= 255; count++)
		 {
				// Display counter value on P0.0 to P0.7
				IOPIN0=((IOPIN0&~(0xFF<<0))|((~count)<<0));
				// Generate 1000 ms delay
				delay_ms(1000);
			}
	}
	 //while(1);
}

