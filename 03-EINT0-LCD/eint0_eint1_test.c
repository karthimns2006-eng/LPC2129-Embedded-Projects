//eint0_eint1_test.c
#include <LPC21xx.h>

#define PORT0 0
#define PORT1 1

#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3


#define EINT0_PIN      16 //select the one port pin which will give support for EINT0
#define EINT0_VIC_CHNO 14	//assign the EINT0 channel number
#define EINT0_LED       9 //toggle one LED for every interrupt0, so select one port pin 
#define EINT1_PIN  		 14 //select the one port pin which will give support for EINT0 
#define EINT1_VIC_CHNO 15	//assign the EINT1 channel number
#define EINT1_LED      10 //toggle one LED for every interrupt1, so select one port pin 


void CfgPortPinFunc(unsigned int,unsigned int,unsigned int);

void eint0_isr(void) __irq
{
	//toggle led EINT0_LED
	IOPIN0 ^= (1<<EINT0_LED);
	//clear eint0 status (through EXTINT SFR)	
	EXTINT = 1<<0;
	//clear eint0 status in VIC (through VICVectAddr SFR)
	VICVectAddr = 0;
}	

void eint1_isr(void) __irq
{
	//toggle led EINT1_LED	
	IOPIN0 ^= (1<<EINT1_LED);
	//clear eint1 status (through EXTINT SFR)	
	EXTINT = 1<<1;
	//clear eint1 status in VIC (through VICVectAddr  SFR)
	VICVectAddr = 0;
}


void Enable_EINTs(void)
{
	 //configure P0.16 as EINT0 input pin and P0.14 as EINT1 input pin (Use PIN CONNECT BLOCK SFRS)
	CfgPortPinFunc(PORT0,EINT0_PIN,FUNC2);
	CfgPortPinFunc(PORT0,EINT1_PIN,FUNC3);

	//configure VIC (Vector Interrupt controller)
	//def External interrupts EINT0 & EINT1 is IRQ types (by using VICIntSelect SFR)
	
	//enable EINT0 & EINT1 via VIC (by using VICIntEnable SFR)
	VICIntEnable = (1<<EINT0_VIC_CHNO)|(1<<EINT1_VIC_CHNO);
	//enable vectored irq slot 0 for EINT0 (by using VICVectCntl0 SFR)
	VICVectCntl0 = ((1<<5)|EINT0_VIC_CHNO);
	//load eint0_isr address into slot 0 (by using VICVectAddr0 SFR)
	VICVectAddr0 = (unsigned int) eint0_isr;
	
	//enable vectored irq slot 1 for EINT1 (by using VICVectCntl1 SFR)
	VICVectCntl1 = ((1<<5)|EINT1_VIC_CHNO);
	//load eint1_isr address into slot 1(by using VICVectAddr1 SFR)
	VICVectAddr1 = (unsigned int)eint1_isr;
	
	//configure External Interrupts Peripheral
	//configure EINT0&EINT1 as edge triggered (use EXTMODE SFR)
	EXTMODE = (1<<0)|(1<<1);
	//configure EINT0&EINT1 as Falling Edge Triggerd (use EXTPOLAR SFR)
	
}

unsigned int count;

int main()
{
	IODIR0 |= ((1<<EINT0_LED)|(1<<EINT1_LED));
	Enable_EINTs();
	while(1)
	{
		count++;
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

