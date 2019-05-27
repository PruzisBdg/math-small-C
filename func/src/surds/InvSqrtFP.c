#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

/*-----------------------------------------------------------------------------------------
|
| Fast inverse square root.
|
| This is the algorithm known as 0x5F3759DF. It works by using the mantissa of the IEEE-754
| floating point number directly as if it were a log2N of that of the mantissa portion it
| actually represents.
|        'mantissa ,_ 0x5f3759df - ( mantissa >> 1 )'
| does
|        mantissa <- log2( 1/sqrt(mantissa))
| But the result isn't exact because
|        log2(n) ~= n for n = [1.0 .. 2.0]
|  The subsequent Newtons refines the initial estimate.
|
------------------------------------------------------------------------------------------*/

PUBLIC float InvSqrtFP(float f)
{
   U32 i = (0x5f3759df -                 // inverse sqrt root on log2(manstissa(f))
              (*(U32*)&f >> 1 ));        // Read 'f' as U32

   float y = *(float*)&i;

   // Newtons on approximate result.
   y  = y * ( 1.5F - ( f * 0.5F * y * y ) );   // 1st iteration
	return y;

}
// --------------------------------- eof -------------------------------------

