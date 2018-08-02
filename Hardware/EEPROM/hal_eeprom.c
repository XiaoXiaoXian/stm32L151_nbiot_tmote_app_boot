/**
  *********************************************************************************************************
  * @file    hal_eeprom.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-11-01
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "hal_eeprom.h"


/**********************************************************************************************************
 @Function			void EEPROM_ReadBytes(u16 addr, u8 *buf, u16 length)
 @Description			��EEPROM�ж���length�ֽ�����(ƫ�Ƶ�ַ�谴4�ֽڶ���)
 @Input				void
 @Return				addr   : ��������EEPROMƫ�Ƶ�ַ
					*buf   : ���������ݵ�ַ
					length : �����ֽ���
**********************************************************************************************************/
void EEPROM_ReadBytes(u16 addr, u8 *buf, u16 length)
{
	u8 *wAddr;
	
	wAddr = (u8 *)(EEPROM_BASE_ADDR + addr);
	while (length--) {
		*buf++ = *wAddr++;
	}
}

/**********************************************************************************************************
 @Function			void EEPROM_WriteBytes(u16 addr, u8 *buf, u16 length)
 @Description			д��EEPROM��length�ֽ�����(ƫ�Ƶ�ַ�谴4�ֽڶ���)
 @Input				void
 @Return				addr   : д������EEPROMƫ�Ƶ�ַ
					*buf   : ��д�����ݵ�ַ
					length : д���ֽ���
**********************************************************************************************************/
void EEPROM_WriteBytes(u16 addr, u8 *buf, u16 length)
{
	u16 i = 0;
	
	EEPROM_ENTER_CRITICAL_SECTION();

	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	for (i = 0; i < length; i++) {
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, EEPROM_BASE_ADDR + addr + i, *(buf + i));
	}
	HAL_FLASHEx_DATAEEPROM_Lock();
	
	EEPROM_EXIT_CRITICAL_SECTION();
}

/**********************************************************************************************************
 @Function			void EEPROM_EnterCriticalSection(void)
 @Description			����ؼ�����,�ر��ж�,�ȴ��жϽ�������
 @Input				void
 @Return				void
**********************************************************************************************************/
void EEPROM_EnterCriticalSection(void)
{
	__disable_irq();
}

/**********************************************************************************************************
 @Function			void EEPROM_ExitCriticalSection(void)
 @Description			�˳��ؼ�����,�����ж�
 @Input				void
 @Return				void
**********************************************************************************************************/
void EEPROM_ExitCriticalSection(void)
{
	__enable_irq();
}

/********************************************** END OF FLEE **********************************************/
