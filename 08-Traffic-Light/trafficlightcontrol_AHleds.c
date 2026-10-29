#include <LPC21xx.h>

/* Traffic Light Bit Definitions */
#define S1R (1<<16)
#define S1Y (1<<17)
#define S1G (1<<18)

#define S2R (1<<19)
#define S2Y (1<<20)
#define S2G (1<<21)

#define S3R (1<<22)
#define S3Y (1<<23)
#define S3G (1<<24)

#define S4R (1<<25)
#define S4Y (1<<26)
#define S4G (1<<27)

/*----------------------------------------------------
  Software Delay
----------------------------------------------------*/
void delay_ms(unsigned int ms)
{
    unsigned int i,j;

    for(i=0;i<ms;i++)
        for(j=0;j<6000;j++);
}

/*----------------------------------------------------
  Turn OFF all LEDs
----------------------------------------------------*/
void All_OFF(void)
{
    IO1CLR = 0x0FFF0000;     // P1.16-P1.27 OFF
}

/*----------------------------------------------------
  Road 1 Green
----------------------------------------------------*/
void Road1_Green(void)
{
    All_OFF();

    IO1SET = S1G;
    IO1SET = S2R | S3R | S4R;
}

/*----------------------------------------------------
  Road 1 Yellow
----------------------------------------------------*/
void Road1_Yellow(void)
{
    All_OFF();

    IO1SET = S1Y;
    IO1SET = S2R | S3R | S4R;
}

/*----------------------------------------------------
  Road 2 Green
----------------------------------------------------*/
void Road2_Green(void)
{
    All_OFF();

    IO1SET = S2G;
    IO1SET = S1R | S3R | S4R;
}

/*----------------------------------------------------
  Road 2 Yellow
----------------------------------------------------*/
void Road2_Yellow(void)
{
    All_OFF();

    IO1SET = S2Y;
    IO1SET = S1R | S3R | S4R;
}

/*----------------------------------------------------
  Road 3 Green
----------------------------------------------------*/
void Road3_Green(void)
{
    All_OFF();

    IO1SET = S3G;
    IO1SET = S1R | S2R | S4R;
}

/*----------------------------------------------------
  Road 3 Yellow
----------------------------------------------------*/
void Road3_Yellow(void)
{
    All_OFF();

    IO1SET = S3Y;
    IO1SET = S1R | S2R | S4R;
}

/*----------------------------------------------------
  Road 4 Green
----------------------------------------------------*/
void Road4_Green(void)
{
    All_OFF();

    IO1SET = S4G;
    IO1SET = S1R | S2R | S3R;
}

/*----------------------------------------------------
  Road 4 Yellow
----------------------------------------------------*/
void Road4_Yellow(void)
{
    All_OFF();

    IO1SET = S4Y;
    IO1SET = S1R | S2R | S3R;
}

/*----------------------------------------------------
  Main Function
----------------------------------------------------*/
int main(void)
{
    /* Configure P1.16-P1.27 as outputs */
    IO1DIR |= 0x0FFF0000;

    All_OFF();

    while(1)
    {
        /* Road 1 */
        Road1_Green();
        delay_ms(10000);

        Road1_Yellow();
        delay_ms(3000);

        /* Road 2 */
        Road2_Green();
        delay_ms(10000);

        Road2_Yellow();
        delay_ms(3000);

        /* Road 3 */
        Road3_Green();
        delay_ms(10000);

        Road3_Yellow();
        delay_ms(3000);

        /* Road 4 */
        Road4_Green();
        delay_ms(10000);

        Road4_Yellow();
        delay_ms(3000);
    }
}
