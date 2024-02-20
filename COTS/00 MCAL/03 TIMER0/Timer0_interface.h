#ifndef 		TIMER0_INTERFACE_H
#define		TIMER0_INTERFACE_H

void 	TIMER0_voidInit(void);

void 	TIMER0_voidDisableOFInt(void); 	
void 	TIMER0_voidDisableCTCInt(void);

void 	TIMER0_voidEnableOFInt(void); 	
void 	TIMER0_voidEnableCTCInt(void);

void 	TIMER0_voidSetTCNT0(u8 Val);
void 	TIMER0_voidSetOCR0(u8 Val);

void 	Timer0_voidSetCallBackOF(void(*Copy_PF)(void));
void 	Timer0_voidSetCallBackCTC(void(*Copy_PF)(void));

void 	__vector_10 (void) __attribute__((signal,used));
void 	__vector_11 (void) __attribute__((signal,used));

#endif