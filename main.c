/*Haptic Robotic Arm using modified BO servo motors 


microcontroller: ATmega-8535
clock: 16mhz

compiler win avr

=============== PORTS DETAILS ==================

############ MOTOR DRIVERS USED ############

0-PortB0 & 1-PortB1 ---- WRIST Motor (120RPM) 

4-PortD4 & 5-PortD5 ---- CLAW Motor (120RPM)

6-PortD6 & 7-PortD7 ---- BASE Motor (60RPM)

######### INTERRUPTS USED ##########

int0 --- PortD2 --- for CLAW Motor

int1 --- PortD3 --- for BASE Motor

int2 --- PortB2 --- for WRIST Motor

######### POTENTIOMETERS USED ##########

POT0 --- PortA0 --- for CLAW Motor

POT1 --- PortA1 --- for BASE Motor

POT2 --- PortA2 --- for WRIST Motor


*********************************************************************************/



#include<avr/io.h>
#include<avr/interrupt.h>
#include"adc.h"
#include"delay.h"

unsigned int x0=0,x1=0,x2=0,position0,position1,position2,potval0,potval1,potval2;

ISR (INT0_vect)  //claw motor
{
 
	if(position0>x0)
	{
     PORTD &=0x0F;
	 PORTD |=0x10;
	 x0++;
	}
   
	if(position0<x0)
	{
	 PORTD &=0x0F;
	 PORTD |=0x20;
	 x0--;
	}
   
	if((position0<(x0+3))&(position0>(x0-3)))
	{
	PORTD &=0xCF;
	}  
}

ISR (INT1_vect)  //base motor
{
 
	if(position1>x1)
	{
     PORTD &=0x0F;
	 PORTD |=0x40;
	 x1++;
	}
   
	if(position1<x1)
	{
	 PORTD &=0x0F;
	 PORTD |=0x80;
	 x1--;
	}
   
	if((position1<(x1+2))&(position1>(x1-2)))
	{
	PORTD &=0x3F;
	}  
}


ISR (INT2_vect)   //wrist motor
{
 
	if(position2>x2)
	{
     PORTB &=0xFC;
	 PORTB |=0x01;
	 x2++;
	}
   
	if(position2<x2)
	{
	 PORTB &=0xFC;
	 PORTB |=0x02;
	 x2--;
	}
   
	if((position2<(x2+3))&(position2>(x2-3)))
	{
	PORTB &=0xFC;
	}  
}

void deg0(unsigned int value0)  //claw motor
{
   position0=value0;
   
   if(position0!=x0)
    {
	   
		if(position0>x0)
		{
		PORTD &=0x0F;
		PORTD |=0x10;
		delayms(10);
		}
   
		if(position0<x0)
		{
		PORTD &=0x0F;
		PORTD |=0x20;
		delayms(10);
		}
   }
 // PORTD &=0xCF;
}


void deg1(unsigned int value1)  //base motor
{
   position1=value1;
  
   if(position1!=x1)
    {
	   
		if(position1>x1)
		{
		PORTD &=0x0F;
		PORTD |=0x40;
		delayms(10);
		}
   
		if(position1<x1)
		{
		PORTD &=0x0F;
		PORTD |=0x80;
		delayms(10);
		}
   }
//  PORTD &=0x3F;
}


void deg2(unsigned int value2)  //wrist motor
{
   position2=value2;

   if(position2!=x2)
    {
	   
		if(position2>x2)
		{
		PORTB &=0xFC;
		PORTB |=0x01;
		delayms(10);
		}
   
		if(position2<x2)
		{
		PORTB &=0xFC;
		PORTB |=0x02;
		delayms(10);
		}
   }
//  PORTB &=0xFC;
}



int main(void)
{
 delayms(1000);
 DDRB=0x03;
 DDRD=0xf0;
  
 MCUCSR=0x00;		  // bit6 (ISC2) for interrupt 2 sense control, falling edge ISC2=0, rising edge ISC2=1 
 MCUCR=0x0a;		 //  lower 4 bit for interrupt 0 & 1 sense control, 0x0a=falling edge, 0x0f=rising edge 
 GICR=0xe0;			//   interrupt1,interrupt0,interrupt2  higher 3 bits for enabling and desabiling
 adc_init();
 x0=(getdata(0)*3)+3;
 x1=getdata(1)+3;
 x2=(getdata(2)*4)+3;
 sei();				//enable interrupt
 
	while(1)
	{
 
	potval0=(getdata(0)*3)+3;
	deg0(potval0);
  
	potval1=getdata(1)+3;
	deg1(potval1);
   
	potval2=(getdata(2)*4)+3;
	deg2(potval2);
   
	}
 
 }
 



  
