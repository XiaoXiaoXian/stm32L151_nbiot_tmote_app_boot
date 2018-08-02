#ifndef __HAL_EEPROM_H
#define   __HAL_EEPROM_H

#include "sys.h"


#define EEPROM_BASE_ADDR		0x08080000
#define EEPROM_BASE_ADDR1	0x0000
#define EEPROM_BASE_ADDR2	0x0200
#define EEPROM_BASE_ADDR3	0x0400
#define EEPROM_BASE_ADDR4	0x0600
#define EEPROM_BASE_ADDR5	0x0800
#define EEPROM_BASE_ADDR6	0x0A00
#define EEPROM_BASE_ADDR7	0x0C00
#define EEPROM_BASE_ADDR8	0x0E00
#define EEPROM_BYTE_SIZE		0x0FFF

#define EEPROM_ENTER_CRITICAL_SECTION()		EEPROM_EnterCriticalSection();
#define EEPROM_EXIT_CRITICAL_SECTION()		EEPROM_ExitCriticalSection();


void EEPROM_ReadBytes(u16 addr, u8 *buf, u16 length);							//��EEPROM�ж���length�ֽ�����
void EEPROM_WriteBytes(u16 addr, u8 *buf, u16 length);							//д��EEPROM��length�ֽ�����

void EEPROM_EnterCriticalSection(void);										//����ؼ�����,�ر��ж�,�ȴ��жϽ�������
void EEPROM_ExitCriticalSection(void);										//�˳��ؼ�����,�����ж�

#endif
