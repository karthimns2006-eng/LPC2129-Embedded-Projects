/*----------------------------------------------------
Program : Binary Equivalent of Switch Press Count
Controller : LPC2129 (ARM7)
LEDs : P0.0 to P0.7
Switch : P1.16

Operation:
1. Each switch press increments a counter.
2. Counter value is displayed in binary on LEDs.
3. Key debounce delay included.
-----------------------------------------------------*/

#include <LPC21xx.h>

unsigned char count = 0;

/* Delay for milliseconds */
void delay_ms(unsigned int dlyMS)
{
	dlyMS *= 12000;	// Each ms = 1,000 µs, so 12 × 1,000 = 12,000 iterations per ms.
	                // Each iteration ~5 cycles ? 5 × 12,000 = 60,000 cycles = 1 ms.

	while(dlyMS--); // Decrement the dlyMS value until it reaches 0.
}

int main(void)
{
    // Configure P0.0 - P0.7 as Output (LEDs) 
    IODIR0 |= 0x000000FF;

    // Configure P1.16 as Input (Switch) 
    IODIR1 &= ~(1 << 16);

    // Initially turn OFF LEDs 
    IOSET0 = 0x000000FF;

    while(1)
    {
        // Check if switch is pressed
        if(!(IOPIN1 & (1 << 16)))
        {
					count++;

          // Display count in binary on LEDs
					IOPIN0=((IOPIN0&~(0xFF<<0))|((~count)<<0));

          // Wait until switch is released 
          while(!(IOPIN1 & (1 << 16)));

          // Release debounce 
          delay_ms(20);          
        }
    }
}
