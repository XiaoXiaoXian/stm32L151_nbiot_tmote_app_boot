/**
  *********************************************************************************************************
  * @file    usart.c
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

#include "usart.h"


u8 USART1_RX_BUF[USART1_REC_LEN];    										//USART1���ջ���,���USART1_REC_LEN���ֽ�
u8 USART2_RX_BUF[USART2_REC_LEN];    										//USART2���ջ���,���USART1_REC_LEN���ֽ�

u16 USART1_RX_STA = 0;													//USART1����״̬��� bit15,������ɱ�־ bit14,���յ�0x0d(\n)
u16 USART2_RX_STA = 0;													//USART2����״̬��� bit15,������ɱ�־ bit14,���յ�0x0d(\n)

u8 USART1_aRxBuffer[USART1_RXBUFFERSIZE];									//HAL��ʹ�õĴ��ڽ��ջ���
u8 USART2_aRxBuffer[USART2_RXBUFFERSIZE];									//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART1_Handler;											//UART1���
UART_HandleTypeDef UART2_Handler;											//UART2���

/**********************************************************************************************************
 @Function			void Uart1_Init(u32 bound)
 @Description			����1��ʼ��
 @Input				void
 @Return				void
**********************************************************************************************************/
//void Uart1_Init(u32 bound)
//{
//	UART1_Handler.Instance = USART1;										//USART1
//	UART1_Handler.Init.BaudRate = bound;									//������
//	UART1_Handler.Init.WordLength = UART_WORDLENGTH_8B;						//�ֳ�Ϊ8λ���ݸ�ʽ
//	UART1_Handler.Init.StopBits = UART_STOPBITS_1;							//һ��ֹͣλ
//	UART1_Handler.Init.Parity = UART_PARITY_NONE;							//����żУ��λ
//	UART1_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;						//��Ӳ������
//	UART1_Handler.Init.Mode = UART_MODE_TX_RX;								//�շ�ģʽ
//	HAL_UART_Init(&UART1_Handler);										//HAL_UART_Init()��ʹ��UART1
//	
//	/* �ú����Ὺ�������ж�: ��־λUART_IT_RXNE, �������ý��ջ����Լ����ջ��������������� */
//	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)USART1_aRxBuffer, USART1_RXBUFFERSIZE);
//}

/**********************************************************************************************************
 @Function			void Uart2_Init(u32 bound)
 @Description			����2��ʼ��
 @Input				void
 @Return				void
**********************************************************************************************************/
//void Uart2_Init(u32 bound)
//{
//	UART2_Handler.Instance = USART2;										//USART2
//	UART2_Handler.Init.BaudRate = bound;									//������
//	UART2_Handler.Init.WordLength = UART_WORDLENGTH_8B;						//�ֳ�Ϊ8λ���ݸ�ʽ
//	UART2_Handler.Init.StopBits = UART_STOPBITS_1;							//һ��ֹͣλ
//	UART2_Handler.Init.Parity = UART_PARITY_NONE;							//����żУ��λ
//	UART2_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;						//��Ӳ������
//	UART2_Handler.Init.Mode = UART_MODE_TX_RX;								//�շ�ģʽ
//	HAL_UART_Init(&UART2_Handler);										//HAL_UART_Init()��ʹ��UART2
//	
//	/* �ú����Ὺ�������ж�: ��־λUART_IT_RXNE, �������ý��ջ����Լ����ջ��������������� */
//	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)USART2_aRxBuffer, USART2_RXBUFFERSIZE);
//}

/**********************************************************************************************************
 @Function			void HAL_UART_MspInit(UART_HandleTypeDef *huart)
 @Description			UART�ײ��ʼ��, ʱ��ʹ��, ��������, �ж�����
					�˺����ᱻHAL_UART_Init()����
					USART1_TX : PA9
					USART1_RX : PA10
					USART2_TX : PA2
					USART2_RX : PA3
 @Input				huart:���ھ��
 @Return				void
**********************************************************************************************************/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if (huart->Instance == USART1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();										//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();									//ʹ��USART1ʱ��
		
		GPIO_Initure.Pin = GPIO_PIN_9 | GPIO_PIN_10;							//PA9|PA10
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;								//�����������
		GPIO_Initure.Pull = GPIO_PULLUP;									//����
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;							//����
		GPIO_Initure.Alternate = GPIO_AF7_USART1;							//����Ϊ����1
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);								//��ʼ��PA9|PA10
		
		HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);							//��ռ���ȼ�1, �����ȼ�0
		HAL_NVIC_EnableIRQ(USART1_IRQn);									//ʹ��USART1�ж�ͨ��
	}
	
	if (huart->Instance == USART2)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();										//ʹ��GPIOAʱ��
		__HAL_RCC_USART2_CLK_ENABLE();									//ʹ��USART2ʱ��
		
		GPIO_Initure.Pin = GPIO_PIN_2 | GPIO_PIN_3;							//PA2|PA3
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;								//�����������
		GPIO_Initure.Pull = GPIO_PULLUP;									//����
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;							//����
		GPIO_Initure.Alternate = GPIO_AF7_USART2;							//����Ϊ����2
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);								//��ʼ��PA2|PA3
		
		HAL_NVIC_SetPriority(USART2_IRQn, 1, 1);							//��ռ���ȼ�1, �����ȼ�1
		HAL_NVIC_EnableIRQ(USART2_IRQn);									//ʹ��USART2�ж�ͨ��
	}
}

