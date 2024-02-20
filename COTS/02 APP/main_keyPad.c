#include	 "STD_TYPES.h"
#include 	 "DIO_interface.h"


int main(void)
{
    DIO_voidSetPortDirection(PORTA,0xFF);
	DIO_voidSetPinDirection(PORTB,PIN1,OUTPUT);
	DIO_voidSetPinDirection(PORTB,PIN2,OUTPUT);
	DIO_voidSetPinDirection(PORTB,PIN3,OUTPUT);
    LCD_init();
	u8 Local_u8Data = 0xff;
	while(1)
	{
		Local_u8Data = KPD_u8GetPressedKey();
		if(Local_u8Data != 0xff)
		{
			LCD_voidWriteChar(Local_u8Data);
		}	
	}
}