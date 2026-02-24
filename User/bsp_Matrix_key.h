#ifndef _BSP_MATRIX_KEY_H
#define _BSP_MATRIX_KEY_H

#include "stm32f10x.h"
#include "sys.h"
#define KEY_MATRIX_GPIO_PORT    	GPIOA              /* GPIO¶Ë¿Ú */
extern  int KEY_MATRIX_OK;
extern void KEY_MATRIX_INIT(void);
extern char MATRIX_SCAN(void);
#endif
