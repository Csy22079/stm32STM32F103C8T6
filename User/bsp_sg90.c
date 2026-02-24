#include "bsp_sg90.h"
uint8_t Angle1 = SERVE1_ANGLE_DEF;//舵机角度控制
uint8_t Angle2 = SERVE2_ANGLE_DEF;//舵机角度控制
uint8_t Angle3 = SERVE3_ANGLE_DEF;//舵机角度控制
uint8_t Angle4 = SERVE4_ANGLE_DEF;//舵机角度控制
uint8_t Angle5 = SERVE5_ANGLE_DEF;//舵机角度控制
uint8_t Angle6 = SERVE6_ANGLE_DEF;//舵机角度控制
uint8_t Angle7 = SERVE7_ANGLE_DEF;//舵机角度控制
uint8_t Angle8 = SERVE8_ANGLE_DEF;//小车速度控制

void SERVO_GPIO_CFG(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*电机管脚初始化*/
	RCC_APB2PeriphClockCmd(SERVO1_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = SERVO1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed =   GPIO_Speed_50MHz;
	GPIO_Init(SERVO1_GPIO_PORT, &GPIO_InitStruct);
	
//	RCC_APB2PeriphClockCmd(SERVO2_GPIO_CLK, ENABLE);
//	GPIO_InitStruct.GPIO_Pin = SERVO2_GPIO_PIN;
//	GPIO_Init(SERVO2_GPIO_PORT, &GPIO_InitStruct);
//	 
//	RCC_APB2PeriphClockCmd(SERVO3_GPIO_CLK, ENABLE);
//	GPIO_InitStruct.GPIO_Pin = SERVO3_GPIO_PIN;
//	GPIO_Init(SERVO3_GPIO_PORT, &GPIO_InitStruct);
//	
//	RCC_APB2PeriphClockCmd(SERVO4_GPIO_CLK, ENABLE);
//	GPIO_InitStruct.GPIO_Pin = SERVO4_GPIO_PIN;
//	GPIO_Init(SERVO4_GPIO_PORT, &GPIO_InitStruct);
//	
//	RCC_APB2PeriphClockCmd(SERVO5_GPIO_CLK, ENABLE);
//	GPIO_InitStruct.GPIO_Pin = SERVO5_GPIO_PIN;
//	GPIO_Init(SERVO5_GPIO_PORT, &GPIO_InitStruct);
//	
//	RCC_APB2PeriphClockCmd(SERVO6_GPIO_CLK, ENABLE);
//	GPIO_InitStruct.GPIO_Pin = SERVO6_GPIO_PIN;
//	GPIO_Init(SERVO6_GPIO_PORT, &GPIO_InitStruct);
//	
//	RCC_APB2PeriphClockCmd(SERVO7_GPIO_CLK, ENABLE);
//	GPIO_InitStruct.GPIO_Pin = SERVO7_GPIO_PIN;
//	GPIO_Init(SERVO7_GPIO_PORT, &GPIO_InitStruct);

}

void Servo_Position_Init()//舵机位置初始化
{
	Angle1 = SERVE1_ANGLE_DEF;//舵机角度控制
	Angle2 = SERVE2_ANGLE_DEF;//舵机角度控制
	Angle3 = SERVE3_ANGLE_DEF;//舵机角度控制
	Angle4 = SERVE4_ANGLE_DEF;//舵机角度控制
	Angle5 = SERVE5_ANGLE_DEF;//舵机角度控制
	Angle6 = SERVE6_ANGLE_DEF;//舵机角度控制
	Angle7 = SERVE7_ANGLE_DEF;//舵机角度控制


}
