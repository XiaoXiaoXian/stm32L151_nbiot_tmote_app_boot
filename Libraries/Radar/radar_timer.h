#ifndef __RADER_TIMER_H
#define   __RADER_TIMER_H

#include "sys.h"


extern TIM_HandleTypeDef			Radar_TIM2_Handler;							//�״ﶨʱ��2���

void Radar_TIM2_Init(u16 arr, u16 psc);										//�״�ͨ�ö�ʱ��2�жϳ�ʼ��
void Radar_TIM2_DeInit(void);												//�״�ͨ�ö�ʱ��2�жϸ�λ

#endif
