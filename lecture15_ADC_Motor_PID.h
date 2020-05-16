#ifndef _lecture15_ADC_Motor_PID_INCLUDED_
#define _lecture15_ADC_Motor_PID_INCLUDED_

#pragma used+

void LCD_Display (void);
void tS_motor_operation (void);



extern void LCD_Init(void);
extern void LCD_Command(unsigned char byte);
extern void LCD_String(char flash str[]);
extern void DataWirte(unsigned char byte);
extern void LcdGotoXY(unsigned char x , unsigned char y);
extern void LCD_puts(const char *s);

extern void Init_ADC (void);
extern void Read_ADC_Operation(void);
extern unsigned int Gas;
extern float fTemp;

extern void INT_Tim0_init (void);
extern void Pwm_Gpio (void);
extern void init_Tim1_Pwm (void);
extern void Tim1_Pwm_Duty (float duty);
extern void MotorCW_Run(unsigned char Dir, float duty);
extern void MotorCW_Stop(void);


extern void UART0_Init (void);
extern void TxChar(unsigned char chr);
extern char RXchar(void);
extern void TxString(unsigned char *str);

extern char tx_flag;

extern float float_abs(float a);
extern void PID_Init (void);
extern float tS_pid_calc(float REF , float Fdb);

extern signed long ePrev;
extern signed long eInteg;

extern float output_max;
extern float output_min;

#pragma used-

#endif
