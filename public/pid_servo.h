/*---------------------------------------------------------------------------
|
|                PID Servo with windup limits
|
|
|
|
|
|
|   
|      Rev 1.0   May 19 2009 12:56:28   spruzina
|   Initial revision.
|  
|--------------------------------------------------------------------------*/

#ifndef PID_SERVO_H
#define PID_SERVO_H

#include "math_common.h"
 
typedef struct
{
   S16 min, max;
} S_Limits;

typedef struct
{
   S16      pGain,      // proportional gain
            iGain,      // integral gain
            dGain,      // differential gain
            outScale,   // output scaling (denominator)
            outCenter;  // output operating point (zero input error gives this output)
   S32      errAccMax;  // error accumlator min/max            
   S_Limits diffLimits, // limits on differential error
            outLimits;  // limits on output
} S_PIDServoCfg;

typedef struct
{
   S_PIDServoCfg CONST *cfg;
   S16      prevX;      // previous input, for the differential error
   S32      errSum;     // the integral error   
} S_PIDServo;


PUBLIC void PIDServo_Init(S_PIDServo *sv, S_PIDServoCfg CONST *cfg);
PUBLIC void PIDServo_Reset(S_PIDServo *sv, S16 target);
PUBLIC S16 PIDServo_Run(S_PIDServo *sv, S16 targetX, S16 x);

#endif // PID_SERVO_H 
