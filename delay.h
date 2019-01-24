/*	LCD.h

	this header file provides time delay in the form of mili second and micro second
	without affecting any interrupts.

	delayms()  this function provides delay in the form of mili second
	delayus()  this function provides delay in the form of micro second
	
*/
#ifndef _DELAY_H_
#define _DELAY_H_
unsigned int delaycounter1,delaycounter2;
void delayms(unsigned int delaytime)
{

	 for(delaycounter1=0;delaycounter1<=delaytime;delaycounter1++)
	 {
		 for(delaycounter2=0;delaycounter2<=800;delaycounter2++)
		  {
		  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
		  }
		
	 }
}

void delayus(unsigned int delaytime)
{

	 for(delaycounter1=0;delaycounter1<=delaytime;delaycounter1++)
	 {
		 
		  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");asm("nop");
	 }
}

#endif 
