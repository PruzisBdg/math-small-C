
#include "iirfilt_fp.h"

/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRFNx2ndVec_Run
|
|     Run multiple 2nd-order parallel vector filter. 
|
|  PARAMETERS:    - 'f'       the filter
|                 - 'in'      input (vector)
|                 - 'out'     output (vector)
|                 - 'vecSize' number of vector elements
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRFNx2ndVec_Run( S_IIRFNx2   *f,             /* Run this vector-filter  */
                             S16          *in,            /* from here */
                             S16          *out,           /* to here */
                             U8           vecSize )
{
   for( ; vecSize; vecSize--, f++, in++, out++ ) 
   { 
      *out = IIRFNx2P_Run( f, *in ); 
   }
}


// ------------------------------- eof -------------------------------------------------


