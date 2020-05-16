#ifndef _INT_TIM0_PWM_TIM1_INCLUDED_
#define _INT_TIM0_PWM_TIM1_INCLUDED_

#pragma used+

void INT_Tim0_init (void);
void Pwm_Gpio (void);
void init_Tim1_Pwm (void);
void Tim1_Pwm_Duty (float duty);
void MotorCW_Run(unsigned char Dir, float duty);
void MotorCW_Stop(void);

#pragma used-

#endif