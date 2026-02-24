#include "bsp_display.h"
   
unsigned int MSGTimer = 0;     //用于上传更新的计时的变量   单位秒
 

uint8_t KEY_VAL = 0;
char PASSWORD[7];//输入密码
char STROE_PASSWORD[7]={'1','2','3','4','5','6','\0'};//存储密码
char DISPLAY_PASSWORD[7]={'*','*','*','*','*','*','\0'};//存储密码

char FIRST_PASSWORD[7];//存储修改密码时第一次输入的新密码
uint8_t PASSWORD_POINT = 0;//密码索引
uint8_t MODIFY_SUCCESS_CNT = 0;//修改密码时输入原始密码成功次数
uint8_t MODIFY_PASSWORD_START = 0;//修改密码时输入原始密码成功次数
uint8_t MODIFY_PASSWORD_STATUS = 0;
uint8_t PASSWORD_OK = 0;//密码正确
uint8_t PRESS_OK = 0;//按下了ok键

uint32_t SYSTIME = 0;



uint8_t keynum = 0;//按键值
uint8_t keycount = 0;
uint8_t set_flag = 0;//显示标志位
uint8_t flash = 0;
uint16_t Key_Set_Time = 0;
 
/**************************/
uint8_t OLED_DISPLAY_BUF[20];//OLED显示缓存



uint8_t FINGER_ADD_STATUS = 0;//添加指纹状态
uint8_t FINGER_ADD_EN = 0;//添加指纹使能

uint8_t FINGER_DELET_STATUS = 0;//删除指纹状态
uint8_t FINGER_DELET_EN = 0;//删除指纹使能

uint8_t FINGER_COMPARE_STATUS = 0;//比对指纹状态
uint8_t FINGER_COMPARE_EN = 0;//比对指纹使能
uint8_t LOCK_STATUS = 0;//门锁状态
uint8_t Relay_Sta = 0;//门锁状态
uint8_t ALARM_STATUS= 0;//蜂鸣器报警


uint8_t unlocktype = 0;//1~密码2~指纹3~APP
char unLockType[32] ;//开锁方式
char mylog[128];

/*********************************************/
 
 
int DisplayTime;
uint8_t DisplayID_EN = 0;
 
 
uint8_t unlock_Time_en = 0;
uint16_t unlock_Time = 0;
//void PASSWORD_STORE_EEPROM(char *buf)
//{
//	uint8_t i = 0;
//	for(i = 0;i < 6;i++)
//	{
//		AT24CXX_Write(i,buf[i]);
//		delay_ms(5);
////		printf("AT24CXX_Write[%d] = %c\r\n",i,buf[i]);
//	}

//}


//void PASSWORD_READ_EEPROM(char *buf)
//{
//	uint8_t i = 0;
//	for(i = 0;i < 6;i++)
//	{
//		buf[i] = AT24CXX_Read(i);
//		delay_ms(5);
////		printf("AT24CXX_Read[%d] = %x\r\n",i,buf[i]);
//	}

//}

void ClearScreen()
{
  	OLED_ShowStr(32,6,"           ",2);//清除显示
}

void ClearScreen2()
{
  	OLED_ShowStr(32,2,"           ",2);//清除显示
}

void lock_handle()//锁上
{

	  RELAY1_OFF();//关锁
//		Angle1 = SERVE1_ANGLE_DEF;//舵机角度控制	
    LOCK_STATUS = 0;//门锁状态	
	  	/***********显示门锁关闭***************/
		OLED_ShowCN(40,6,66);	//
		OLED_ShowCN(56,6,67);	//
		OLED_ShowCN(72,6,72);	//
		OLED_ShowCN(88,6,73);	//
	 					
		delay_ms(1500);
		strcpy(PASSWORD,"       ");
		OLED_ShowStr(39,6,(unsigned char*)"           ",2);//显示
		//strcpy(unLockType,"key");
		//sprintf(mylog,"T:%d id:%s tp:%s st:%s",SystemTimer,cardHexID,unLockType,"off"); 
		//printf("mylog:%s\r\n",mylog); 
	
}

void unlock_handle()//开锁
{

	  unlock_Time_en = 1;
    unlock_Time = 0;
 
//	  Angle1 = 15;//
	  LOCK_STATUS = 1;//门锁状态
  	RELAY1_ON();//开锁
		/***********显示开锁成功***************/
		 OLED_ShowCN(40,6,54);	//
		 OLED_ShowCN(56,6,55);	//
		 OLED_ShowCN(72,6,21);	//
		 OLED_ShowCN(88,6,22);	//
		 OLED_ShowCN(104,6,51);	//
			delay_ms(1500);
			strcpy(PASSWORD,"       ");
			OLED_ShowStr(39,6,(unsigned char*)"        ",2);//显示		
		//		RELAY1_OFF();//关锁
//		memset(unLockType,0,sizeof(unLockType));
//		strcpy(unLockType,"key");
//sprintf(mylog,"T:%d id:%s tp:%s st:%s",SystemTimer,cardHexID,unLockType,"on"); 
//printf("mylog:%s\r\n",mylog); 
				
	 
}

