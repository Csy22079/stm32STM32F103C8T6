#include "bsp_wifi.h"	    

char WiFi_Init_Status = 0;//wifi初始化状态

char wifi_mode = 0;     //联网模式 0：SSID和密码写在程序里   1：Smartconfig方式用APP发送
	
	
	
 
char Usart1_RxCompleted = 0;            //定义一个变量 0：表示接收未完成 1：表示接收完成 
unsigned int Usart1_RxCounter = 0;      //定义一个变量，记录串口2总共接收了多少字节的数据
char Usart1_RxBuff[USART1_RXBUFF_SIZE]; //定义一个数组，用于保存串口2接收到的数据   	
 

/*-------------------------------------------------*/
/*函数名：初始化WiFi的复位IO                       */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void WiFi_ResetIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	/*管脚初始化*/
	RCC_APB2PeriphClockCmd(WIFI_RST_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = WIFI_RST_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed =   GPIO_Speed_50MHz;
	GPIO_Init(WIFI_RST_GPIO_PORT, &GPIO_InitStruct);
	RESET_IO(1);                                              //复位IO拉高电平
}
/*-------------------------------------------------*/
/*函数名：WiFi发送设置指令                         */
/*参  数：cmd：指令                                */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
char WiFi_SendCmd(char *cmd, int timeout)
{
	WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
	WiFi_printf("%s\r\n",cmd);                  //发送指令
	while(timeout--){                           //等待超时时间到0
		delay_ms(200);                          //延时100ms
		if(strstr(WiFi_RX_BUF,"OK"))            //如果接收到OK表示指令成功
			break;       						//主动跳出while循环
		u3_printf("%d ",timeout);               //串口输出现在的超时时间
	}
	u3_printf("\r\n");                          //串口输出信息
	if(timeout<=0)return 1;                     //如果timeout<=0，说明超时时间到了，也没能收到OK，返回1
	else return 0;		         				//反之，表示正确，说明收到OK，通过break主动跳出while
}

