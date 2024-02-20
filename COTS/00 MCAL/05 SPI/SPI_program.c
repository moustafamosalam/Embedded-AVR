#include 		"STD_TYPES.h"
#include 		"BIT_MATH.h"

#include 		"SPI_interface.h"
#include 		"SPI_private.h"
#include 		"SPI_config.h"


void 		SPI_Init(void)
{
	/* 		ENABLING SPI 					*/
	SET_BIT(SPCR , 6);
	
	/* 		SELECTING MODE 					*/
	#if 		MS_SELECT 	== 	MASTER
	  SET_BIT(SPCR, 4);
	#elif 	MS_SELCT 	== 	SLAVE
	  CLR_BIT(SPCR, 4);
	#else
		#error "WRONG CHOICE OF MODE!"
	#endif
	
	/* 		SELECTING POLARITY 				*/
	#if 		CPOL 	== 		RISING
	  CLR_BIT(SPCR, 3);
	#elif 	CPOL 	== 		FALLING
	  SET_BIT(SPCR, 3);
	#else
		#error "WRONG CHOICE OF POLARITY!"
	#endif  
	
	/* 		SELECTING PHASE 					*/
	#if 		CPHA 	== 		SAMPLE
	  CLR_BIT(SPCR, 2);
	#elif 	CPHA 	== 		SETUP
	  SET_BIT(SPCR, 2);
	#else
		#error "WRONG CHOICE OF PHASE!"
	#endif 
	
	/*		SPEED SELECTION 					*/
	#if 		SPEED 	== 		NORMAL
	  CLR_BIT(SPSR, 0);
	#elif 	SPEED 	== 		DOUBLE
	  SET_BIT(SPSR, 0);
	#else
		#error "WRONG CHOICE OF SPEED!"
	#endif 
	
	/*  	 	CLOCK RATE 						*/
	#if 		SPEED == NORMAL
		#if CK_RATE == f/4
			CLR_BIT(SPCR, 1);
			CLR_BIT(SPCR, 0);
		#elif CK_RATE == f/16
			CLR_BIT(SPCR, 1);
			SET_BIT(SPCR, 0);
		#elif CK_RATE == f/64
			SET_BIT(SPCR, 1);
			CLR_BIT(SPCR, 0);
		#elif CK_RATE == f/128
			SET_BIT(SPCR, 1);
			SET_BIT(SPCR, 0);
		#error "WRONG CHOICE OF Clock Rate!"
		#endif 
		
	#elif 	SPEED == DOUBLE
		#if CK_RATE == f/2
			CLR_BIT(SPCR, 1);
			CLR_BIT(SPCR, 0);
		#elif CK_RATE == f/8
			CLR_BIT(SPCR, 1);
			SET_BIT(SPCR, 0);
		#elif CK_RATE == f/32
			SET_BIT(SPCR, 1);
			CLR_BIT(SPCR, 0);
		#elif CK_RATE == f/64
			SET_BIT(SPCR, 1);
			SET_BIT(SPCR, 0);
		#error "WRONG CHOICE OF Clock Rate!"
		#endif
	#endif	
	
	/*		Data Order 						*/
	#if 		DATA_ORDER 	== 	MSB
	  CLR_BIT(SPCR, 5);
	#elif 	DATA_ORDER 	== 	LSB
	  SET_BIT(SPCR, 5);
	#else
		#error "WRONG CHOICE OF Data Order!"
	#endif  
	
}
u8 			SPI_Receive(void)
{
    while((GET_BIT(SPSR, 7))==0);
	return SPDR;
	
}

void 		SPI_Transmit(u8 Data)
{
	SPDR = Data;
	while((GET_BIT(SPSR, 7))==0);
}

void		SPI_SendString(u8 *str)
{
	u8 i = 0 ;
	
	while(str[i] != '\0')
	{
		SPI_Transmit(str[i]);
		i++;
	}

}