void KEYSCAN()
{
		
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN))//人脸识别ok
			{
						memset(unLockType,0,sizeof(unLockType));
				          strcpy(unLockType,"face");
									sprintf(mylog,"t:%d,tp:%s st:%s",SystemTimer,unLockType,"on"); 
				 unlock_handle();//开锁
						//u3_printf("KEY1\r\n");
					 
			}
 
		if(!Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN))//设置按键
			{
						FINGER_COMPARE_EN = 1;
					 
			}
 
			if(unlock_Time > 50)
			{
			  unlock_Time = 0;
				  unlock_Time_en = 0;
				 lock_handle();//锁上
			}

}
void Display_Init()//显示初始化
{
//   人(56) 脸(57) 识(58) 别(59) 门(60) 禁(61) 状(62) 态(63) 密(64) 码(65) 门(66) 锁(67) 系(68) 统(69) 强(70) 锁(71)
/************第1行显示：课题名字*************/
	OLED_ShowCN(16,0,56);	//
	OLED_ShowCN(32,0,57);	//
	OLED_ShowCN(48,0,58);	//
	OLED_ShowCN(64,0,59);	//
	OLED_ShowCN(80,0,60);	//
	OLED_ShowCN(96,0,61);	//
	
 
	OLED_ShowStr(0,2,"Time:0000",2);
	
	OLED_ShowCN(0,4,64);	
	OLED_ShowCN(16,4,65);
	OLED_ShowStr(32,4,":",2);
//	OLED_ShowCN(112,0,6);	//
//	OLED_ShowStr(0,2," id:",2);
  /***********第6行********************/
	OLED_ShowCN(0,6,62);	
	OLED_ShowCN(16,6,63);
	OLED_ShowStr(32,6,":",2);
//		PASSWORD_STORE_EEPROM(STROE_PASSWORD);
//   PASSWORD_READ_EEPROM(STROE_PASSWORD);//将新密码读到STROE_PASSWORD
//	printf("STROE_PASSWORD = %c,%c,%c,%c,%c,%c\r\n",STROE_PASSWORD[0],STROE_PASSWORD[1],STROE_PASSWORD[2],STROE_PASSWORD[3],STROE_PASSWORD[4],STROE_PASSWORD[5]);
 
}
void BEEP_ALARM()//报警
{
	uint8_t i = 0;
	for(i = 0;i < 10;i++)
	{
		BEEP(1);//蜂鸣器报警
		delay_ms(30);
		BEEP(0);//蜂鸣器报警
		delay_ms(30);
	}
}
 

