#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ILI93xx.h"
#include "key.h"
#include "malloc.h" 
#include "usmart.h" 
#include "GUI.h"
#include "GUIDEMO.h"
#include "touch.h"
#include "timer.h"
//ALIENTEK Mini STM32�����巶������27
//�ڴ����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
extern void _MY_GetTouchPos(void);
int main(void)
{
	NVIC_Configuration();	 
	delay_init();	    			 //��ʱ������ʼ��	  
	uart_init(115200);	 		//���ڳ�ʼ��Ϊ9600
	LED_Init();		  				//��ʼ����LED���ӵ�Ӳ���ӿ�
 	KEY_Init();							//������ʼ�� 
	TFTLCD_Init();			   	//��ʼ��LCD		 
	tp_dev.init();
//	tp_dev.adjust();
	mem_init();				//��ʼ���ڴ��

	TIM3_Int_Init(999,71);	//1KHZ ��ʱ��1ms 
	TIM6_Int_Init(999,719);	//10ms�ж�
	

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);
	WM_SetCreateFlags(WM_CF_MEMDEV);//�����洢�豸 �ӿ�gui�ٶ�
  GUI_Init();
#if 0
	 _MY_GetTouchPos();
#endif
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringAt("Hello World!", 30, 200);
	GUI_DispStringAt("Hello emWin!", 30, 216);
	GUI_DrawRoundedRect(0,0,200,200,5);
	GUI_DrawRoundedFrame(2,2,180,20,5,2);
	GUI_Delay(3000);
#if 1
	GUIDEMO_Main();
#endif

 while(1)
 {
	tp_dev.scan(0);
	 if(tp_dev.x[0] >0 && tp_dev.x[0]<240 && tp_dev.y[0]>0 && tp_dev.y[0]<320){
		 GUI_DrawPoint(tp_dev.x[0],tp_dev.y[0]);
	 }
	 LED0 = !LED0;
	 GUI_Delay(10);
 }
}











