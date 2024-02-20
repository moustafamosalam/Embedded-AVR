#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer0_configuration.h"
#include "Timer0_Private.h"
#include "Timer0_Register.h"
#include "Timer0_interface.h"

#ifndef			NULL
#define			NULL	(void *)0
#endif

static void (*OFCallBack_PF)(void) = NULL ;
static void (*CTCCallBack_PF)(void) = NULL ;

void	Timer0_Init	(void)
{
	/*	Waveform Generation Mode		*/
	
	#if 	Mode == Normal
	CLR_BIT(TCCR0,3);	//WGM01 Pin
	CLR_BIT(TCCR0,6);	//WGM00 Pin
	
	#elif 	Mode == PWM_Phase_Correct
	CLR_BIT(TCCR0,3);	//WGM01 Pin
	SET_BIT(TCCR0,6);	//WGM00 Pin
	
	#elif 	Mode == CTC
	SET_BIT(TCCR0,3);	//WGM01 Pin
	CLR_BIT(TCCR0,6);	//WGM00 Pin

	
	#elif 	Mode == Fast_PWM
	SET_BIT(TCCR0,3);	//WGM01 Pin
	SET_BIT(TCCR0,6);	//WGM00 Pin
	
	#else
	#error	"Wrong Choice of Timer 0 Waveform Generation Mode!"
	#endif
	
	/*	Prescaler				*/
	#if 	Prescaler == 1
	SET_BIT(TCCR0,0);	//CS00 Pin
	CLR_BIT(TCCR0,1);	//CS01 Pin
	CLR_BIT(TCCR0,2);	//CS02 Pin

	#elif 	Prescaler == 8
	CLR_BIT(TCCR0,0);	//CS00 Pin
	SET_BIT(TCCR0,1);	//CS01 Pin
	CLR_BIT(TCCR0,2);	//CS02 Pin
	
	#elif 	Prescaler == 64
	SET_BIT(TCCR0,0);	//CS00 Pin
	SET_BIT(TCCR0,1);	//CS01 Pin
	CLR_BIT(TCCR0,2);	//CS02 Pin
	
	#elif 	Prescaler == 256
	CLR_BIT(TCCR0,0);	//CS00 Pin
	CLR_BIT(TCCR0,1);	//CS01 Pin
	SET_BIT(TCCR0,2);	//CS02 Pin
	
	#elif 	Prescaler == 1024
	SET_BIT(TCCR0,0);	//CS00 Pin
	CLR_BIT(TCCR0,1);	//CS01 Pin
	SET_BIT(TCCR0,2);	//CS02 Pin

	#elif 	Prescaler == External_Clock_Falling	//On T0 pin, used as a counter
	CLR_BIT(TCCR0,0);	//CS00 Pin
	SET_BIT(TCCR0,1);	//CS01 Pin
	SET_BIT(TCCR0,2);	//CS02 Pin

	#elif 	Prescaler == External_Clock_Rising //On T0 pin, used as a counter
	SET_BIT(TCCR0,0);	//CS00 Pin
	SET_BIT(TCCR0,1);	//CS01 Pin
	SET_BIT(TCCR0,2);	//CS02 Pin
	
	#else
	#error	"Wrong Choice of Timer 0 Prescaler!"
	#endif

}

void	TIMER0_EnableOverFlowInt(void)
{
	SET_BIT(TIMSK,0);
}

void	TIMER0_EnableCTCInt(void)
{
	SET_BIT(TIMSK,1);
}

void	TIMER0_DisableOverFlowInt(void)
{
	CLR_BIT(TIMSK,0);
}

void	TIMER0_DisableCTCInt(void)
{
	CLR_BIT(TIMSK,1);
}


void	TIMER0_SetTCNT0(u8 Val)
{
	TCNT0= Val;
}
void	TIMER0_SetOCR0(u16 Val)
{
	OCR0= Val;
}

/*	ISR SetCallBack Functions 		*/
void	TIMER0_voidSetCallBackOF(void (*PF)(void))
{
	OFCallBack_PF = PF;
}
void	TIMER0_voidSetCallBackCTC(void (*PF)(void))
{
	CTCCallBack_PF = PF ;
}

/*	ISR Functions For Timer0 Compare Match & Overflow Interrupts 		*/
void	__vector_10 (void) //Timer0 Compare Match Interrupt
{
	CTCCallBack_PF();
}
void	__vector_11 (void) //Timer0 Overflow Interrupt
{
	OFCallBack_PF();
}

/*		Global Interrupts Enable and Disable	*/
void GIE_voidEnable(void)
{
	SET_BIT(SREG,7);
}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG,7);
}