void MODIFY_PASSWORD()//修改按键密码
{
	if(MODIFY_PASSWORD_START)//MODIFY_SUCCESS_CNT
	{
		switch(MODIFY_PASSWORD_STATUS)
		{
			case 0://开始修改密码
			{
//				    //printf("开始修改密码\r\n");
						OLED_ShowCN(40,6,12);	//显示修改密码
						OLED_ShowCN(56,6,13);	//
						OLED_ShowCN(72,6,6);	//
						OLED_ShowCN(88,6,7);	//
				
						PASSWORD_POINT = 0;
						strcpy(DISPLAY_PASSWORD,"      ");
						OLED_ShowStr(40,4,(unsigned char*)DISPLAY_PASSWORD,2);//清空显示密码
				
						delay_ms(1000);
						OLED_ShowStr(40,6,(unsigned char*)"        ",2);//清除显示
					  MODIFY_PASSWORD_STATUS = 1;
			}
			break;
			case 1://显示输原始密码
			{
				
						if(PASSWORD_OK == 1)//输入原始密码正确
						{
//							//printf("原始密码正确\r\n");
							   PASSWORD_OK = 0;
							   PRESS_OK = 0;//清除本次按键按下标志，防止直接进入下一个状态
							    PASSWORD_POINT = 0;
									strcpy(DISPLAY_PASSWORD,"      ");//清除显示密码
									strcpy(PASSWORD,"      ");//清除当前输入密码
									OLED_ShowStr(40,4,(unsigned char*)DISPLAY_PASSWORD,2);//清除显示密码
							  	MODIFY_PASSWORD_STATUS = 2;
						}
						else
						{
						
							OLED_ShowCN(40,6,15);	//显示输入原始密码
							OLED_ShowCN(56,6,17);	//
							OLED_ShowCN(72,6,18);	//
							OLED_ShowCN(88,6,6);	//
							OLED_ShowCN(104,6,7);	//
//							MODIFY_PASSWORD_STATUS = 2;
//							PASSWORD_POINT = 0; 
						}
					
			}
			break;
			case 2:
			{
				
						if(PRESS_OK == 1)//输入新密码完成
						{ 
//							//printf("输入新密码正确\r\n");
							    PRESS_OK = 0;
							    PASSWORD_POINT = 0;
									strcpy(DISPLAY_PASSWORD,"      ");//清除显示密码
									OLED_ShowStr(40,4,(unsigned char*)DISPLAY_PASSWORD,2);//清除显示密码
							    strcpy(FIRST_PASSWORD,PASSWORD);//保存第一次输入的密码
//						     	//printf("%s\r\n",FIRST_PASSWORD);
							  	MODIFY_PASSWORD_STATUS = 3;
						}
						else//输入原始密码正确后
						{
							 
								 OLED_ShowCN(40,6,15);	//显示输入新密码
								 OLED_ShowCN(56,6,16);	//
								 OLED_ShowCN(72,6,25);	//
								 OLED_ShowCN(88,6,6);	  //
								 OLED_ShowCN(104,6,7);	//				
						}
				
			}
			break;
			case 3:
			{
						if(PRESS_OK == 1)//再次输入新密码完成
						{
//							  //printf("再次输入新密码正确\r\n");
							  PRESS_OK = 0;
							  PASSWORD_POINT = 0;
								strcpy(DISPLAY_PASSWORD,"      ");//清除显示密码
								OLED_ShowStr(40,4,(unsigned char*)DISPLAY_PASSWORD,2);//清除显示密码
								MODIFY_PASSWORD_STATUS = 4;
						}
						else
						{
						
						    OLED_ShowCN(40,6,14);	//显示请再次输入
								OLED_ShowCN(56,6,19);	//
								OLED_ShowCN(72,6,20);	//
								OLED_ShowCN(88,6,15);	//
								OLED_ShowCN(104,6,16);	//
						}
			}
			break;
			case 4://输入两次新密码一致
			{
				
						if(!strcmp(PASSWORD,FIRST_PASSWORD))//密码一致
							{
									MODIFY_PASSWORD_STATUS = 5;
							}
							else
							{
								OLED_ShowCN(40,6,6);	//两次输入密码不一致
								OLED_ShowCN(56,6,7);	//
								OLED_ShowCN(72,6,26);	//
								OLED_ShowCN(88,6,27);	//
								OLED_ShowCN(104,6,28);	//
								BEEP_ALARM();//报警
								MODIFY_PASSWORD_STATUS = 3;//重新再次输入新密码
							}
							
			}
			break;
			case 5:
			{
				  
				  strcpy(STROE_PASSWORD,PASSWORD);//将新密码存储到EEPROM   
//				  PASSWORD_STORE_EEPROM(PASSWORD);//将新密码存储到EEPROM
//				  PASSWORD_READ_EEPROM(STROE_PASSWORD);//将新密码读到STROE_PASSWORD
				  MODIFY_PASSWORD_STATUS = 0;//清零修改密码状态
				  MODIFY_PASSWORD_START = 0;//结束修改密码
					PRESS_OK = 0;
					PASSWORD_POINT = 0;
//				  //printf("修改密码完成\r\n");
					OLED_ShowCN(40,6,12);	//修改完成
					OLED_ShowCN(56,6,13);	//
					OLED_ShowCN(72,6,21);	//
					OLED_ShowCN(88,6,22);	//
					OLED_ShowCN(104,6,51);//
					delay_ms(1000);
					strcpy(DISPLAY_PASSWORD,"      ");//清除显示密码
				  strcpy(PASSWORD,"      ");//清除当前输入密码
					OLED_ShowStr(40,6,(unsigned char*)DISPLAY_PASSWORD,2);//清除显示密码
				  OLED_ShowStr(40,6,(unsigned char*)"          ",2);//清除状态显示
			}
			break;
		
		}
	}

}


/**
  * @brief  录指纹
  * @param  无
  * @retval 无
  */
