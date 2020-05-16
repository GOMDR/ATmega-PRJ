#include <mega128.h>
#include "INT_TIM0_PWM_TIM1.h"

void INT_Tim0_init (void)
{
  //--------------- 8bit Ÿ�̸�0 �����÷ο� ���ͷ�Ʈ ----- //
   TCCR0 = 0x07;   // Ŭ������ 1024
   TCNT0 = 99;     // 10msec ���� �η��ͷ�Ʈ   
   TIMSK = 0x01;   // TOIE0 (Timer/Counter 0 Output OVF) SET (1)
}

void Pwm_Gpio (void)
{
  PORTB = 0xff;   // PORTB �ʱⰪ 
  DDRB = 0xff;    // PORTB ������� ����
  
  PORTA = 0xff;
  DDRA = 0x00;
}

void init_Tim1_Pwm (void)
{ 
  TCCR1A = 0xC2; // 0b1000 0010  , 10bit ������ PWM (MODE10) 
  //TCCR1B = 0x13;  // 0b0001 0011  , 64����     1.25Khz
  TCCR1B = 0x15;  // 0b0001 0101  , 1024����     100hz
  //ICR1 = 100;     
  ICR1 = 78;     
  
  OCR1AH = 0x00;
  OCR1AL = 0x00;
  PORTB.1 = 0;
}

void Tim1_Pwm_Duty (float duty)
{ 
          
  float Cal_duty = 0;
  float IRC_temp = 0;
  
  IRC_temp = ICR1;
  Cal_duty = IRC_temp*(duty/100);
  
  OCR1AH = (((unsigned int)Cal_duty & 0xff00)); 
  OCR1AL = ((unsigned int)Cal_duty & 0x00ff);  
  
  
}

void MotorCW_Run(unsigned char Dir, float duty)
{
      PORTB.0 = Dir;  // IN2   0: ������ ,1:������
      PORTB.1 = 1;  // Drive Enable 1:enable  0:disable   
      Tim1_Pwm_Duty(duty);
}

void MotorCW_Stop(void)
{
  Tim1_Pwm_Duty(0); 
  PORTB.1 = 0;
}


