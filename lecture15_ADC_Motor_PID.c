/*
 * lecture15_ADC_Motor_PID.c
 *
 * Created: 2019-05-31 오후 5:24:27
 * Author: FreeMan
 */

#include <io.h>
#include <stdio.h>
#include <mega128.h>
#include <delay.h>
#include "lecture15_ADC_Motor_PID.h"

//---------------LCD COMMAND Define -------------//
#define CLEAR   0x01 // Clear Display
#define LINE2   0xC0 // 2and Line Move
#define HOME    0x02 // Cursor Home
#define RSHIFT  0x1C // Display Right Shift
#define LSHIFT  0x18 // Display Left Shift
#define DISPON  0x0c // Display On 
#define DISPOFF 0x08 // Display Off

#define RX_COMPLETE 0x80

#define SW0 PINA.0
#define SW1 PINA.1 

unsigned char rx_data; 
char tx_flag = 0; 

char sbuf[50];


float motor_duty_cal_temp =0.0;
float motor_duty_cal =0.0;
//float sat_Error_vaule = 1.0;

void main(void)
{            
  
  INT_Tim0_init();
  Pwm_Gpio();
  init_Tim1_Pwm();
  LCD_Init();
  Init_ADC();
  PID_Init(); 
  UART0_Init();
  
  SREG = 0x80;      // 전역 인터럽트 세트 
  
while (1)
    {
      LCD_Command(HOME);
      LCD_String("AC System ready");
      LCD_Command(LINE2);
      LCD_String("SW0 to start");
      
      if(SW0==0)  //start button
      {
         do{
            Read_ADC_Operation();
            tS_motor_operation();
            LCD_Display();
                
            if(rx_data == 0x41 && tx_flag == 1)
            {
             sprintf(sbuf,"Temp_Data :%4f \r\n",fTemp);        
             TxString(sbuf); 
       
             tx_flag = 0;
            }
          }while((SW0 != 0) && (SW1 != 0));//if switch preesed break untill then this will loop
       
      }
      else if(SW1 == 0)  //emergencty stop button. if this button pressed. motor will stop beside sensor value.
      {
        do{
            LCD_Command(HOME);
            LCD_String("AC System stop");
            MotorCW_Stop();
        }while((SW0!=0) && (SW1 != 0));
      }        
    }
}


void LCD_Display (void)     //LCD dispaly when system running. display Temp, Gas sensor value
{
        sprintf(sbuf,"Temp = %2.1f",fTemp);      
        LCD_Command(HOME);
        LCD_puts(sbuf); 
        delay_ms(10);  
      
        sprintf(sbuf,"Gas = %5d  ",Gas);      
        LCD_Command(LINE2);
        LCD_puts(sbuf); 
        delay_ms(10);  
}

float set_tS_vaule = 32.0;       //target value for start motor. if tempeture over 32'C motor will running
//float tS_pid_calc(float REF , float Fdb);
void tS_motor_operation (void)   //motor operation.
{
   motor_duty_cal_temp = tS_pid_calc(set_tS_vaule,fTemp);   //duty value from PID operation.
   
   if(motor_duty_cal_temp <= 0) // 음수이면 온도가 높다.
   {      
     motor_duty_cal =  float_abs(motor_duty_cal_temp);
     
     if(motor_duty_cal > output_max)
     {
       motor_duty_cal = output_max;
     }
     else if(motor_duty_cal < output_min )
     {
       motor_duty_cal = output_min;
     }               
     
     MotorCW_Run(1,motor_duty_cal); 
   }   
   else if (motor_duty_cal_temp > 0)
   {    
     motor_duty_cal = 0;
     MotorCW_Stop(); 
     ePrev = 0;
     eInteg = 0;
   }
}
// 데이터 수신 ----인터럽트 방식

interrupt [USART0_RXC] void uart0_rx(void)
{
   rx_data = UDR0; 
}

int tcnt = 0;

interrupt [TIM0_OVF] void timer0_ovf_isr (void)
{
  tcnt++;
  if(tcnt == 100)
  {  
    tcnt = 0;
    tx_flag = 1;
  }
  
}