static void  Add_FR(void)
{
  uint16_t  i = 0,sure,ID;
	if(FINGER_ADD_EN)
	{ 
		////printf("FINGER_ADD_STATUS = %d\r\n",FINGER_ADD_STATUS);
		switch(FINGER_ADD_STATUS)//录指纹状态
		{
			case 0:
			{
				/***********显示添加指纹***************/
				OLED_ShowCN(40,6,29);	//
				OLED_ShowCN(56,6,30);	//
				OLED_ShowCN(72,6,32);	//
				OLED_ShowCN(88,6,33);	//
//				OLED_ShowStr(40,6,(unsigned char*)DISPLAY_PASSWORD,2);//清除添加指纹
				delay_ms(1000);
				/***********显示请按手指***************/
				OLED_ShowCN(40,6,14);	//
				OLED_ShowCN(56,6,31);	//
				OLED_ShowCN(72,6,32);	//
				OLED_ShowCN(88,6,33);	//
				delay_ms(1000);
				 //printf("******命令：请按手指******\r\n");
				FINGER_ADD_STATUS = 1;
			}
			break;
			case 1:
			{
				 
					
					sure=PS_GetImage();              /*录入图像*/      
					if(sure == 0x00)
					{
						sure=PS_GenChar(CHAR_BUFFER1);  /*生成特征1*/
						if(sure==0x00)
						{ 
							//printf("输入指纹一正常！！！\r\n");
							/***********显示指纹一正常***************/
							OLED_ShowCN(40,6,32);	//
							OLED_ShowCN(56,6,33);	//
							OLED_ShowCN(72,6,27);	//
							OLED_ShowCN(88,6,36);	//
							OLED_ShowCN(104,6,37);	//
	//					OLED_ShowStr(40,6,(unsigned char*)DISPLAY_PASSWORD,2);//清除指纹一正常
							sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
							if(sure==0x00)
							{
							 //printf ("指纹已存在，指纹ID：%d！！！\r\n\r\n",ID);
								 /***********显示指纹已存在***************/
								OLED_ShowCN(40,6,32);	//
								OLED_ShowCN(56,6,33);	//
								OLED_ShowCN(72,6,38);	//
								OLED_ShowCN(88,6,39);	//
								OLED_ShowCN(104,6,40);	//
								delay_ms(1000);
								FINGER_ADD_STATUS = 0; /*跳转到第0步*/
								FINGER_ADD_EN = 0;//取消指纹添加
								 ClearScreen();//清除显示
							 return ;
							}              
							else 
							{
								FINGER_ADD_STATUS = 2;/*跳转到第2步*/
							 }
						 }
						 else
						 {
	//						 ShowErrMessage(sure);	
									//printf ("生成特征：%d\r\n",sure);						 
						 }
					}
					else 
					{
						i++;
	//				  ShowErrMessage(sure);
//							AS608_INFO ("没有检测到手指：%d\r\n",sure);				
					}
			
			}
			break;
			case 2:
			{
					/***********显示请再按手指***************/
				OLED_ShowCN(40,6,14);	//
				OLED_ShowCN(56,6,19);	//
				OLED_ShowCN(72,6,31);	//
				OLED_ShowCN(88,6,32);	//
				OLED_ShowCN(104,6,33);	//
				delay_ms(1000);
//				OLED_ShowStr(40,6,(unsigned char*)DISPLAY_PASSWORD,2);//清除请再按手指
				FINGER_ADD_STATUS = 3;
//				 AS608_INFO("******命令：请再按一次手指******\r\n");
			}
			break;
			case 3:
			{
					sure=PS_GetImage();
					if(sure==0x00)
					{ 
						sure=PS_GenChar(CHAR_BUFFER2);  /*生成特征2*/
						if(sure==0x00)
						{ 
	//				    AS608_INFO("输入指纹2正常！！！\r\n");    
							 /***********显示指纹二正常***************/
							OLED_ShowCN(40,6,32);	//
							OLED_ShowCN(56,6,33);	//
							OLED_ShowCN(72,6,35);	//
							OLED_ShowCN(88,6,36);	//
							OLED_ShowCN(104,6,37);	//
							delay_ms(1000);
							FINGER_ADD_STATUS = 4; /*跳转到第4步*/
						}
						else 
						{
	//					  ShowErrMessage(sure);
//								AS608_INFO ("生成特征：%d\r\n",sure);	
						}

					 }
					 else 
					 {
							i++;
	//			   ShowErrMessage(sure);
//							AS608_INFO ("没有检测到手指：%d\r\n",sure);			
					 }
				
			}
			break;
			case 4:
			{
//				 AS608_INFO("正在对比两次输入的指纹\r\n");
					 /***********显示比对指纹***************/
							OLED_ShowCN(40,6,41);	//
							OLED_ShowCN(56,6,42);	//
							OLED_ShowCN(72,6,32);	//
							OLED_ShowCN(88,6,33);	//
							OLED_ShowCN(104,6,51);	//
				
					 sure=PS_Match();                /*精确比对两枚指纹特征*/
					 if(sure==0x00) 
					 {
//						 AS608_INFO("输入指纹对比成功！！！\r\n");
							/***********显示比对成功***************/
							OLED_ShowCN(40,6,41);	//
							OLED_ShowCN(56,6,42);	//
							OLED_ShowCN(72,6,21);	//
							OLED_ShowCN(88,6,22);	//
						  OLED_ShowCN(104,6,51);	//
							FINGER_ADD_STATUS = 5; /*跳转到第5步*/
					 }
					 else
					 {
//						 AS608_INFO("对比失败，请重新录入指纹！！！\r\n");
							/***********显示比对失败***************/
							OLED_ShowCN(40,6,41);	//
							OLED_ShowCN(56,6,42);	//
							OLED_ShowCN(72,6,43);	//
							OLED_ShowCN(88,6,44);	//
						  OLED_ShowCN(104,6,51);	//
//						 ShowErrMessage(sure);
							FINGER_ADD_EN = 0;//取消指纹添加
						FINGER_ADD_STATUS = 0; /*跳转到第0步*/
					 }
				
			}
			break;	
			case 5:
			{
//					 AS608_INFO("正在生成指纹模块\r\n");
					/***********显示生成模板***************/
						OLED_ShowCN(40,6,45);	//
						OLED_ShowCN(56,6,46);	//
						OLED_ShowCN(72,6,47);	//
						OLED_ShowCN(88,6,48);	//
			      OLED_ShowCN(104,6,51);	//
					 sure=PS_RegModel();            /*合并特征（生成模板）*/
					 if(sure==0x00) 	
					 {
//						 AS608_INFO("生成指纹模块成功！！！\r\n");
						 /***********显示生成成功***************/
							 OLED_ShowCN(40,6,45);	//
							 OLED_ShowCN(56,6,46);	//
							 OLED_ShowCN(72,6,21);	//
							 OLED_ShowCN(88,6,22);	//
						   OLED_ShowCN(104,6,51);	//
							 FINGER_ADD_STATUS = 6; /*跳转到第5步*/
					 } 
					 else 
					{
					    FINGER_ADD_STATUS = 0; /*跳转到第0步*/
						  FINGER_ADD_EN = 0;//取消指纹添加
//					    ShowErrMessage(sure);
					}
				
			}
			break;
				case 6:
			{
				 /***********显示输入ID***************/
//						 OLED_ShowCN(40,6,15);	//
//						 OLED_ShowCN(56,6,16);	//
					
				
	//			  do
	//         { 
	//           AS608_INFO ("******命令：请输入存储ID，范围为0—239******\r\n");
	//           ID=GET_NUM();
	//         }while(!(ID<PS_MAXNUM));
					
//					 ID = KEY_VAL - 0x30;
				

//				if((KEY_VAL >= '1') && ((KEY_VAL <= '9')))//按下了按键
				{
//					 if((ID > 0) && (ID < PS_MAXNUM))
					 {
							 sure=PS_StoreChar(CHAR_BUFFER2,0);  /*储存模板*/
//						 //printf("STORE_FINGER_ID = %d\r\n",STORE_FINGER_ID);
								if(sure==0x00) 	
							 {
//								 AS608_INFO("录入指纹模块成功！！！\r\n\r\n");
									/***********显示录入成功***************/
								 OLED_ShowCN(40,6,49);	//
								 OLED_ShowCN(56,6,50);	//
								 OLED_ShowCN(72,6,21);	//
								 OLED_ShowCN(88,6,22);	//
								 OLED_ShowCN(104,6,51);	//
									delay_ms(1000);
								 FINGER_ADD_STATUS = 0;
								 FINGER_ADD_EN = 0;
									 ClearScreen();//清除显示
								 return ;
							 } 
							 else 
							 {
									FINGER_ADD_STATUS = 0; /*跳转到第0步*/
									FINGER_ADD_EN = 0;//取消指纹添加
//								 ShowErrMessage(sure);
							 }
					 }
				 }
			}
			break;
			
			
//			 if(i==4)                       /*超过4次没有按手指则退出*/
//				{ 
//					AS608_INFO("录指纹失败！\r\n\r\n\r\n");
//					break;
//				}	
			}
		}
  
}	
uint16_t  ID;
/**
  * @brief  删除指定用户指纹
  * @param  无
  * @retval 无
  */