/**********************************************************************************************************
 @Function			void Uart1_PortSerialEnable(u8 xRxEnable, u8 xTxEnable)
 @Description			ʹ��/ʧ�� ����/���� �����ж�
 @Input				xRxEnable : 1 ENABLE
							  0 DISABLE
					xTxEnable : 1 ENBALE
							: 0 DISABLE
 @Return				void
**********************************************************************************************************/
void Uart1_PortSerialEnable(u8 xRxEnable, u8 xTxEnable)
{
	ENTER_CRITICAL_SECTION();
	
	if (xRxEnable) {													//ʹ�ܴ��ڽ����ж�
		__HAL_USART_ENABLE_IT(&UART1_Handler, UART_IT_RXNE);
	}
	else {															//ʧ�ܴ��ڽ����ж�
		__HAL_USART_DISABLE_IT(&UART1_Handler, UART_IT_RXNE);
	}
	
	if (xTxEnable) {													//ʹ�ܴ��ڷ����ж�
		__HAL_USART_ENABLE_IT(&UART1_Handler, UART_IT_TXE);
	}
	else {															//ʧ�ܴ��ڷ����ж�
		__HAL_USART_DISABLE_IT(&UART1_Handler, UART_IT_TXE);
	}
	
	EXIT_CRITICAL_SECTION();
}

/**********************************************************************************************************
 @Function			void Uart2_PortSerialEnable(u8 xRxEnable, u8 xTxEnable)
 @Description			ʹ��/ʧ�� ����/���� �����ж�
 @Input				xRxEnable : 1 ENABLE
							  0 DISABLE
					xTxEnable : 1 ENBALE
							: 0 DISABLE
 @Return				void
**********************************************************************************************************/
void Uart2_PortSerialEnable(u8 xRxEnable, u8 xTxEnable)
{
	ENTER_CRITICAL_SECTION();
	
	if (xRxEnable) {													//ʹ�ܴ��ڽ����ж�
		__HAL_USART_ENABLE_IT(&UART2_Handler, UART_IT_RXNE);
	}
	else {															//ʧ�ܴ��ڽ����ж�
		__HAL_USART_DISABLE_IT(&UART2_Handler, UART_IT_RXNE);
	}
	
	if (xTxEnable) {													//ʹ�ܴ��ڷ����ж�
		__HAL_USART_ENABLE_IT(&UART2_Handler, UART_IT_TXE);
	}
	else {															//ʧ�ܴ��ڷ����ж�
		__HAL_USART_DISABLE_IT(&UART2_Handler, UART_IT_TXE);
	}
	
	EXIT_CRITICAL_SECTION();
}

/**********************************************************************************************************
 @Function			void Uart_EnterCriticalSection(void)
 @Description			����ؼ�����,�ر��ж�,�ȴ��жϽ�������
 @Input				void
 @Return				void
**********************************************************************************************************/
void Uart_EnterCriticalSection(void)
{
	__disable_irq();
}

/**********************************************************************************************************
 @Function			void Uart_ExitCriticalSection(void)
 @Description			�˳��ؼ�����,�����ж�
 @Input				void
 @Return				void
**********************************************************************************************************/
void Uart_ExitCriticalSection(void)
{
	__enable_irq();
}

#if 1
#pragma import(__use_no_semihosting)

struct __FILE
{
	int handle;
};

FILE __stdout;

void _sys_exit(int x)
{
	x = x;
}

int fputc(int ch, FILE *f)
{
	while ((PRINTF_USART->SR & 0X40) == 0);
	PRINTF_USART->DR = (u8) ch;
	return ch;
}
#endif 

/********************************************** END OF FLEE **********************************************/
