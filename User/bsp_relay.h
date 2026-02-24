#ifndef _BSP_RELAY_H
#define _BSP_RELAY_H

#include "stm32f10x.h"


#define RELAY1_GPIO_PORT GPIOB
#define RELAY1_GPIO_CLK  RCC_APB2Periph_GPIOB
#define RELAY1_GPIO_PIN GPIO_Pin_9

#define RELAY2_GPIO_PORT GPIOB
#define RELAY2_GPIO_CLK  RCC_APB2Periph_GPIOB
#define RELAY2_GPIO_PIN GPIO_Pin_9

#define    RELAY1_OFF()  GPIO_ResetBits(RELAY1_GPIO_PORT,RELAY1_GPIO_PIN)
#define    RELAY1_ON() GPIO_SetBits  (RELAY1_GPIO_PORT,RELAY1_GPIO_PIN)

#define    RELAY2_OFF()  GPIO_ResetBits(RELAY2_GPIO_PORT,RELAY2_GPIO_PIN)
#define    RELAY2_ON() GPIO_SetBits  (RELAY2_GPIO_PORT,RELAY2_GPIO_PIN)
extern void RELAY_GPIO_Config(void);
#endif