void Del_FR(void)
{ 

	uint16_t  sure;
	uint8_t  buf[20];
  	if(FINGER_DELET_EN)
	{
		                            
		switch(FINGER_DELET_STATUS)//删指纹状态
		{
			case 0:
			{	
//				AS608_INFO("删除指纹\r\n");
				/***********显示删除指纹***************/
				OLED_ShowCN(40,6,52);	//
				OLED_ShowCN(56,6,53);	//
				OLED_ShowCN(72,6,32);	//
				OLED_ShowCN(88,6,33);	//
				delay_ms(1000);
				/***********显示请按手指***************/
				OLED_ShowCN(40,6,14);	//
				OLED_ShowCN(56,6,31);	//
				OLED_ShowCN(72,6,32);	//
				OLED_ShowCN(88,6,33);	//
				delay_ms(1000);
//				 AS608_INFO("******命令：请按手指******\r\n");
				FINGER_DELET_STATUS = 1;//切换下一个状态
				
			}break;
			case 1:
			{
				 sure=PS_GetImage();
					if(sure == 0x00)
					{
						sure=PS_GenChar(CHAR_BUFFER1);    /*生成特征1*/
						if(sure==0x00)
						{  
							/*高速搜索指纹库*/
							sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
							if(sure==0x00)
							{
								/***********显示指纹ID***************/
								OLED_ShowCN(40,6,32);	//
								OLED_ShowCN(56,6,33);	//
								sprintf(buf,"ID:%d",ID);
								OLED_ShowStr(72,6,buf,2);//显示ID
								delay_ms(1500);
								ClearScreen();//清除显示
								printf ("对比指纹成功，指纹ID：%d\r\n\r\n",ID);
								FINGER_DELET_STATUS = 2;//切换下一个状态
							}
							else 
							{
//									ShowErrMessage(sure);
									if(sure == 0x09)
									{
												/***********显示指纹不存在***************/
											 OLED_ShowCN(40,6,32);	//
											 OLED_ShowCN(56,6,33);	//
											 OLED_ShowCN(72,6,26);	//
											 OLED_ShowCN(88,6,39);	//
											 OLED_ShowCN(104,6,40);	//
											delay_ms(1000);
									   	 ClearScreen();//清除显示
											/***********显示删除失败***************/
											 OLED_ShowCN(40,6,52);	//
											 OLED_ShowCN(56,6,53);	//
											 OLED_ShowCN(72,6,43);	//
											 OLED_ShowCN(88,6,44);	//
											 OLED_ShowCN(104,6,51);	//
												delay_ms(1000);
											 FINGER_DELET_STATUS = 0;
											 FINGER_DELET_EN = 0;
											 ClearScreen();//清除显示
									}
							}
						}
						else 
						{   
//									ShowErrMessage(sure);	
						}
					}
					else  
					{
//								ShowErrMessage(sure);
					}
			}break;
			case 2:
			{	
//				//printf("ID:%d\r\n",ID);
					sure=PS_DeletChar(0,1);         /*删除指定用户的指纹模板*/
			   
					if(sure == 0x00)                
					{
//						AS608_INFO("删除指定用户指纹成功！！！\r\n\r\n");
							/***********显示删除成功***************/
						 OLED_ShowCN(40,6,52);	//
						 OLED_ShowCN(56,6,53);	//
						 OLED_ShowCN(72,6,21);	//
						 OLED_ShowCN(88,6,22);	//
						 OLED_ShowCN(104,6,51);	//
							delay_ms(1000);
						 FINGER_DELET_STATUS = 0;
						 FINGER_DELET_EN = 0;
						 ClearScreen();//清除显示
						printf("删除指定用户指纹成功\r\n");
					}
					else 
					{
//						ShowErrMessage(sure);
						if(sure == 0x10)
						{
									/***********显示删除失败***************/
								 OLED_ShowCN(40,6,52);	//
								 OLED_ShowCN(56,6,53);	//
								 OLED_ShowCN(72,6,43);	//
								 OLED_ShowCN(88,6,44);	//
								 OLED_ShowCN(104,6,51);	//
									delay_ms(1000);
								 FINGER_DELET_STATUS = 0;
								 FINGER_DELET_EN = 0;
									 ClearScreen();//清除显示
						}
						
					}
			}break;
		}
  }	
}

