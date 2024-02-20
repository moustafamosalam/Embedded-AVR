#include 	"STD_TYPES.h"
#include 	"BIT_MATH.h"
#include 	"RTO_interface.h"

#include			<util/delay.h>
#include 		<avr/io.h>
#include		<avr/interrupt.h>

#define			NULL			(void *) 0
#define			F_CPU			16000000UL

/*  				Toggle LEDs				*/
void 		LED1  	(void)
{
	PORTC ^=(1<<2);
}

void 		LED2  	(void)
{
	PORTC ^=(1<<7);
}

void 		LED3  	(void)
{
	PORTD ^=(1<<3);
}


#define 		NUM_OF_TASKS 			3
volatile      u16 RTO_u16Ticks = 0  ;


TCB_Tasks 		Tasks[NUM_OF_TASKS] ;

void		RTO_voidCreateTask(u8 Task_ID , u16 Periodicity , void  (*pf)(void), u16 First_Delay)
{
	Tasks[Task_ID].u16_periodicity = Periodicity;
	Tasks[Task_ID].PfTask = pf;
	Tasks[Task_ID].u16_FirstDelay = First_Delay;
}

/* 			Scheduler API 					*/
static void RTO_voidScheduler(void)
{
	for(int i = 0; i < NUM_OF_TASKS; i++)
	{
		if((RTO_u16Ticks % ((Tasks[i].u16_periodicity)+(Tasks[i].u16_FirstDelay))) == 0)
		{
			Tasks[i].PfTask();
			Tasks[i].u16_FirstDelay=0;
		}
	}
}


/* 			Tick Time ====> Timer0 			*/
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	RTO_u16Ticks++;
	RTO_voidScheduler();
}


int main()
{
	/*			Direction 	 									*/
	DDRC = 0xFF;
	DDRD = 0xFF;
	/*			Timer Configuration to get overflow at 1ms			*/
	TCNT0 = 6;
	/* 			Normal  Modem ,   Pre = 64							*/
	TCCR0 = 0x03 ;
	
	SET_BIT(TIMSK,0);
	SET_BIT(SREG ,7);
	/* 			Create Task										*/
	RTO_voidCreateTask(0,1000,LED1,0);
	RTO_voidCreateTask(1,2000,LED2,1000);
	RTO_voidCreateTask(2,3000,LED3,2000);
	
	
	while(1)
	{

		
	}
	
	return 0;
}