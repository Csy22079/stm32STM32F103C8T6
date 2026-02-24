#include "bsp_relay.h"

void RELAY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*LED管脚初始化*/
	RCC_APB2PeriphClockCmd(RELAY1_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = RELAY1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed =   GPIO_Speed_50MHz;
	GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RELAY2_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = RELAY2_GPIO_PIN;
	GPIO_Init(RELAY2_GPIO_PORT, &GPIO_InitStruct);
	
	 RELAY1_OFF();//关闭继电器
	 RELAY2_OFF();//关闭继电器
		
}
