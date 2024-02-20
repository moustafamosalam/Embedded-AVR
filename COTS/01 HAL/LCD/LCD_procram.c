#include		"STD_TYPES.h"
#include		"DIO_interface.h"
#include 		"LCD_interface.h"
#include		<util/delay.h> 
#define		FONT_5X7_2_LINES		0x38

void LCD_init(void) {

/*  _delay_ms(35);  //delay
LCD_SendCMD(FONT_5X7_2_LINES); // 2 LINES and FONT 5x7
_delay_ms(1);
LCD_SendCMD(0x0C); //Cursor OFF and Blinking OFF
_delay_ms(1);
LCD_SendCMD(0x01); //Clear Display
_delay_ms(2);
LCD_SendCMD(0x06); //Dislay is increased */


_delay_ms(100);
//send commands to LCD for initializing as 4-bit mode/
LCD_SendCMD4(0x33);
LCD_SendCMD4(0x32);
LCD_SendCMD4(0x28);

LCD_SendCMD4(0x0C);
LCD_SendCMD4(0x01);
LCD_SendCMD4(0x06);
LCD_SendCMD4(0x02);
}

void	LCD_WriteChar(u8 Data)
{
	DIO_voidSetPinValue(CONTROL_PORT,LCD_RS,HIGH);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_RW,LOW);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,HIGH);
	_delay_ms(5);
	DIO_voidSetPortValue(DATA_PORT,Data);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,LOW);
	_delay_ms(5);
	
}

void	LCD_SendCMD(u8 CMD)
{
	DIO_voidSetPinValue(CONTROL_PORT,LCD_RS,LOW);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_RW,LOW);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,HIGH);
	_delay_ms(5);
	DIO_voidSetPortValue(DATA_PORT,CMD);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,LOW);
	_delay_ms(5);
	
}

void LCD_SendCMD4(u8 cmd)
{
	DIO_voidSetPinValue(CONTROL_PORT,LCD_RS,LOW);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_RW,LOW);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,HIGH);
	_delay_ms(5);
	

	u8 Dummy = (cmd & 0xf0) | (PORTA & 0x0f);
	DIO_voidSetPortValue(DATA_PORT,Dummy);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,LOW);
	_delay_ms(5);
	
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,HIGH);
	_delay_ms(5);
	
	Dummy = (cmd << 4) | (PORTA & 0x0f);
	DIO_voidSetPortValue(DATA_PORT,Dummy);
	DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,LOW);
	_delay_ms(5);
}

void LCD_WriteChar4(u8 Data)
{
	

DIO_voidSetPinValue(CONTROL_PORT,LCD_RS,HIGH);
DIO_voidSetPinValue(CONTROL_PORT,LCD_RW,LOW);
DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,HIGH);
_delay_ms(5);


u8 Dummy = (Data & 0xf0) | (PORTA & 0x0f);
DIO_voidSetPortValue(DATA_PORT,Dummy);
DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,LOW);
_delay_ms(5);


DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,HIGH);
Dummy = (Data << 4) | (PORTA & 0x0f);
DIO_voidSetPortValue(DATA_PORT,Dummy);
_delay_ms(5);
DIO_voidSetPinValue(CONTROL_PORT,LCD_EN,LOW);
_delay_ms(5);
}

void LCD_GOTOXY(u8 LINE_NUM,u8 POSITION)
{
	
	if((LINE_NUM ==0) && (POSITION<16))
	{
		LCD_SendCMD4((0x80 + POSITION));
			}
			else if ((LINE_NUM ==1) && (POSITION<16))
			{
		
		LCD_SendCMD4((0xC0 + POSITION));
			}

}

void LCD_WriteSTring(u8 * ptr)
{
	u8 i = 0 ;
	
	while(ptr[i] != '\0')
	{
		LCD_WriteChar4(ptr[i]);
		i++;
	}

}