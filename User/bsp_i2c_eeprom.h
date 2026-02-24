#ifndef __I2C_EE_H
#define	__I2C_EE_H


#include "stm32f10x.h"
#include "bsp_i2c_gpio.h"
//			  256			  /* 24xx02总容量 */
#define AT24CXX_ADRESS			0xA0		/* 24xx02的设备地址 */
#define EEPROM_PAGE_SIZE		  8			  /* 24xx02的页面大小 */
#define EEPROM_SIZE	
/* 
 * AT24C02 2kb = 2048bit = 2048/8 B = 256 B
 * 32 pages of 8 bytes each
 *
 * Device Address
 * 1 0 1 0 A2 A1 A0 R/W
 * 1 0 1 0 0  0  0  0 = 0XA0
 * 1 0 1 0 0  0  0  1 = 0XA1 
 */

/* AT24C01/02每页有8个字节 
 * AT24C04/08A/16A每页有16个字节 
 */
#define TIME_EEPROM 0x00//掉电保存早晨小时
#define Morn_Mint_EEPROM 0x20//掉电保存早晨分钟
#define Morn_Hour_EEPROM 0x10//掉电保存早晨小时
#define Morn_Mint_EEPROM 0x20//掉电保存早晨分钟

#define Midy_Hour_EEPROM 0x30
#define Midy_Mint_EEPROM 0x40

#define Even_Hour_EEPROM 0x50
#define Even_Mint_EEPROM 0x60

#define Medc_Remd_EEPROM 0x70


#define Place_Hour_EEPROM 0x80
#define Place_Mint_EEPROM 0x90


extern void AT24CXX_Write(uint8_t add,uint8_t dat);
extern uint8_t AT24CXX_Read(uint8_t add);


#endif /* __I2C_EE_H */
