//eint0_test.c
//Write an ECP to demonstrate External interrupt 0 in LPC2129?
#include <LPC21xx.h>

#define PORT0 0
#define PORT1 1

#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3

#define EINT0_PIN      16    //select the one port pin which will give support for EINT0
#define EINT0_VIC_CHNO 14	     //assign the EINT0 channel number
#define EINT0_LED      9      //toggle one LED for every interrupt, so select one port pin


void CfgPortPinFunc(unsigned int,unsigned int,unsigned int);

void eint0_isr(void) __irq
{
	//toggle EINT_LED
	IOPIN0 ^= (1<<EINT0_LED);
	
	//clear eint0 status (through EXTINT SFR)
	EXTINT = 1<<0;
	
	//clear eint0 status in VIC (through VICVectAddr )
	VICVectAddr = 0;
}	


void Enable_EINT0(void)
{
	//configure P0.1/P0.16 as EINT0 input pin
	CfgPortPinFunc(PORT0,EINT0_PIN,FUNC2);
	
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
	IODIR0 |= (1<<EINT0_LED);
	Enable_EINT0();
	while(1)
	{
		count++; //some regular operation
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