/**
  * @brief  比对指纹（识别指纹）
  * @param  无
  * @retval 无
  */
void Compare_FR(void)  
{  
  uint16_t  ID=0;                    /*初始化ID值*/  
  uint16_t  sure;
	 
	if((!FINGER_ADD_EN) && (!FINGER_DELET_EN) && (FINGER_COMPARE_EN))//不在删除和录入指纹状态下
	{
	                               //喂狗
		switch(FINGER_COMPARE_STATUS)
		{
			case 0:
			{	
				
//				AS608_INFO("******命令：对比指纹，请按手指******\r\n");
						/***********显示比对指纹***************/
							OLED_ShowCN(40,6,41);	//
							OLED_ShowCN(56,6,42);	//
							OLED_ShowCN(72,6,32);	//
							OLED_ShowCN(88,6,33);	//
						  OLED_ShowCN(104,6,51);	//
							FINGER_COMPARE_STATUS = 1; /*跳转到第5步*/

			}break;
		  case 1:
			{
				
					sure=PS_GetImage();
					if(sure == 0x00)
					{
						sure=PS_GenChar(CHAR_BUFFER1);    /*生成特征1*/
						if(sure==0x00)
						{  
							/*高速搜索指纹库*/
							sure=PS_HighSpeedSearch(CHAR_BUFFER1,0,PS_MAXNUM,&ID);
							if(sure==0x00)
							{
								FINGER_COMPARE_EN = 0;//失能指纹功能
//								AS608_INFO ("对比指纹成功，指纹ID：%d！！！\r\n\r\n",ID);
								/***********显示指纹ID***************/
//								OLED_ShowCN(40,6,32);	//
//								OLED_ShowCN(56,6,33);	//
//								sprintf(buf,"ID:%d",ID);
//								OLED_ShowStr(72,6,buf,2);//显示ID
//								LOCK_STATUS = 1;//开锁状态
//						     RELAY1_ON();//打开继电器
								 unlock_handle();//开锁
								
								delay_ms(1500);
								/***********显开锁成功***************/
								 OLED_ShowCN(40,6,54);	//
								 OLED_ShowCN(56,6,55);	//
								 OLED_ShowCN(72,6,21);	//
								 OLED_ShowCN(88,6,22);	//
								 OLED_ShowCN(104,6,51);	//
									delay_ms(1000);
								 FINGER_COMPARE_EN = 0;//失能指纹功能
								 FINGER_COMPARE_STATUS = 0;//清零状态
								 	ALARM_STATUS = 0;
									 ClearScreen();//清除显示
//								AS608_INFO ("对比指纹成功，指纹ID：%d\r\n\r\n",ID);
//							 RELAY1_OFF();//关闭继电器
									memset(unLockType,0,sizeof(unLockType));
				          strcpy(unLockType,"finger");
									sprintf(mylog,"t:%d,tp:%s st:%s",SystemTimer,unLockType,"on"); 
								//printf("mylog:%s\r\n",mylog); 
							}
							else 
							{
//									ShowErrMessage(sure);
							 
									/***********显示指纹不存在***************/
									 OLED_ShowCN(40,6,32);	//
									 OLED_ShowCN(56,6,33);	//
									 OLED_ShowCN(72,6,26);	//
									 OLED_ShowCN(88,6,39);	//
									 OLED_ShowCN(104,6,40);	//
									 delay_ms(1000);
									 ClearScreen();//清除显示
									 BEEP_ALARM();//报警
								   ALARM_STATUS = 1;//蜂鸣器报警
								   lock_handle();//锁上
								 
									 FINGER_COMPARE_EN = 0;//失能指纹功能
								   FINGER_COMPARE_STATUS = 0;//清零状态
										 ClearScreen();//清除显示
									memset(unLockType,0,sizeof(unLockType));
				          strcpy(unLockType,"finger");
									sprintf(mylog,"t:%d,tp:%s st:%s",SystemTimer,unLockType,"off"); 
								//printf("mylog:%s\r\n",mylog); 
							}
						}
						else 
						{   
//							ShowErrMessage(sure);	
						}
					}
					else  
					{
//						ShowErrMessage(sure);
					}
			}break;	
				
			}
		}
}

 

