#ifndef __WIFI_H
#define __WIFI_H
#include "sys.h"	    //包含需要的头文件
#include "bsp_usart.h"	    //包含需要的头文件
#include "bsp_usart2.h"	    //包含需要的头文件

#define USART1_TXBUFF_SIZE   512   //定义串口1 发送缓冲区大小 1024字节
 
#define USART1_RXBUFF_SIZE   512              //定义串口1 接收缓冲区大小 1024字节
/*定义WIFI模块RST管脚*/
#define WIFI_RST_GPIO_PORT GPIOA
#define WIFI_RST_GPIO_CLK  RCC_APB2Periph_GPIOA
#define WIFI_RST_GPIO_PIN GPIO_Pin_8
#define RESET_IO(x)    if(x)\
												GPIO_SetBits(WIFI_RST_GPIO_PORT,WIFI_RST_GPIO_PIN);\
												else		\
												GPIO_ResetBits(WIFI_RST_GPIO_PORT,WIFI_RST_GPIO_PIN)
	
#define WiFi_printf       printf           //串口1控制 WiFi
#define WiFi_RxCounter    Usart1_RxCounter    //串口1控制 WiFi
#define WiFi_RX_BUF       Usart1_RxBuff       //串口1控制 WiFi
#define WiFi_RXBUFF_SIZE  USART1_RXBUFF_SIZE  //串口1控制 WiFi

#define SSID   "wifi123"                     //路由器SSID名称
#define PASS   "666888666"                      //路由器密码

#define  PRODUCTKEY           "a1hKq8J0y7h"                                        //产品ID
#define  DEVICENAME           "my_device_mcu"                                               //设备名  
#define  MQTTPASSWORD         "f77d48100742ef39ebec07d9b74be747eeb079d4c539d748fc8f787a2c176a82"     //passward
#define  TIMESTAMP            "1764079728037"                                      //时间戳										
#define  S_TOPIC_NAME         "/a1hKq8J0y7h/my_device_mcu/user/get"   //需要订阅的主题  
#define  P_TOPIC_NAME         "/a1hKq8J0y7h/my_device_mcu/user/update"    //需要发布的主题 

 

extern char Usart1_RxCompleted ;               //外部声明，其他文件可以调用该变量
extern unsigned int Usart1_RxCounter;          //外部声明，其他文件可以调用该变量
extern char Usart1_RxBuff[USART1_RXBUFF_SIZE]; //外部声明，其他文件可以调用该变量
 

void WiFi_ResetIO_Init(void);
char WiFi_SendCmd(char *cmd, int timeout);
char WiFi_Reset(int timeout);
char WiFi_JoinAP(int timeout);
char WiFi_Connect_Server(int timeout);
char WiFi_Smartconfig(int timeout);
char WiFi_WaitAP(int timeout);
char WiFi_Connect_IoTServer(void);
char WiFi_Connect_ALiYun(void);//配置连接阿里云

#endif


