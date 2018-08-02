/****************************************Copyright (c)****************************************************
**                         SHENZHEN DECARD TECHNOLOGIES Co.,LTD.                               
**                                     
**                               http://www.decard.com
**
**--------------File Info---------------------------------------------------------------------------------
** Create by:			ck
** Create date:			2012-07-12
** Version:             0.1
** Descriptions:		bootloader����
*********************************************************************************************************/
#include "stm32l1xx_hal.h"
#include "boot.h"
//#include "iap.h"
typedef  void (*pFunction)(void);



/**
  * @brief  ���Ƴ�����ת��ָ��λ�ÿ�ʼִ�� ��
  * @param  Addr ����ִ�е�ַ��
  * @retval ������ת״̬��
  */
//uint32_t test_addr[2];
uint8_t JumpToApplication(uint32_t Addr)
{
	pFunction Jump_To_Application;
	__IO uint32_t JumpAddress; 
	uint32_t firmfirtword = (*(__IO uint32_t*)Addr);
	//test_addr[0] = Addr;
	__NOP();
	/* Test if user code is programmed starting from address "ApplicationAddress" */
	if (( firmfirtword & 0x2FF00000 ) == 0x20000000)
	{ 
		
	  /* Jump to user application */
	  JumpAddress = *(__IO uint32_t*) (Addr + 4);
	  //test_addr[1] = JumpAddress;
	  Jump_To_Application = (pFunction) JumpAddress;

		
	  /* Initialize user application's Stack Pointer */
	  __set_MSP(*(__IO uint32_t*) Addr);
		//__set_MSP(0x20000CB0);
	  Jump_To_Application();
	}
	return 1;
}

void boot_from_flash(unsigned int app_address)
{
	// �ж� �̼��Ƿ�����
	HAL_FLASH_Lock();
	JumpToApplication(app_address);
}
