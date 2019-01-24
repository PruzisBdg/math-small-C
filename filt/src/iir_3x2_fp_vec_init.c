
#include "iirfilt_fp.h"

/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRF3x2ndVec_Init
|
|     Init multiple 2nd-order parallel vector filter. Each vector element gets the same
|     filter
|
|  PARAMETERS:    - 'f'       the (resulting) filter
|                 - 'coffs'   coefficients
|                 - 'vecSize' number of vector elements
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRF3x2ndVec_Init( S_IIRF3x2ndPar      *f,          /* Init this vector-filter  */
                              S_IIRF2_Coffs  CONST *coffs,      /* each channel has the same coffs */
                            U8                     vecSize )
{
   for( ; vecSize; vecSize--, f++ ) 
   {
      IIRFNx2_Init( &f->filt, f->sections, coffs, 3 ); 
   }
}



// ------------------------------- eof -------------------------------------------------


