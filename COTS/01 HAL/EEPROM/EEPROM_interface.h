

#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C_interface.h"

void EEpromInit(void);
void EEpromWriteByte(unsigned short address, unsigned char data);
void E2PROM_WriteMultyByteOn(uint8 Block_addr, uint8 *data);
unsigned char EEpromReadByte(unsigned short address);
uint8* E2PROM_ReadMultyByteFrom(uint8 address);
 
#endif








