#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "stm32f10x.h"
/*¶¨ÒåºËÐÄ°åLED*/
#define LED1_GPIO_PORT GPIOB
#define LED1_GPIO_CLK  RCC_APB2Periph_GPIOB
#define LED1_GPIO_PIN GPIO_Pin_3

#define LED2_GPIO_PORT GPIOB
#define LED2_GPIO_CLK  RCC_APB2Periph_GPIOB
#define LED2_GPIO_PIN GPIO_Pin_3


#define LED3_GPIO_PORT GPIOB
#define LED3_GPIO_CLK  RCC_APB2Periph_GPIOB
#define LED3_GPIO_PIN GPIO_Pin_3


#define LED4_GPIO_PORT GPIOB
#define LED4_GPIO_CLK  RCC_APB2Periph_GPIOB
#define LED4_GPIO_PIN GPIO_Pin_3



#define    LED1_ON()   GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define    LED1_OFF()  GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define    LED3_ON()   GPIO_ResetBits(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define    LED3_OFF()  GPIO_SetBits(LED3_GPIO_PORT,LED3_GPIO_PIN)

#define    LED2_ON()   GPIO_ResetBits(LED1_GPIO_PORT,LED2_GPIO_PIN)
#define    LED2_OFF()  GPIO_SetBits(LED1_GPIO_PORT,LED2_GPIO_PIN)


#define    LED4_ON()   GPIO_ResetBits(LED4_GPIO_PORT,LED4_GPIO_PIN)
#define    LED4_OFF()  GPIO_SetBits  (LED4_GPIO_PORT,LED4_GPIO_PIN)


extern void LED_GPIO_Config(void);
#endif
