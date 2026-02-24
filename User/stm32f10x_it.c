/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "sys.h"         //包含需要的头文件
#include "bsp_usart.h"        //包含需要的头文件
#include "bsp_usart2.h"        //包含需要的头文件
 
#include "bsp_timer3.h"        //包含需要的头文件
#include "bsp_wifi.h" 
 
#include "bsp_sg90.h"
 
uint8_t UART_BUF;
uint8_t UART2_BUF;
uint8_t UART3_BUF;
uint8_t UART_RECEIVE_OK;
uint8_t CARD_ID_BUF[14];
uint8_t Recive_table[25];  		//用于接收wifi模块反馈到MCU上的数据  

unsigned int SystemTimer = 0;   //用于全局计时的变量           单位秒

extern uint8_t unlock_Time_en ;
extern uint16_t unlock_Time ;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/******************************************************************************/

// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
{
static uint8_t i=0;  
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		 UART_BUF = USART_ReceiveData(DEBUG_USARTx);  
		 	if(DEBUG_USARTx->DR){                                 								 								//处于指令配置状态时，非零值才保存到缓冲区	
			Usart1_RxBuff[Usart1_RxCounter]=DEBUG_USARTx->DR;                                   //保存到缓冲区	
			Usart1_RxCounter ++;                                                          //每接收1个字节的数据，Usart2_RxCounter加1，表示接收的数据总量+1 
			if(Usart1_RxCounter > USART1_RXBUFF_SIZE)Usart1_RxCounter = 0;
		}		
 
	}	 
}

/*-------------------------------------------------*/
/*函数名：串口2接收中断函数                        */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void USART2_IRQHandler(void)   
{                      
	if((USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) ){       //如果USART_IT_RXNE标志置位，表示有数据到了，且当前已没有经连接上服务器 进入if分支
		if(USART2->DR){                                 								 								//处于指令配置状态时，非零值才保存到缓冲区	
			Usart2_RxBuff[Usart2_RxCounter]=USART2->DR;                                   //保存到缓冲区	
			Usart2_RxCounter ++;                                                         
			if(Usart2_RxCounter > USART2_RXBUFF_SIZE)Usart2_RxCounter = 0;
		}		
	}	
 
} 
 
/*-------------------------------------------------*/
/*函数名：定时器3中断服务函数                      */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){   //如果TIM_IT_Update置位，表示TIM3溢出中断，进入if	
 
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);      //清除TIM3溢出中断标志 	
	}
}
/*-------------------------------------------------*/
/*函数名：定时器2中断服务函数                      */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM2_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){  //如果TIM_IT_Update置位，表示TIM2溢出中断，进入if	
		SystemTimer++;                                  //全局计时的变量+1,表示过去了1秒钟
		if(unlock_Time_en)unlock_Time++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);     //清除TIM2溢出中断标志 	
	}
}
/*-------------------------------------------------*/
/*函数名：定时器1中断服务函数                      */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM1_UP_IRQHandler(void)
{
	static uint8_t pwm = 0;
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET){  //如果TIM_IT_Update置位，表示TIM1溢出中断，进入if			
	pwm++;
	SystemTimer++;
		
	if(pwm >= 200) {pwm=0;}
		
	 
	  if(pwm <= Angle1) //舵机pwm控制
		 {
			 SERVO1_PIN_SET();
		 }else 
		 {
			 SERVO1_PIN_CLR();
		 }
//		  if(pwm <= Angle2) //舵机pwm控制
//		 {
//			 SERVO2_PIN_SET();
//		 }else 
//		 {                                                              
//			 SERVO2_PIN_CLR();
//		 }
//		  if(pwm <= Angle3) //舵机pwm控制
//		 {
//			 SERVO3_PIN_SET();
//		 }else 
//		 {
//			 SERVO3_PIN_CLR();
//		 }
//			if(pwm <= Angle4) //舵机pwm控制
//		 {
//			 SERVO4_PIN_SET();
//		 }else 
//		 {
//			 SERVO4_PIN_CLR();
//		 }
//		 if(pwm <= Angle5) //舵机pwm控制
//		{
//			SERVO5_PIN_SET();
//		}else 
//		{
//			SERVO5_PIN_CLR();
//		}
//		if(pwm <= Angle6) //舵机pwm控制
//		{
//			SERVO6_PIN_SET();
//		}else 
//		{
//			SERVO6_PIN_CLR();
//		}
//		if(pwm <= Angle7) //舵机pwm控制
//		{
//			SERVO7_PIN_SET();
//		}else 
//		{
//			SERVO7_PIN_CLR();
//		}
//			if(pwm <= motor_pwm) //小车pwm控制
//				{
//					LEFT_FRONT_PWM_SET()  ;
//				}
//				else 
//				{
//					 LEFT_FRONT_PWM_CLR() ;   
//				}
	
		
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);     //清除TIM1溢出中断标志 	
	}
}
/*-------------------------------------------------*/
/*函数名：定时器4中断服务函数                      */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM4_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){  //如果TIM_IT_Update置位，表示TIM4溢出中断，进入if	
	
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);     //清除TIM4溢出中断标志 	
	
	}
}
//// 串口中断服务函数
//void USART3_IRQHandler(void)
//{
// 
//	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
//	{		
//		
//		 UART3_BUF = USART_ReceiveData(USART3);  
//				 
//	}	 
//}



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
	
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
