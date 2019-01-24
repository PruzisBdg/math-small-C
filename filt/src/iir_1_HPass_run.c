 /*---------------------------------------------------------------------------
|
|                  1st-order High Pass IIR filter
|
|                    HPass = input - LPass
|
|--------------------------------------------------------------------------*/

#include "math_common.h"
#include "iirFilt1.h"
#include "arith.h"

PUBLIC S16 IIR1_HPass_Run( S_IIR1 RAM_IS *f, S16 in )
{
   /* Do summation with clipped arithmetic, in case 'in' steps > 32768
   
      N.B On 8051, code is most compact with 'in' as 2nd parm to AddTwoS16()
   */
   return AplusBS16(-IIR1_LPass_Run(f, in), in);
}

// -------------------------- eof --------------------------------------

