#ifndef __BSP_SG90_H__
#define __BSP_SG90_H__
#include "sys.h"

#define SERVE1_ANGLE_MAX 23//舵机1最大角度
#define SERVE1_ANGLE_MIN 5//舵机1最小角度
#define SERVE1_ANGLE_DEF 5//舵机1默认角度12

#define SERVE2_ANGLE_MAX 23//舵机2最大角度
#define SERVE2_ANGLE_MIN 5 //舵机2最小角度
#define SERVE2_ANGLE_DEF 5//舵机1默认角度

#define SERVE3_ANGLE_MAX 23//舵机3最大角度
#define SERVE3_ANGLE_MIN 5 //舵机3最小角度
#define SERVE3_ANGLE_DEF 5//舵机1默认角度 

#define SERVE4_ANGLE_MAX 23//舵机4最大角度
#define SERVE4_ANGLE_MIN 5 //舵机4最小角度
#define SERVE4_ANGLE_DEF 5//舵机1默认角度

#define SERVE5_ANGLE_MAX 23//舵机1最大角度
#define SERVE5_ANGLE_MIN 5 //舵机1最小角度
#define SERVE5_ANGLE_DEF 5//舵机1默认角度

#define SERVE6_ANGLE_MAX 23//舵机2最大角度
#define SERVE6_ANGLE_MIN 5 //舵机2最小角度
#define SERVE6_ANGLE_DEF 5//舵机1默认角度



#define SERVE7_ANGLE_MAX 20//舵机3最大角度
#define SERVE7_ANGLE_MIN 6 //舵机3最小角度
#define SERVE7_ANGLE_DEF 15//舵机1默认角度

#define SERVE8_ANGLE_MAX 200//小车速度最大角度
#define SERVE8_ANGLE_MIN 30  //小车速度最小角度
#define SERVE8_ANGLE_DEF 40 //小车速度

#define SERVE9_ANGLE_MAX 20//舵机4最大角度
#define SERVE9_ANGLE_MIN 6 //舵机4最小角度



#define SERVO1_GPIO_PORT GPIOC
#define SERVO1_GPIO_CLK  RCC_APB2Periph_GPIOC
#define SERVO1_GPIO_PIN GPIO_Pin_13

//#define SERVO2_GPIO_PORT GPIOB
//#define SERVO2_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define SERVO2_GPIO_PIN GPIO_Pin_8

//#define SERVO3_GPIO_PORT GPIOB
//#define SERVO3_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define SERVO3_GPIO_PIN GPIO_Pin_7

//#define SERVO4_GPIO_PORT GPIOB
//#define SERVO4_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define SERVO4_GPIO_PIN GPIO_Pin_6

//#define SERVO5_GPIO_PORT GPIOB
//#define SERVO5_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define SERVO5_GPIO_PIN GPIO_Pin_5

//#define SERVO6_GPIO_PORT GPIOB
//#define SERVO6_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define SERVO6_GPIO_PIN GPIO_Pin_5

//#define SERVO7_GPIO_PORT GPIOB
//#define SERVO7_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define SERVO7_GPIO_PIN GPIO_Pin_5




#define    SERVO1_PIN_CLR()  GPIO_ResetBits(SERVO1_GPIO_PORT,SERVO1_GPIO_PIN)
#define    SERVO1_PIN_SET()  GPIO_SetBits(SERVO1_GPIO_PORT,SERVO1_GPIO_PIN)

#define    SERVO2_PIN_CLR()  GPIO_ResetBits(SERVO2_GPIO_PORT,SERVO2_GPIO_PIN)
#define    SERVO2_PIN_SET()  GPIO_SetBits(SERVO2_GPIO_PORT,SERVO2_GPIO_PIN)


#define    SERVO3_PIN_CLR()  GPIO_ResetBits(SERVO3_GPIO_PORT,SERVO3_GPIO_PIN)
#define    SERVO3_PIN_SET()  GPIO_SetBits(SERVO3_GPIO_PORT,SERVO3_GPIO_PIN)

#define    SERVO4_PIN_CLR()  GPIO_ResetBits(SERVO4_GPIO_PORT,SERVO4_GPIO_PIN)
#define    SERVO4_PIN_SET()  GPIO_SetBits(SERVO4_GPIO_PORT,SERVO4_GPIO_PIN)


#define    SERVO5_PIN_CLR()  GPIO_ResetBits(SERVO5_GPIO_PORT,SERVO5_GPIO_PIN)
#define    SERVO5_PIN_SET()  GPIO_SetBits(SERVO5_GPIO_PORT,SERVO5_GPIO_PIN)

#define    SERVO6_PIN_CLR()  GPIO_ResetBits(SERVO6_GPIO_PORT,SERVO6_GPIO_PIN)
#define    SERVO6_PIN_SET()  GPIO_SetBits(SERVO6_GPIO_PORT,SERVO6_GPIO_PIN)



#define    SERVO7_PIN_CLR()  GPIO_ResetBits(SERVO7_GPIO_PORT,SERVO7_GPIO_PIN)
#define    SERVO7_PIN_SET()  GPIO_SetBits(SERVO7_GPIO_PORT,SERVO7_GPIO_PIN)



extern uint8_t Angle1;//舵机角度控制
extern uint8_t Angle2;//舵机角度控制
extern uint8_t Angle3;//舵机角度控制
extern uint8_t Angle4;//舵机角度控制
extern uint8_t Angle5;//舵机角度控制
extern uint8_t Angle6;//舵机角度控制
extern uint8_t Angle7;//舵机角度控制 
extern uint8_t Angle8;//舵机角度控制



extern void SERVO_GPIO_CFG(void);//管脚配置
extern void Servo_Position_Init(void);//舵机位置初始化


#endif
