#ifndef __RADER_DAC_H
#define   __RADER_DAC_H

#include "sys.h"


#define DACx							DAC
#define DACx_CHANNEL_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define DACx_CHANNEL_GPIO_CLK_DISABLE()		__HAL_RCC_DAC_CLK_DISABLE()
#define DACx_CLK_ENABLE()				__HAL_RCC_DAC_CLK_ENABLE()
#define DACx_FORCE_RESET()				__HAL_RCC_DAC_FORCE_RESET()
#define DACx_RELEASE_RESET()				__HAL_RCC_DAC_RELEASE_RESET()

/* ����DACͨ������ */
#define DACx_CHANNEL_PIN					GPIO_PIN_4
#define DACx_CHANNEL_GPIO_PORT			GPIOA

#define DACx_DMAx_CHANNELn				DMA1_Channel2
#define DACx_DMAx_CHANNELn_IRQn			DMA1_Channel2_IRQn
#define DACx_DMAx_CHANNELn_IRQHANDLER		DMA1_Channel2_IRQHandler

/* ����DACͨ�� */
#define DACx_CHANNEL					DAC_CHANNEL_1


extern DAC_HandleTypeDef 				DAC_Handler;						//DAC���

void Rader_DAC_Init(void);												//�״�DAC��ʼ��
void Rader_DAC_DeInit(void);												//�״�DAC��λ

#endif
