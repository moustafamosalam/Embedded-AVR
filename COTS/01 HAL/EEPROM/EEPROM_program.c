
#include "EEPROM_interface.h"



void EEpromInit(void)
{
	I2C_Master_Init();
}



void EEpromWriteByte(unsigned short address, unsigned char data)
{
    I2C_Start_Condition();
	I2C_SendSlaveAddress_Write( 0b01010000 );
	I2C_Send_Data((unsigned char)address);
	I2C_Send_Data(data);
	I2C_Stop_Condition();
    return;
}

void E2PROM_WriteMultyByteOn(uint8 address, uint8 *data)
{
	uint8 i=0;
	I2C_Start_Condition();
	I2C_SendSlaveAddress_Write( 0b01010000);
	I2C_Send_Data((unsigned char)address);
	while(data[i] != '\0')
	{
		I2C_Send_Data(data[i]);
		i++;
	}
	I2C_Stop_Condition();
}


unsigned char EEpromReadByte(unsigned short address)
{
	unsigned char data;
	I2C_Start_Condition();
	I2C_SendSlaveAddress_Write( 0b01010000 );
    I2C_Send_Data((unsigned char)address);
	I2C_Repeated_Start();
	I2C_SendSlaveAddress_Read( 0b01010000  );
	data = I2C_Read_Data();
	I2C_Stop_Condition();
    return data;
}

uint8* E2PROM_ReadMultyByteFrom(uint8 address)
{
	uint8* data;
	uint8 i =0;
	I2C_Start_Condition();
	I2C_SendSlaveAddress_Write( 0b01010000 );
	I2C_Send_Data((unsigned char)address);

	I2C_Repeated_Start();
	I2C_SendSlaveAddress_Read( 0b01010000  );

    while(data[i] != '\0')
    {
	 data[i] = I2C_Read_Data();
     i++;
    }

	I2C_Stop_Condition();
	return data;
}
