#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_display.h"
#include "bsp_led.h"
#include "bsp_oled_iic.h"
#include "bsp_timer2.h" 
#include "bsp_timer1.h" 
#include "bsp_timer4.h" 
#include "bsp_beep.h"   
#include "bsp_as608.h"
#include "bsp_Matrix_key.h"
#include "bsp_relay.h"
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)                                
{

	USART_Config();//初始化串口 
//	USART3_Config();//初始化串口3
	BEEP_GPIO_Config();
	SOFT_IIC_GPIO_CFG();//初始化IIC管脚
  OLED_Init();//OLED初始化 
	OLED_CLS();//清屏
	Display_Init();//初始化显示界面
	Timer2_Init();
	KEY_GPIO_Config();//
	KEY_MATRIX_INIT();//初始化矩阵键盘
	RELAY_GPIO_Config();//初始化继电器 
   rx_queue_init(); /*初始化环形缓冲区*/
	AS608_Config(); /*初始化指纹模块配置*/
	WiFi_Connect_ALiYun();//配置连接阿里云
  
//	Timer1_Init();//初始化定时器 
	printf("INIT OK\r\n");
  /* Infinite loop */
  while (1)
  {
		DISPLAY_Main();//显示函数	
  }
}
