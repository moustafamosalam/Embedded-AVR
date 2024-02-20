#ifndef		EXTI_INTERFAC_H
#define		EXTI_INTERFAC_H

void EXTI_voidInit(void);
void EXTI0_voidEnable(void);
void EXTI0_voidDisable(void);

void GIE_voidEnable(void);
void GIE_voidDisable(void);

void EXTI0_voidSetCallBack(void (*pf)(void));
#endif