#ifndef __SYS_H
#define   __SYS_H

#include "stm32l1xx.h"
#include "core_cm3.h"
#include "stm32l1xx_hal.h"


#define SYSTEM_SUPPORT_OS		0										//����ϵͳ�ļ����Ƿ�֧��OS 0:��֧��os 1:֧��os

#define ON					1
#define OFF					0


typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  

extern __IO uint32_t uwTick;


void Stm32_Clock_Init(u32 pllmul, u32 plldiv);								//����ϵͳʱ��

/* ����Ϊ��ຯ�� */
void WFI_SET(void);														//ִ��WFIָ��
void INTX_DISABLE(void);													//�ر������ж�
void INTX_ENABLE(void);													//���������ж�
void MSR_MSP(u32 addr);													//���ö�ջ��ַ

#define MODELPOWER(n)			(n?HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET):HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET))
#define RADERPOWER(n)			(n?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET))
#define NBIOTPOWER(n)			(n?HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET))


#endif
