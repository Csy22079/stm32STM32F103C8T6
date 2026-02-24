#include "bsp_i2c_eeprom.h"


void AT24CXX_Write(uint8_t add,uint8_t dat)
{
	Soft_IIC_Write_Address(AT24CXX_ADRESS,add,dat);
}
uint8_t AT24CXX_Read(uint8_t add)
{
	return Soft_IIC_Read_Address(AT24CXX_ADRESS,add,AT24CXX_ADRESS+1);
}
