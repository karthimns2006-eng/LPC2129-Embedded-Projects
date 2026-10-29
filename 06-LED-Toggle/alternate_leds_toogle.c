/*
Write an Embedded C Program (ECP) for LPC21xx to configure 
GPIO pins P0.8 to P0.15 as output pins and toggle the 
alternate pins continuously with a delay of 500 ms using 
the IOPIN register.
*/

#include <LPC21xx.h>

/*
0x55 - 01010101
0xAA - 10101010
11111111 - 255 / 0xFF

*/

/* Delay for milliseconds */
void delay_ms(unsigned int dlyMS)
{
	dlyMS *= 12000;	// Each ms = 1,000 µs, so 12 × 1,000 = 12,000 iterations per ms.
	                // Each iteration ~5 cycles --> 5 × 12,000 = 60,000 cycles = 1 ms.

	while(dlyMS--); // Decrement the dlyMS value until it reaches 0.
}

int main()
{
    // Configure P0.8 to P0.15 as GPIO outputs
		IODIR0 |= 0xFF<<8;

    while(1)
    {
      // Output alternate pins pattern (0x55)
			//IOPIN0 = (IOPIN0 & 0xFFFF00FF) | (0x55 << 8);
			//IOPIN0 = (IOPIN0 & 0xFFFF00FF);
			IOPIN0 = (IOPIN0 & ~(0xFF<<8));
			IOPIN0 = IOPIN0 | (0x55 << 8);
			/*
			(IOPIN0 & 0xFFFF00FF) = (IOPIN0 & ~(0xFF<<8))
			*/
      // Generate 500 ms delay
			delay_ms(500);


      // Output alternate pins pattern (0xAA)
			//IOPIN0 = (IOPIN0 & 0xFFFF00FF) | (0xAA << 8);
			//IOPIN0 = (IOPIN0 & 0xFFFF00FF);
			IOPIN0 = (IOPIN0 & ~(0xFF<<8));
			IOPIN0 = IOPIN0 | (0xAA << 8);

      // Generate 500 ms delay
			delay_ms(500);

    }
}
