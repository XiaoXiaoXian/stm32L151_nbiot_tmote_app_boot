/**
  *********************************************************************************************************
  * @file    hal_rtc.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-24
  * @brief   HAL RTC Device
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "hal_rtc.h"


RTC_HandleTypeDef RTC_Handler;											//RTC���

/**********************************************************************************************************
 @Function			u8 RTC_Init(void)
 @Description			RTC��ʼ��
 @Input				void
 @Return				0 : ��ʼ���ɹ�
					2 : �����ʼ��ģʽʧ��
**********************************************************************************************************/
u8 RTC_Init(void)
{
	RTC_Handler.Instance = RTC;
	RTC_Handler.Init.HourFormat = RTC_HOURFORMAT_24;							//RTC����Ϊ24Сʱ��ʽ
	RTC_Handler.Init.AsynchPrediv = 0X7F;									//RTC�첽��Ƶϵ��(1~0X7F)
	RTC_Handler.Init.SynchPrediv = 0XFF;									//RTCͬ����Ƶϵ��(0~7FFF)
	RTC_Handler.Init.OutPut = RTC_OUTPUT_DISABLE;
	RTC_Handler.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	RTC_Handler.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&RTC_Handler) != HAL_OK) return 2;
	
	if (HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR0) != 0X5050)				//�Ƿ��һ������
	{
		//RTC_Set_Time(12, 10, 00);										//����ʱ��
		//RTC_Set_Date(17, 11, 8);											//��������
		HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR0, 0X5050);				//����Ѿ���ʼ������
	}
	
	return 0;
}

/**********************************************************************************************************
 @Function			HAL_StatusTypeDef RTC_Set_Time(u8 hour, u8 min, u8 sec)
 @Description			RTCʱ������
 @Input				hour, min, sec : Сʱ, ����, ����
					ampm 		: RTC_HOURFORMAT12_AM / RTC_HOURFORMAT12_PM
 @Return				SUCEE(1) : �ɹ�
					ERROR(0) : �����ʼ��ģʽʧ��
**********************************************************************************************************/
HAL_StatusTypeDef RTC_Set_Time(u8 hour, u8 min, u8 sec)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	
	RTC_TimeStructure.Hours = hour;
	RTC_TimeStructure.Minutes = min;
	RTC_TimeStructure.Seconds = sec;
	RTC_TimeStructure.TimeFormat = (hour < 12)?RTC_HOURFORMAT12_AM:RTC_HOURFORMAT12_PM;
	RTC_TimeStructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	RTC_TimeStructure.StoreOperation = RTC_STOREOPERATION_RESET;
	return HAL_RTC_SetTime(&RTC_Handler, &RTC_TimeStructure, RTC_FORMAT_BIN);
}

/**********************************************************************************************************
 @Function			HAL_StatusTypeDef RTC_Set_Date(u8 year, u8 month, u8 date)
 @Description			RTC��������
 @Input				year, month, date 	: ��(0~99), ��(1~12), ��(0~31)
					week 			: ����(1~7,0,�Ƿ�!)
 @Return				SUCEE(1) : �ɹ�
					ERROR(0) : �����ʼ��ģʽʧ��
**********************************************************************************************************/
HAL_StatusTypeDef RTC_Set_Date(u8 year, u8 month, u8 date)
{
	u8 week;
	RTC_DateTypeDef RTC_DateStructure;
	
	RTC_DateStructure.Date = date;
	RTC_DateStructure.Month = month;
	RTC_DateStructure.Year = year;
	
	if (month == 1 || month == 2) {
          month += 12;
          year--;
     }
	
	week = (date+2*month+3*(month+1)/5+year+year/4-year/100+year/400+1)%7;
     RTC_DateStructure.WeekDay = (week == 0) ? 7 : week;
	
	return HAL_RTC_SetDate(&RTC_Handler, &RTC_DateStructure, RTC_FORMAT_BIN);
}

/**********************************************************************************************************
 @Function			struct tm Time_ConvUnixToCalendar(time_t t)
 @Description			ת��UNIXʱ���Ϊ����ʱ��
 @Input				��ǰʱ���UNIXʱ���
 @Return				struct tm
**********************************************************************************************************/
struct tm Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;												//localtimeת�������tm_year�����ֵ, ��Ҫת�ɾ���ֵ
	
	return *t_tm;
}

/**********************************************************************************************************
 @Function			time_t Time_ConvCalendarToUnix(struct tm t)
 @Description			д��RTCʱ�ӵ�ǰʱ��
 @Input				struct tm t
 @Return				time_t
**********************************************************************************************************/
time_t Time_ConvCalendarToUnix(struct tm t)
{
	t.tm_year += 100;													//�ⲿtm�ṹ��洢�����Ϊ20xx��ʽ,����2017�꼴17
																	//��time.h�ж������ݸ�ʽΪ1900�꿪ʼ�����
																	//����,������ת��ʱҪ���ǵ��������
	return mktime(&t);
}

/**********************************************************************************************************
 @Function			void RTC_Set_AlarmA(u8 week, u8 hour, u8 min, u8 sec)
 @Description			��������ʱ��(����������,24Сʱ��)
 @Input				week, hour, min, sec : ���ڼ�(1~7), Сʱ, ����, ����
 @Return				void
**********************************************************************************************************/
void RTC_Set_AlarmA(u8 week, u8 hour, u8 min, u8 sec)
{
	RTC_AlarmTypeDef RTC_AlarmStructure;
	
	RTC_AlarmStructure.AlarmTime.Hours = hour;
	RTC_AlarmStructure.AlarmTime.Minutes = min;
	RTC_AlarmStructure.AlarmTime.Seconds = sec;
	RTC_AlarmStructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
	
	RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_NONE;						//��ȷƥ������, ʱ����
	RTC_AlarmStructure.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;		//������
	RTC_AlarmStructure.AlarmDateWeekDay = week;								//����
	RTC_AlarmStructure.Alarm = RTC_ALARM_A;									//����A
	
	HAL_RTC_SetAlarm_IT(&RTC_Handler, &RTC_AlarmStructure, RTC_FORMAT_BIN);
	HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0x02, 0x01);							//��ռ���ȼ�2, �����ȼ�1
	HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

/**********************************************************************************************************
 @Function			void RTC_Set_WakeUp(u32 wksel, u16 cnt)
 @Description			�����Ի��Ѷ�ʱ������
 @Input				wksel : @ ref RTCEx_Wakeup_Timer_Definitions : 
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV16        ((uint32_t)0x00000000)
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV8         ((uint32_t)0x00000001)
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV4         ((uint32_t)0x00000002)
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV2         ((uint32_t)0x00000003)
							#define RTC_WAKEUPCLOCK_CK_SPRE_16BITS      ((uint32_t)0x00000004)
							#define RTC_WAKEUPCLOCK_CK_SPRE_17BITS      ((uint32_t)0x00000006)
					cnt   : �Զ���װ��ֵ ����0, �����ж�
 @Return				void
**********************************************************************************************************/
void RTC_Set_WakeUp(u32 wksel, u16 cnt)
{
	__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RTC_Handler, RTC_FLAG_WUTF);				//���RTC WAKE UP�ı�־
	
	HAL_RTCEx_SetWakeUpTimer_IT(&RTC_Handler, cnt, wksel);						//������װ��ֵ��ʱ��
	
	HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0x02, 0x02);							//��ռ���ȼ�2,�����ȼ�2s
	HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

/********************************************** END OF FLEE **********************************************/
