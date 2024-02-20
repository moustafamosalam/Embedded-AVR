#ifndef 		I2C_INTERFACE_H
#define 		I2C_INTERFACE_H

/*
Error Status
*/

typedef enum
{
	I2C_OK,
	I2C_SC_Error,
	I2C_RSC_Error,
	I2C_MT_SLA_W_Error,
	I2C_MT_SLA_R_Error,
	I2C_MT_DATA_Error,
	I2C_MR_DATA_Error,
	
}I2C_Error_State 

void 				I2C_MasterInit(void);
void 	 			I2C_SlaveInit(u8 SLA);
I2C_Error_State 	I2C_Start_Condition(void);
I2C_Error_State 	I2C_Repeated_Start(void);
I2C_Error_State 	I2C_SendSlaveAddress_Write(u8 SLA);
I2C_Error_State 	I2C_SendSlaveAddress_Read(u8 SLA);
I2C_Error_State 	I2C_Send_Data(u8 Data);
I2C_Error_State 	I2C_Read_Data(u8 * data);
void  				I2C_Stop_Condition(void);

#endif