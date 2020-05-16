#ifndef _PID_operation_INCLUDED_
#define _PID_operation_INCLUDED_

#pragma used+
float float_abs(float a);
void PID_Init (void);
float tS_pid_calc(float REF , float Fdb);
#pragma used-

#endif