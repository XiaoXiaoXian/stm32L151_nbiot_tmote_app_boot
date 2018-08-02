#ifndef __HAL_RTC_H
#define   __HAL_RTC_H

#include "sys.h"
#include <time.h>


extern RTC_HandleTypeDef RTC_Handler;										//RTC���

struct tm Time_ConvUnixToCalendar(time_t t);									//ת��UNIXʱ���Ϊ����ʱ��
time_t Time_ConvCalendarToUnix(struct tm t);									//ת������ʱ��ʱ���ΪUNIX

u8 RTC_Init(void);														//RTC��ʼ��
HAL_StatusTypeDef RTC_Set_Time(u8 hour, u8 min, u8 sec);						//RTCʱ������
HAL_StatusTypeDef RTC_Set_Date(u8 year, u8 month, u8 date);						//RTC��������
void RTC_Set_AlarmA(u8 week, u8 hour, u8 min, u8 sec);							//��������ʱ��(����������,24Сʱ��)
void RTC_Set_WakeUp(u32 wksel, u16 cnt);									//�����Ի��Ѷ�ʱ������

#endif