/*-------------------------------------------------*/
/*函数名：WiFi模块接收到的内容                     */
/*参  数：dat：接收到的内容                        */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
char WiFi_ReceiveDate(char *dat, int timeout)//WiFi模块接收到的内容 
{
	WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
	memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
	while(timeout--){                           //等待超时时间到0
		delay_ms(100);                          //延时100ms
		if(strstr(WiFi_RX_BUF,dat))            //如果接收到OK表示指令成功
			break;       						//主动跳出while循环
		u3_printf("%d ",timeout);               //串口输出现在的超时时间
	}
	u3_printf("\r\n");                          //串口输出信息
	if(timeout<=0)return 1;                     //如果timeout<=0，说明超时时间到了，也没能收到OK，返回1
	else return 0;		         				//反之，表示正确，说明收到OK，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：WiFi复位                                 */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
char WiFi_Reset(int timeout)
{
	RESET_IO(0);                                    //复位IO拉低电平
	delay_ms(500);                                  //延时500ms
	RESET_IO(1);                                    //复位IO拉高电平	
	while(timeout--){                               //等待超时时间到0
		delay_ms(100);                              //延时100ms
		if(strstr(WiFi_RX_BUF,"ready"))             //如果接收到ready表示复位成功
			break;       						    //主动跳出while循环
		u3_printf("%d ",timeout);                   //串口输出现在的超时时间
	}
	u3_printf("\r\n");                              //串口输出信息
	if(timeout<=0)return 1;                         //如果timeout<=0，说明超时时间到了，也没能收到ready，返回1
	else return 0;		         				    //反之，表示正确，说明收到ready，通过break主动跳出while
}
//AT+CWAUTOCONN=0
//AT+CWMODE=1
//AT+CIPSNTPCFG=1,8,"ntp1.aliyun.com"
//AT+CWJAP="wifi863","chang230@"
//AT+MQTTUSERCFG=0,1,"NULL","mcus&a1pkTNA76OR","06f47b4566e5d3e6403b0c78ee49e4d3fd4788be12cccfb6caca18ec041088cc",0,0,""
//AT+MQTTCLIENTID=0,"a1pkTNA76OR.mcus|securemode=2\,signmethod=hmacsha256\,timestamp=1710592066968|"
//AT+MQTTCONN=0,"a1pkTNA76OR.iot-as-mqtt.cn-shanghai.aliyuncs.com",1883,1
//AT+MQTTSUB=0,"topic",1//订阅指令
//AT+MQTTPUB=0,"topic","Json 格式内容",1,0//发布指令
//AT+MQTTCLEAN=0 //断开连接
char WiFi_Connect_ALiYun()//配置连接阿里云
{
		char  temp[256];             //缓冲区
	while(WiFi_Init_Status != 8)
	{
		switch(WiFi_Init_Status)
		{
			case 0:
			{
					u3_printf("关闭回显\r\n");                 //串口提示数据
				if(WiFi_SendCmd("ATE0",10)){                //关闭多路连接，100ms超时单位，总计5s超时时间
					u3_printf("关闭回显失败\r\n");   //返回非0值，进入if，串口提示数据
						WiFi_Init_Status = 0;//重新复位WIFI模块流程
		                                     //返回9
				}
				else 
				{
					u3_printf("关闭回显成功\r\n");           //串口提示数据
					 WiFi_Init_Status++;//切换下一状态
				}
			}break;
			case 1:
			{
	      u3_printf("准备再次复位模块\r\n");                     //串口提示数据
				if((WiFi_SendCmd("AT+RST",50))){                                //复位，100ms超时单位，总计5s超时时间WiFi_Reset(50)
					u3_printf("复位失败，准备重启\r\n");           //返回非0值，进入if，串口提示数据
						WiFi_Init_Status = 2;//重新复位WIFI模块流程
				}
				else
				{
					u3_printf("复位成功\r\n");                   //串口提示数据
					WiFi_Init_Status++;//切换下一状态
				}
			}
			break;
			case 2:
			{
					u3_printf("准备设置AP+STA模式\r\n");                  //串口提示数据
					if(WiFi_SendCmd("AT+CWMODE=1",20)){                //设置STA模式，100ms超时单位，总计5s超时时间
						u3_printf("设置AP模式失败，准备重启\r\n");    //返回非0值，进入if，串口提示数据
						WiFi_Init_Status = 2;//重新复位WIFI模块流程
				                         
					}
					else 
					{
						u3_printf("设置STA模式成功\r\n");            //串口提示数据
						WiFi_Init_Status++;//切换下一状态
					}
			}
			break;
			case 3:
			{
					u3_printf("准备连接路由器\r\n");                 //串口提示数据
					if(WiFi_SendCmd("AT+CWJAP=\"wifi123\",\"666888666\"",50)){            //取消自动连接，100ms超时单位，总计5s超时时间
						u3_printf("连接路由器失败，准备重启\r\n");   //返回非0值，进入if，串口提示数据
							WiFi_Init_Status = 2;//重新复位WIFI模块流程
					                            //返回3
					}
					else 
					{
						u3_printf("连接路由器成功\r\n");           //串口提示数据
						WiFi_Init_Status++;//切换下一状态
					}
			}
			break;
			case 4:
			{
					u3_printf("准备用户名密码登录阿里云\r\n");                 //串口提示数据
				memset(temp,0,sizeof(temp));
				sprintf(temp,"AT+MQTTUSERCFG=0,1,\"NULL\",\"%s&%s\",\"%s\",0,0,\"\"",DEVICENAME,PRODUCTKEY,MQTTPASSWORD);
					if(WiFi_SendCmd(temp,20)){            //8080表示目标（在此是电脑）UDP端口，9000表示本地端口（ 即ESP8266），0表示远端不变）。
						u3_printf("用户名密码登录阿里云失败，准备重启  %s\r\n",temp);   //返回非0值，进入if，串口提示数据
							WiFi_Init_Status = 3;//重新复位WIFI模块流程
					
					}
					else 
					{
						u3_printf("用户名密码登录阿里云成功,%s\r\n",temp);           //串口提示数据
						WiFi_Init_Status++;//切换下一状态
					}
			}
			break;
			case 5:
			{
				u3_printf("准备CLIENTID\r\n");                 //串口提示数据
				memset(temp,0,sizeof(temp));
				sprintf(temp,"AT+MQTTCLIENTID=0,\"%s.%s|securemode=2\\,signmethod=hmacsha256\\,timestamp=%s|\"",PRODUCTKEY,DEVICENAME,TIMESTAMP);
				if(WiFi_SendCmd(temp,50)){  //CLIENTID
					                                   
					u3_printf("CLIENTID失败\r\n");   //返回非0值，进入if，串口提示数据
						WiFi_Init_Status = 5;//重新复位WIFI模块流程
					                                 //返回3
				}
				else 
				{
					u3_printf("CLIENTID成功\r\n");           //串口提示数据
					 WiFi_Init_Status++;//切换下一状态
				}
			}
			break;
		case 6:
			{
				u3_printf("准备连接阿里云服务器\r\n");                 //串口提示数据
				memset(temp,0,sizeof(temp));
				sprintf(temp,"AT+MQTTCONN=0,\"%s.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1",PRODUCTKEY);                                
				if(WiFi_SendCmd(temp,50)){  //CLIENTID
					u3_printf("连接阿里云服务器失败,%s\r\n",temp);   //返回非0值，进入if，串口提示数据
						WiFi_Init_Status = 6;//重新复位WIFI模块流程
					                                 //返回3
				}
				else 
				{
					u3_printf("连接阿里云服务器成功\r\n");           //串口提示数据
					 WiFi_Init_Status++;//切换下一状态
				}
			}
			break;
		 	case 7:
			{
				u3_printf("订阅主题\r\n");           
					memset(temp,0,sizeof(temp));
					sprintf(temp,"AT+MQTTSUB=0,\"%s\",1",S_TOPIC_NAME);          
				if(WiFi_SendCmd(temp,50)){  //CLIENTID
					u3_printf("订阅主题失败\r\n");   //返回非0值，进入if，串口提示数据
						WiFi_Init_Status = 7;//重新复位WIFI模块流程
					                                 //返回3
				}
				else 
				{
					u3_printf("订阅主题成功\r\n");           //串口提示数据
					 WiFi_Init_Status++;//切换下一状态
				}
			}
			break;
			
			
			//AT+SAVETRANSLINK=1,"192.168.1.35",1125,"UDP",500
		}
	}
		return 0;//成功
}



