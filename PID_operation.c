
#include <stdio.h>
#include "PID_operation.h"

float output_max = 90.0;
float output_min = 1.0;

float tS_Err = 0.0;       /* PID - Variable: Error */
float tS_Ref = 0.0;       /* PID - Input: Reference input */
float tS_Fdb = 0.0;       /* PID - Input: Feedback input  */
float tS_SatErr = 0.0;    /* PID - Variable: Saturated difference */

float tS_Kp = 0.0;        /* PID - Parameter: Proportional gain */
float tS_Ki = 0.0;        /* PID - Parameter: Integral gain */  
float tS_Kd = 0.0;        /* PID - Parameter: Derivative gain */

float tS_PWM_PIDOut = 0.0; /* PID - Output: PID output */

signed long ePrev;
signed long eInteg;
    
void PID_Init (void)
{

 tS_Err = 0.0;       
 tS_Ref = 0.0;       
 tS_Fdb = 0.0;       
 tS_SatErr = 0.0;
 
 tS_Kp = 30.0;    
 tS_Ki = 0.000;
        
 tS_Kd = 0.0;  

 tS_PWM_PIDOut = 0.0;     
    
 ePrev = 0;    
 eInteg = 0;    
}

//float start_pwm = 0.0;
 
// (Kp * ����) + ( Ki*������ ������ ) + ( Kd * ��ȸ ������ �� �� )  
  
float tS_pid_calc(float REF , float Fdb)
{
    
     float motor_output = 0;     
     signed long D_val = 0;
    
      tS_Ref = REF;
      tS_Fdb = Fdb;
    
    
   tS_Err = tS_Ref - tS_Fdb;                // Err = Ref (���ذ�or ������)- Fdb (FeedBack �� ,���簪)
                                            // p = tS_Kp * Err              ����              ���
                                            // i = tS_Ki * eInteg           ������ ������     ����
                                            // d = tS_Kd * (ePrev - tS_Err) ��ȸ ������ �� �� �̺�
    /* Compute the saturate difference ��ȭ ���� ���*/                                         
   if(ePrev > tS_Err) {                     
      D_val = ePrev - tS_Err;               
     }
   else if(tS_Err > ePrev) {
      D_val =  -1 * (tS_Err - ePrev);
     }
     //                    P               I                 D
     tS_PWM_PIDOut = tS_Kp * tS_Err + tS_Ki * eInteg +   tS_Kd * D_val;
         
     motor_output = tS_PWM_PIDOut;
     
     eInteg += tS_Err;                      
     ePrev = tS_Err;                       
              
     if( tS_Err > 0)
     {
       eInteg = 0;
       ePrev = 0;
     }  
     if(eInteg > 10)
     {
       eInteg = 0;
     }                           
      
   return motor_output;
}

float float_abs(float a)
{
	if(a<0)	a	= -a;
	
	return a;
}