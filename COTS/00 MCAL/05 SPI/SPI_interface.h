#ifndef 		SPI_INTERFACE_H
#define 		SPI_INTERFACE_H

void 		SPI_Init(void);
u8 			SPI_Receive(void);
void 		SPI_Transmit(u8 Data);
void		SPI_SendString(u8 *str);
u8 *		SPI_ReceiveString(void);

#endif