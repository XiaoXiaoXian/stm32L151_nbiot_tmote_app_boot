#ifndef __RADER_API_H
#define   __RADER_API_H

#include "sys.h"



void Rader_Init(void);													//�״��ʼ��
void Rader_InitBG(void);													//�״��ʼ������ֵ
u8   Rader_GetData(u8 dataNum);											//��ȡ�״�����

void Rader_RunTest(void);												//�״����в���
void Rader_Get_Sample(void);												//�״����
void Rader_Get_Sample_Time(void);											//�״��������

#endif
