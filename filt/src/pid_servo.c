/*---------------------------------------------------------------------------
|
|                PID Servo with windup limits
|
|--------------------------------------------------------------------------*/

#include "math_common.h"
#include "arith.h"
#include "pid_servo.h"

/*-----------------------------------------------------------------------------------------
|
|  PIDServo_Init()
|
------------------------------------------------------------------------------------------*/

PUBLIC void PIDServo_Init(S_PIDServo *sv, S_PIDServoCfg CONST *cfg)
{
   sv->cfg = cfg;   
}


/*-----------------------------------------------------------------------------------------
|
|  PIDServo_Reset()
|
------------------------------------------------------------------------------------------*/

PUBLIC void PIDServo_Reset(S_PIDServo *sv, S16 target)
{
   sv->errSum = 0;         // zero the error sum
   sv->prevX = target;     // previous input starts at the target value
}


/*-----------------------------------------------------------------------------------------
|
|  PIDServo_Run()
|
|  Given the next input sample 'in', run servo 'sv' and return an updated output. 
|
------------------------------------------------------------------------------------------*/

PUBLIC S16 PIDServo_Run(S_PIDServo *sv, S16 targetX, S16 x)
{
   S16 diff;
   S_PIDServoCfg CONST * cfg;

   sv->errSum -= x;                          // Update the error accumulator
   diff = AplusBS16(x, -sv->prevX);          // Get the difference between the new input and the previous one
   sv->prevX = x;                            // Cache the current input as previous - for the next time

   cfg = sv->cfg;                            // Cache to compact code
   ClipS32(sv->errSum, -cfg->errAccMax, cfg->errAccMax );  // Limit backlash by clipping the accumulated error
   
   /*
      new_y = pGain * (x - targetX)  + iGain * accumulated_error  + dGain * (x - prevX)
      
      new_y is limited to 'outLimits'
   */
   return ClipS16
   (
      ClipS32toS16
      (
         cfg->outCenter +
         ( 
            (
               MulS16(cfg->pGain, AplusBS16(x, -targetX)) +
               MulS16(cfg->iGain, sv->errSum) + 
               MulS16(cfg->dGain, diff)
            ) 
            / cfg->outScale
         )
      ),
      cfg->outLimits.min,
      cfg->outLimits.max
   );
}

// ----------------------------- eof --------------------------------------

 
