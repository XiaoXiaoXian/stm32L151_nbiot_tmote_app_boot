#ifndef __USART_H
#define   __USART_H

#include "sys.h"
#include "stdio.h"


#define PRINTF_USART			USART1									//Printfʹ�ô���

#define ENTER_CRITICAL_SECTION()	Uart_EnterCriticalSection();
#define EXIT_CRITICAL_SECTION()	Uart_ExitCriticalSection();

#define USART1_REC_LEN			200										//����1�������ֽ���
#define USART2_REC_LEN			200										//����2�������ֽ���

#define USART1_RXBUFFERSIZE   	1 										//HAL��ʹ�õĴ��ڽ��ջ����С
#define USART2_RXBUFFERSIZE   	1 										//HAL��ʹ�õĴ��ڽ��ջ����С

extern u8 USART1_RX_BUF[USART1_REC_LEN];    									//USART1���ջ���,���USART1_REC_LEN���ֽ�
extern u8 USART2_RX_BUF[USART2_REC_LEN];    									//USART2���ջ���,���USART1_REC_LEN���ֽ�

extern u16 USART1_RX_STA;												//USART1����״̬��� bit15,������ɱ�־ bit14,���յ�0x0d(\n)
extern u16 USART2_RX_STA;												//USART2����״̬��� bit15,������ɱ�־ bit14,���յ�0x0d(\n)

extern u8 USART1_aRxBuffer[USART1_RXBUFFERSIZE];								//HAL��ʹ�õĴ��ڽ��ջ���
extern u8 USART2_aRxBuffer[USART2_RXBUFFERSIZE];								//HAL��ʹ�õĴ��ڽ��ջ���

extern UART_HandleTypeDef UART1_Handler;									//UART1���
extern UART_HandleTypeDef UART2_Handler;									//UART2���


void Uart1_Init(u32 bound);												//����1��ʼ��
void Uart2_Init(u32 bound);												//����2��ʼ��
void Uart1_PortSerialEnable(u8 xRxEnable, u8 xTxEnable);						//ʹ��/ʧ�� ����/���� �����ж�
void Uart2_PortSerialEnable(u8 xRxEnable, u8 xTxEnable);						//ʹ��/ʧ�� ����/���� �����ж�

void Uart_EnterCriticalSection(void);										//����ؼ�����,�ر��ж�,�ȴ��жϽ�������
void Uart_ExitCriticalSection(void);										//�˳��ؼ�����,�����ж�

#endif
