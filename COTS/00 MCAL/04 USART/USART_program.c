#include 		"STD_TYPES.h"
#include 		"BIT_MATH.h"
#include		"Dio_interface.h"
#include 		"USART_interface.h"
#include 		"USART_private.h"
#include		"USART_config.h"


void  	USART_Init(void)
{
	u8 Local_UCSRC = 0 ;
	u8 Local_UBRRH = 0 ; 
	
	/* 	Enable Transmit and Enable Receive			 */
	SET_BIT(UCSRB, 4);
	SET_BIT(UCSRB, 3);	
	
	/*	Rx And Tx OUTPUT							 */
	DIO_voidSetPinDirection(PORTD,PIN0,INPUT);
	DIO_voidSetPinDirection(PORTD,PIN1,OUTPUT);
	
	/* 	 Mode of Operation 		  				 */
	#if 		MODE_OF_OPERATION == ASYNCHRONOUS
	    CLR_BIT(Local_UCSRC,6);
	#elif	MODE_OF_OPERATION == SYNCHRONOUS	
	    SET_BIT(Local_UCSRC,6);
	#endif
		
	/* 	 Transmission Speed 		  				 */	
	#if		MODE_OF_OPERATION == ASYNCHRONOUS 		
		#if	TRANSMISSION_SPEED == NORMAL_SPEED
			SET_BIT(UCSRA,1);
		#elif TRANSMISSION_SPEED == DOUBLE_SPEED
			CLR_BIT(UCSRA,1);
			#endif
	#elif 	MODE_OF_OPERATION == SYNCHRONOUS
			CLR_BIT(UCSRA,1);
	#endif
	
	/* 	Send 8 bit Data Size  				 	*/
	#if 		CHARACTER_BITS == 5
			CLR_BIT(UCSRB,2);
			CLR_BIT(Local_UCSRC, 1);
			CLR_BIT(Local_UCSRC, 2);
	#elif 	CHARACTER_BITS == 6
			CLR_BIT(UCSRB,2);
			SET_BIT(Local_UCSRC, 1);
			CLR_BIT(Local_UCSRC, 2);
	#elif 	CHARACTER_BITS == 7
			CLR_BIT(UCSRB,2);
			CLR_BIT(Local_UCSRC, 1);
			SET_BIT(Local_UCSRC, 2);
	#elif 	CHARACTER_BITS == 8
			CLR_BIT(UCSRB,2);
			SET_BIT(Local_UCSRC, 1);
			SET_BIT(Local_UCSRC, 2);
	#elif 	CHARACTER_BITS == 9
			SET_BIT(UCSRB,2);
			SET_BIT(Local_UCSRC, 1);
			SET_BIT(Local_UCSRC, 2);
	#endif
	
	/* 	Number of Stop Bits 		  				*/
	#if 		STOP_BITS == ONE_BIT
			CLR_BIT(Local_UCSRC,3);
	#elif 	STOP_BITS == TWO_BIT
			SET_BIT(Local_UCSRC,3);
	#endif
	
	/*  Parity Mode		  						*/
	#if 		PARITY_MODE == DISABLED
			CLR_BIT(Local_UCSRC,4);
			CLR_BIT(Local_UCSRC,5);
	#elif 	PARITY_MODE == EVEN_PARITY
			CLR_BIT(Local_UCSRC,4);
			SET_BIT(Local_UCSRC,5);
	#elif 	PARITY_MODE == ODD_PARITY
			SET_BIT(Local_UCSRC,4);
			SET_BIT(Local_UCSRC,5);
	#endif
	
	/* 	Baud Rate Equation		  				*/
	#if 		MODE_OF_OPERATION == ASYNCHRONOUS
		#if(TRANSMISSION_SPEED == NORMAL_SPEED)
			Local_UBRRH = ((F_CPU/(16*BAUD_RATE))-1);
			CLR_BIT(UBRRH,8); 					 //Selecting UBRRH
			UBRRH = (u8)(Local_UBRRH>>8);
			UBRRL = (u8)Local_UBRRH;
		#elif(TRANSMISSION_SPEED == DOUBLE_SPEED)
			Local_UBRRH = ((F_CPU/(8*BAUD_RATE))-1);
			CLR_BIT(UBRRH,8); 					 //Selecting UBRRH
			UBRRH = (u8)(Local_UBRRH>>8);
			UBRRL = (u8)Local_UBRRH;
				#endif
			
	#elif 	MODE_OF_OPERATION == SYNCHRONOUS
			Local_UBRRH = ((F_CPU/(2*BAUD_RATE))-1);
			CLR_BIT(UBRRH,8); 					 //Selecting UBRRH
			UBRRH = (u8)(Local_UBRRH>>8);
			UBRRL = (u8)Local_UBRRH;
	#endif		
	
	/* 	Clock Polarity	   		  				 */
	#if 		MODE_OF_OPERATION == SYNCHRONOUS
		#if(CLOCK_POLARITY == RISING_EDGE)
			CLR_BIT(Local_UCSRC,0);
		#elif(CLOCK_POLARITY == FALLING_EDGE)
			SET_BIT(Local_UCSRC,0);
			#endif
		
	#elif 	MODE_OF_OPERATION == ASYNCHRONOUS
 			CLR_BIT(Local_UCSRC,0);
	#endif
	
	SET_BIT(Local_UCSRC, 7);  					 //Selecting UCSRC
	UCSRC = Local_UCSRC;
	
}

void  	USART_SendByte(u8 Byte)
{
	 while ((GET_BIT(UCSRA, 5))== 0);
	 UDR = Byte;
}

void 	USART_SendString(u8 * str)
{
	u8 i = 0 ;
	
	while(str[i] != '\0')
	{
		USART_SendByte(str[i]);
		i++;
	}
}

u8  	USART_ReceiveByte(void) 
{
	while ((GET_BIT(UCSRA, 7))== 0);
	return UDR;
	CLR_BIT(UCSRA,7); 							 //Clear Flag
}

/*u8 *  USART_ReceiveString(void) 
{
	u8 i = 0 ;
	
	while(str[i] != '\0')
	{
		USART_ReceiveByte(str[i]);
		i++;
	}
}*/
