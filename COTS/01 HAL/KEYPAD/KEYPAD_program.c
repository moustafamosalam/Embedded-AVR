#include "STD_TYPES.h"
#include "Dio_interface.h"
#include "KEYPAD_interface.h"
#include <util/delay.h>

const u8 key[4][4] = { { '7' , '8' , '9' , '.'} ,  
                       { '4' , '5' , '6' , '*'} ,
					   { '1' , '2' , '3' , '-'} ,						
					   { '/' , '0' , '=' , '+'} };
					   


u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8Key = 0xff ;
	DIO_voidSetPortDirection(KEYPAD_PORT , 0x0f) ;
	DIO_voidSetPortValue(KEYPAD_PORT , 0xff) ;
	u8 Col ;
	for(Col = 0 ; Col<4 ; Col++)
	{
		/*  		Col Activated (Pattern) 		*/
		DIO_voidSetPinValue(KEYPAD_PORT , Col , LOW);
	    u8 Row;
	for(Row = 4 ; Row < 8 ; Row++ )	
	{
		if((DIO_u8GetPinValue(KEYPAD_PORT,Row))==0)
		{
			Local_u8Key = key[Col][Row-4];
			_delay_ms(5);
		}
	}
	    /*			Col Deactivated (Pattern)	    */
	    DIO_voidSetPinValue(KEYPAD_PORT , Col , HIGH);
	}	
	return Local_u8Key ;
}