void MATRIX_KEYPROCESS()
{
	KEY_VAL = MATRIX_SCAN();
KEYSCAN();//独立按键扫描
	if(KEY_MATRIX_OK)
	{
		KEY_MATRIX_OK = 0;
		switch(KEY_VAL)
		{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					PASSWORD[PASSWORD_POINT] = KEY_VAL;//存储实际密码
					DISPLAY_PASSWORD[PASSWORD_POINT] = '*';//存储显示的密码*
					if(PASSWORD_POINT >= 6)
					{
							PASSWORD_POINT = 6; 
					}	
					else
					{
							PASSWORD_POINT++; 
					}	
					PASSWORD[PASSWORD_POINT] = '\0';
		     	DISPLAY_PASSWORD[PASSWORD_POINT] = '\0';
		      OLED_ShowStr(40,4,(unsigned char*)DISPLAY_PASSWORD,2);//显示密码
				}
				break;				
				case '*'://退格键
				{
					if(PASSWORD_POINT <= 0)
					{
							PASSWORD_POINT = 0; 
					}	
					else
					{
							PASSWORD_POINT--; 
					}	
					PASSWORD[PASSWORD_POINT] = ' ';
					DISPLAY_PASSWORD[PASSWORD_POINT] = ' ';
		      PASSWORD[PASSWORD_POINT+1] = '\0';
					DISPLAY_PASSWORD[PASSWORD_POINT+1] = '\0';
		      OLED_ShowStr(40,4,(unsigned char*)DISPLAY_PASSWORD,2);//显示密码
				}	
				break;
				case '#'://确认按键
				{
					 PRESS_OK = 1;//按下了确认键
					if(MODIFY_PASSWORD_START)//修改密码状态
					{
								if(!strcmp(PASSWORD,STROE_PASSWORD))//密码正确
								{
										PASSWORD_OK = 1;//按下了ok键
								}
								else
								{
									if(MODIFY_PASSWORD_STATUS == 1)//输入原始密码的状态下
									{
											/***********显示密码错误***************/
										OLED_ShowCN(40,6,6);	//
										OLED_ShowCN(56,6,7);	//
										OLED_ShowCN(72,6,10);	//
										OLED_ShowCN(88,6,11);	//
										BEEP_ALARM();//报警
									  
								    MODIFY_PASSWORD_STATUS = 1;//重新输入原始密码
									  PASSWORD_POINT = 0;
									  strcpy(DISPLAY_PASSWORD,"       ");
									  OLED_ShowStr(39,4,(unsigned char*)DISPLAY_PASSWORD,2);//清除显示密码
									  delay_ms(1500);
									}
									
								}
					}
					else//识别状态
					{
							 unlocktype = 1;//1~密码2~指纹3~APP
						  //printf("PASSWORD:%s,STROE_PASSWORD:%s\r\n",PASSWORD,STROE_PASSWORD);
							if(!strcmp(PASSWORD,STROE_PASSWORD))//密码正确
							{
								PASSWORD_POINT = 0;
								strcpy(DISPLAY_PASSWORD,"       ");
									ALARM_STATUS = 0;
								 OLED_ShowStr(40,4,(unsigned char*)DISPLAY_PASSWORD,2);//显示密码
								 unlock_handle();//开锁
								memset(unLockType,0,sizeof(unLockType));
				          strcpy(unLockType,"passwoed");
									sprintf(mylog,"t:%d,tp:%s st:%s",SystemTimer,unLockType,"on"); 
							}		
							else
							{

								PASSWORD_POINT = 0;
								strcpy(DISPLAY_PASSWORD,"       ");
								 OLED_ShowStr(39,4,(unsigned char*)DISPLAY_PASSWORD,2);//显示密码
								 BEEP_ALARM();//报警
								 ALARM_STATUS = 1;//陌生人
								 lock_handle();//锁上
								memset(unLockType,0,sizeof(unLockType));
				          strcpy(unLockType,"passwoed");
									sprintf(mylog,"t:%d,tp:%s st:%s",SystemTimer,unLockType,"off"); 
							}	
					}
					
				}	
				break;
				case 'A'://修改按键密码
				{
				 
						MODIFY_PASSWORD_START = 1;//开始修改密码
				}
				break;
					case 'B'://添加指纹
				{
//							//printf("添加指纹\r\n");
				 
					FINGER_ADD_EN = 1;//添加指纹
				}
				break;
				case 'C'://删除指纹
				{
					 
					FINGER_DELET_EN = 1;//删除指纹标志
				}
				break;
				case 'D'://管理员模式
				{
//					//printf("比对指纹\r\n");
//					FINGER_COMPARE_EN = 1;//使能指纹功能	 
//					 adminEn = 0;//管理员模式
//						if(Angle1 < 25)Angle1++;
//              else Angle1 = 4;	
						printf("Relay_Sta = %d\r\n",Relay_Sta);	
 
				}
				break;
				case '.'://清除指纹库
				{
//					//printf("清除指纹库\r\n");
						
				}
				break;
			
		}
		printf("KEY_VAL = %c,PASSWORD_POINT = %d,MODIFY_SUCCESS_CNT = %d\r\n",KEY_VAL,PASSWORD_POINT,MODIFY_SUCCESS_CNT);
	}
	
}


