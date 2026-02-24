#include "bsp_Matrix_key.h"
int KEY_MATRIX_OK=0;
//char MATRIX_KEYVAL[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
//char MATRIX_KEYVAL[]={'D','C','B','A','#','9','6','3','0','8','5','2','*','7','4','1'};
char MATRIX_KEYVAL[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
void KEY_MATRIX_INIT()
{
	 GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC,ENABLE);            /*矩阵*/

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                         //上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEY_MATRIX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(KEY_MATRIX_GPIO_PORT, &GPIO_InitStructure);   
	
}

/********************************************************************
* 名称 : Keyscan()
* 功能 : 实现按键的读取。下面这个子程序是按处理 矩阵键盘 的基本方法处理的。
* 输入 : 无
* 输出 : 按键值
* 管脚 ：A0-A7
***********************************************************************/
/*************************************************************

                            ________
                    7 |                   |
                    6 |                   |
                    5 |                   |
                    4 |______|
                             3 2 1 0
*********************************************************************/
char MATRIX_SCAN(void)
{
        uint8_t BufferH[4] = {0x7f,0xbf, 0xdf,0xef};//
        uint8_t j,temp;
        uint8_t num=16;               
        
        for(j=0; j<4; j++)
        {
                GPIO_SetBits(KEY_MATRIX_GPIO_PORT,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);        //上拉输入默认高电平
                GPIO_ResetBits(KEY_MATRIX_GPIO_PORT,GPIO_Pin_7>>j);    //依次置0
                temp=KEY_MATRIX_GPIO_PORT->IDR;
                temp=temp&BufferH[j];
                if(temp!=BufferH[j])
                {                                                                                                                    
                        delay_ms(5);                        //可以去掉消抖
                        temp=KEY_MATRIX_GPIO_PORT->IDR;
                    temp=temp&BufferH[j];
                        if(temp!=BufferH[j])                                 
                  {
                        
                           if(GPIO_ReadInputDataBit(KEY_MATRIX_GPIO_PORT, GPIO_Pin_0) == 0)
                           {  
                              num=3+j*4;
                           }
                           else if(GPIO_ReadInputDataBit(KEY_MATRIX_GPIO_PORT, GPIO_Pin_1) == 0)
                           {  
                              num=2+j*4;
                           }
                            else if(GPIO_ReadInputDataBit(KEY_MATRIX_GPIO_PORT, GPIO_Pin_2) == 0)
                           {  
                              num=1+j*4;
                           }
                            else if(GPIO_ReadInputDataBit(KEY_MATRIX_GPIO_PORT, GPIO_Pin_3) == 0 )
                           {
                              num=0+j*4;
                           }
                  }
                  
                  
								while(temp!=BufferH[j])
								{
                        temp=KEY_MATRIX_GPIO_PORT->IDR;
                         temp=temp&BufferH[j];
                        KEY_MATRIX_OK=1;
//									printf("66666\r\n");
                }
        }
        }
        return(MATRIX_KEYVAL[num]);
}
