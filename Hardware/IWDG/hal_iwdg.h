#ifndef __HAL_IWDG_H
#define   __HAL_IWDG_H

#include "sys.h"


void IWDG_Init(u8 prer, u16 rlr);											//��ʼ���������Ź�
void IWDG_Feed(void);													//ι�������Ź�

#endif
