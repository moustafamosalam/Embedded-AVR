#ifndef 		USART_INTERACE_H
#define 		USART_INTERACE_H

void  		USART_Init(void);
u8  		USART_ReceiveByte(void);
void  		USART_SendByte(u8 Byte);
void 		USART_SendString(u8 * str);
u8 *	 	USART_ReceiveString(void);

#endif