
#include "iirfilt_fp.h"

/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRF2x2ndVec_Run
|
|     Run multiple 2nd-order parallel vector filter. 
|
|  PARAMETERS:    - 'f'       the filter
|                 - 'in'      input (vector)
|                 - 'out'     output (vector)
|                 - 'vecSize' number of vector elements
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRF2x2ndVec_Run( S_IIRF2x2ndPar *f,             /* Run this vector-filter  */
                             S16             *in,            /* from here */
                             S16             *out,           /* to here */
                             U8              vecSize )
{
   for( ; vecSize; vecSize--, f++, in++, out++ ) 
   { 
      *out = IIRFNx2P_Run( &f->filt, *in ); 
   }
}


// ------------------------------- eof -------------------------------------------------


