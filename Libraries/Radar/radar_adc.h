#ifndef __RADER_ADC_H
#define   __RADER_ADC_H

#include "sys.h"


extern __IO uint16_t ADC_ConvertedValue;

extern ADC_HandleTypeDef			ADC_Handler;								//ADC���
extern DMA_HandleTypeDef			ADC_DMA_Handler;							//ADC DMA���

void Rader_ADC_Init(void);												//�״�ADC��ʼ��
void Rader_ADC_DeInit(void);												//�״�ADC��λ

#endif
