/**
  *********************************************************************************************************
  * @file    sys.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-23
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "sys.h"


/**********************************************************************************************************
 @Function			void Stm32_Clock_Init(u32 pllmul, u32 plldiv)
 @Description			ʱ�����ú���(MAX32MHz)
 @Input				pllmul	: ��PLL��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:0 ~ 48
					plldiv	: ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2,3,4.(������3��ֵ!)
 @Return				void
 @attention			Fsys = Fs*(pllmul/plldiv);

					Fsys : ϵͳʱ��Ƶ��
					Fs	: PLL����ʱ��Ƶ��,������HSI,HSE��
**********************************************************************************************************/
void Stm32_Clock_Init(u32 pllmul, u32 plldiv)
{
	HAL_StatusTypeDef ret = HAL_OK;
	RCC_OscInitTypeDef RCC_OscInitStructure;
	RCC_ClkInitTypeDef RCC_ClkInitStructure;
	HAL_RCC_DeInit();

	RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSI;				//ʱ��ԴΪHSI
	RCC_OscInitStructure.HSIState = RCC_HSI_ON;								//��HSI
	RCC_OscInitStructure.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStructure.PLL.PLLState = RCC_PLL_ON;							//��PLL
	RCC_OscInitStructure.PLL.PLLSource = RCC_PLLSOURCE_HSI;					//PLLʱ��Դѡ��HSI
	RCC_OscInitStructure.PLL.PLLMUL = pllmul;								//��PLL��Ƶϵ��(PLL��Ƶ)
	RCC_OscInitStructure.PLL.PLLDIV = plldiv;								//ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ)
	ret = HAL_RCC_OscConfig(&RCC_OscInitStructure);							//��ʼ��
	if (ret != HAL_OK) while(1);
	
	__HAL_RCC_PWR_CLK_ENABLE();											//ʹ��PWRʱ��
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);				//���õ�ѹ�������ѹ����, �Ա�������δ�����Ƶ�ʹ���
	while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

	/* ѡ��PLL��Ϊϵͳʱ��Դ��������HCLK, PCLK1 �� PCLK2 */
	RCC_ClkInitStructure.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStructure.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;				//����ϵͳʱ��ʱ��ԴΪPLL
	RCC_ClkInitStructure.AHBCLKDivider = RCC_SYSCLK_DIV1;						//AHB��Ƶϵ��Ϊ1
	RCC_ClkInitStructure.APB1CLKDivider = RCC_HCLK_DIV1;						//APB1��Ƶϵ��Ϊ1
	RCC_ClkInitStructure.APB2CLKDivider = RCC_HCLK_DIV1;						//APB2��Ƶϵ��Ϊ1

	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_1);			//ͬʱ����FLASH��ʱ����Ϊ1WS, Ҳ����2��CPU����
	if (ret != HAL_OK) while(1);
}


#ifdef  USE_FULL_ASSERT
/**********************************************************************************************************
 @Function			void assert_failed(uint8_t* file, uint32_t line)
 @Description			��������ʾ�����ʱ��˺����������������ļ���������
 @Input				file		: ָ��Դ�ļ�
					line		: ָ�����ļ��е�����
 @Return				void
**********************************************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
	while (1)
	{
	}
}
#endif

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//���������ж�
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

/********************************************** END OF FLEE **********************************************/
