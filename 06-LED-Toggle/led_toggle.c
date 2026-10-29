/*
Write an Embedded C program to toggle an active-low LED connected 
to pin P0.8 at the rate of 1 second delay?
*/
#include <lpc214x.h>

#define LED 8 //active low led connection

/* Delay for seconds */
void delay_s(unsigned int dlyS)
{
	dlyS *= 12000000;	// Each second = 1,000 ms
	                  // 12,000 (for 1 ms) × 1,000 = 12,000,000 iterations per second.

	while(dlyS--);     // Decrement the dlyS value until it reaches 0.
}

int main()
{
    /* Configure P0.8 as output pin */
    IODIR0 |= (1 << LED);

    while(1)
    {
        /* Active-low LED ON
           Writing 0 to LED pin turns it ON */
        IOCLR0 = (1 << LED);

        /* Delay */
        delay_s(1);

        /* Active-low LED OFF
           Writing 1 to LED pin turns it OFF */
        IOSET0 = (1 << LED);

        /* Delay */
        delay_s(1);
    }
}