/*-------------------------------------------------*/
/*函数名：定时上传各种数据的任务                   */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AliIot_Post(void)
{ 	
	 
	char  temp[512];             //缓冲区
  static uint16_t Post_Time = 0;
	#define POST_TIME 100
	Post_Time++;
	if((Post_Time > POST_TIME))
	{                                   
    Post_Time = 0;		
		 
		  memset(temp,0,sizeof(temp));
		  sprintf(temp,"AT+MQTTPUB=0,\"%s\",\"{\\\"LOCK_STATUS\\\":%d\\,\\\"SystemTimer\\\":%d\\,\\\"ALARM_STATUS\\\":%d\\,\\\"log\\\":\\\"%s\\\"}\",0,0\r\n",\
		  P_TOPIC_NAME,LOCK_STATUS,SystemTimer,ALARM_STATUS,mylog);
	    printf("%s",temp);		 
		  memset(unLockType,0,sizeof(unLockType));
		  memset(mylog,0,sizeof(mylog));
					 
		
		
//			//u3_printf("%s len = %d\r\n",temp,strlen(temp));
	}
}

void  AliIot_Message_Handle()//处理阿里云报文
{
	      if(strstr((const char*)WiFi_RX_BUF,"{\"SW1\":\"0\"}"))//判断阿里云发下来的数据里是否有on
				{
					 ////u3_printf("收到SW1\r\n");
					  
					if(LOCK_STATUS)
					{
						LOCK_STATUS = 0;
						lock_handle();//锁 
						memset(unLockType,0,sizeof(unLockType));
						strcpy(unLockType,"app");
						sprintf(mylog,"t:%d,tp:%s st:%s",SystemTimer,unLockType,"off"); 
					}else
					{
						LOCK_STATUS = 1;
						unlock_handle();//开锁
						memset(unLockType,0,sizeof(unLockType));
						strcpy(unLockType,"app");
						sprintf(mylog,"t:%d,tp:%s st:%s",SystemTimer,unLockType,"on"); 
					}
					WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
				}
				else if(strstr((const char*)WiFi_RX_BUF,"{\"SW1\":\"1\"}"))//判断阿里云发下来的数据里是否有on
				{
					////u3_printf("收到SW1\r\n");
			 	 
					WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
				}
				else if(strstr((const char*)WiFi_RX_BUF,"{\"SW2\":\"0\"}"))//判断阿里云发下来的数据里是否有off
				{
					////u3_printf("收到SW2\r\n");
		 	
					WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
				}	
				else if(strstr((const char*)WiFi_RX_BUF,"{\"SW2\":\"1\"}"))//判断阿里云发下来的数据里是否有off
				{
					////u3_printf("收到SW2\r\n");
 	
          WiFi_RxCounter=0;                         
					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
				}	
				else if(strstr((const char*)WiFi_RX_BUF,"{\"SW3\":\"0\"}"))//判断阿里云发下来的数据里是否有off
				{
					////u3_printf("收到SW3\r\n");
 
					WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
				}	
				else if(strstr((const char*)WiFi_RX_BUF,"{\"SW3\":\"1\"}"))//判断阿里云发下来的数据里是否有off
				{
					////u3_printf("收到SW3\r\n");
	 	
					WiFi_RxCounter=0;                           //WiFi接收数据量变量清零                        
					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);     //清空WiFi接收缓冲区 
				}	
			 
     
} 
void DISPLAY_Main()//显示函数
{
						AliIot_Message_Handle();//处理阿里云报文
						AliIot_Post();//上报阿里云
					 MSGTimer++;
						if(MSGTimer > 10000)
						{
							MSGTimer = 0;
							 
						}
				
						MATRIX_KEYPROCESS();//矩阵键盘扫码
							MODIFY_PASSWORD();//修改密码
						Add_FR();   /*添加指纹*/
						Del_FR();//删除指纹
						Compare_FR();  /*比对指纹*/
						OLED_DISPLAY_BUF[0] = SystemTimer / 1000  + 0x30;
						OLED_DISPLAY_BUF[1] = SystemTimer / 100  % 10 + 0x30;
						OLED_DISPLAY_BUF[2] = SystemTimer / 10  % 10 + 0x30;
				    OLED_DISPLAY_BUF[3] = SystemTimer % 10 + 0x30;
						OLED_DISPLAY_BUF[4] = '\0';
						OLED_ShowStr(40,2,(unsigned char*)OLED_DISPLAY_BUF,2);				//显示
}

