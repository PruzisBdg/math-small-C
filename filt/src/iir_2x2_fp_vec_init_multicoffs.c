

#include "iirfilt_fp.h"

/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRFNx2ndVec_Init_MultiCoffs
|
|     Init multiple 2-section 2nd-order parallel vector filter. Each vector element 
|     gets a different filter
|
|  PARAMETERS:    - 'f'       the (resulting) filter
|                 - 'coffs'   an array of coefficients (arrays)
|                 - 'vecSize' number of vector elements
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRF2x2ndVec_Init_MultiCoffs( 
                           S_IIRF2x2ndPar      *f,                   /* Init this vector-filter  */
                           S_IIRF2_Coffs  CONST * CONST * coffs,     /* each channel has different coffs */
                           U8                     vecSize )
{
   for( ; vecSize; vecSize--, f++, coffs++ ) 
   {
      IIRFNx2_Init( &f->filt, f->sections, *coffs, 2 ); 
   }
}


// -------------------------------- eof ------------------------------------------
