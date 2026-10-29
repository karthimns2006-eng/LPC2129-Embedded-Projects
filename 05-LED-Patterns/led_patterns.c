/*
led_patterns.c
Write an Embedded C Program for LPC2129 to display the following patterns on 8 Active-Low LEDs connected to Port-0:

1. LEDs glow one by one from Left to Right.
2. LEDs glow one by one from Right to Left.
3. Two LEDs glow simultaneously from the ends towards the center.
4. Two LEDs glow simultaneously from the center towards the ends.
*/

#include <LPC21xx.h>

/* Delay for milliseconds */
void delay_ms(unsigned int dlyMS)
{
	dlyMS *= 12000;	// Each ms = 1,000 �s, so 12 � 1,000 = 12,000 iterations per ms.
	                // Each iteration ~5 cycles ? 5 � 12,000 = 60,000 cycles = 1 ms.

	while(dlyMS--); // Decrement the dlyMS value until it reaches 0.
}

int main()
{
    int i;
    unsigned char pattern;

    IODIR0 = 0x000000FF;    // P0.0 to P0.7 as outputs

    while(1)
    {
        /* Pattern 1 : Left to Right */
        for(i = 0; i < 8; i++)
        {
            pattern = ~(1 << i);      // Active LOW
            IOPIN0 = (IOPIN0 & 0xFFFFFF00) | (pattern & 0xFF);
            delay_ms(100);
        }

        /* All LEDs OFF */
        IOPIN0 = (IOPIN0 & 0xFFFFFF00) | 0xFF;
        delay_ms(100);

        /* Pattern 2 : Right to Left */
        for(i = 0; i < 8; i++)
        {
            pattern = ~(1 << (7 - i)); // Active LOW
            IOPIN0 = (IOPIN0 & 0xFFFFFF00) | (pattern & 0xFF);
            delay_ms(100);
        }

        /* All LEDs OFF */
        IOPIN0 = (IOPIN0 & 0xFFFFFF00) | 0xFF;
        delay_ms(100);

        /* Pattern 3 : Two LEDs from Ends to Center */
        for(i = 0; i < 4; i++)
        {
            pattern = ~((1 << i) | (1 << (7 - i)));
            IOPIN0 = (IOPIN0 & 0xFFFFFF00) | (pattern & 0xFF);
            delay_ms(100);
        }

        /* All LEDs OFF */
        IOPIN0 = (IOPIN0 & 0xFFFFFF00) | 0xFF;
        delay_ms(100);

        /* Pattern 4 : Two LEDs from Center to Ends */
        for(i = 0; i < 4; i++)
        {
            pattern = ~((1 << (3 - i)) | (1 << (4 + i)));
            IOPIN0 = (IOPIN0 & 0xFFFFFF00) | (pattern & 0xFF);
            delay_ms(100);
        }

        /* All LEDs OFF */
        IOPIN0 = (IOPIN0 & 0xFFFFFF00) | 0xFF;
        delay_ms(100);
    }
}
