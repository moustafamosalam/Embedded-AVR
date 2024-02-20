#include 	"STD_TYPES.h"
#include 	"BIT_MATH.h"
#include	    "Dio_interface.h"
#include 	"ADC_interface.h"
#include 	"ADC_register.h"
#include	"ADC_config.h"


void ADC_Init(void)
{
	/*  	V Ref = 5  	  						  */
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	
	/*		Enable ADC								*/
	SET_BIT(ADCSRA,7);
	
	/*   	Analog Channel Selecion		 						  */
	#if		CHANNEL	== 0
	CLR_BIT(ADMUX,0);
	CLR_BIT(ADMUX,1);
	CLR_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#elif	CHANNEL	== 1
	SET_BIT(ADMUX,0);
	CLR_BIT(ADMUX,1);
	CLR_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#elif	CHANNEL	== 2
	CLR_BIT(ADMUX,0);
	SET_BIT(ADMUX,1);
	CLR_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#elif	CHANNEL	== 3
	SET_BIT(ADMUX,0);
	SET_BIT(ADMUX,1);
	CLR_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#elif	CHANNEL	== 4
	CLR_BIT(ADMUX,0);
	CLR_BIT(ADMUX,1);
	SET_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#elif	CHANNEL	== 5
	SET_BIT(ADMUX,0);
	CLR_BIT(ADMUX,1);
	SET_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#elif	CHANNEL	== 6
	CLR_BIT(ADMUX,0);
	SET_BIT(ADMUX,1);
	SET_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#elif	CHANNEL	== 7
	SET_BIT(ADMUX,0);
	SET_BIT(ADMUX,1);
	SET_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);
	#endif
	
	/*		Auto Trigger										*/
	#if		AUTO_TRIGGER	==	ENABLED
	SET_BIT(ADCSRA,5);
	#elif	AUTO_TRIGGER	==	DISABLED
	CLR_BIT(ADCSRA,5);
	#endif
	
	/*  		PreScaler   						  				*/
	#if		PRESCALER	==	2
	CLR_BIT(ADCSRA,0);
	CLR_BIT(ADCSRA,1);
	CLR_BIT(ADCSRA,2);
	#elif		PRESCALER	==	4
	CLR_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	CLR_BIT(ADCSRA,2);
	#elif		PRESCALER	==	8
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	CLR_BIT(ADCSRA,2);
	#elif		PRESCALER	==	16
	CLR_BIT(ADCSRA,0);
	CLR_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	#elif		PRESCALER	==	32
	SET_BIT(ADCSRA,0);
	CLR_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	#elif		PRESCALER	==	64
	CLR_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	#elif		PRESCALER	==	128
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	#endif
	
	/*       Clear The Flag    								*/
	SET_BIT(ADCSRA,4);
	
	/*		ADC Interrupt										*/
	#if 		ADC_INTERRUPT	==	ENABLED
	SET_BIT(ADCSRA,3);
	#elif	ADC_INTERRUPT	==	DISABLED
	CLR_BIT(ADCSRA,3);
	#endif
	
	/*		RIGHT/LEFT RESULT ADJUSTMENT						*/
	#if		RES_ADJUSTMENT	==	RIGHT
	CLR_BIT(ADMUX,5);
	#elif	RES_ADJUSTMENT	==	LEFT
	SET_BIT(ADMUX,5);
	#endif
}

u16 ADC_Read(void)
{
	u16 Local_u16Value = 0 ;
	/*     Start Conversion 					  */
	SET_BIT(ADCSRA,6);
	
	/*     Polling  					  		  */
	while((GET_BIT(ADCSRA,4))==0);
	
	/*     Read The Conversion Value			  */
	Local_u16Value = ADC;
	
	return Local_u16Value;
}