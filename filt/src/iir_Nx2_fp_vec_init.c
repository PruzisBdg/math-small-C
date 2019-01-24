

#include "iirfilt_fp.h"

/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRFNx2ndVec_Init
|
|     Init multiple 2-section 2nd-order parallel vector filter. Each vector element 
|     gets the same filter
|
|  PARAMETERS:    - 'f'       the (resulting) filter
|                 - 'coffs'   an array of coefficients 
|                 - 'vecSize' number of vector elements
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRFNx2ndVec_Init( 
               S_IIRFNx2                 *filt,       /* Init this vector-filter                   */
               S_IIRF2           * const *sections,   /* with these sections for each filter       */
               S_IIRF2_Coffs_Multi CONST *coffs,      /* each channel has these coffs              */
               U8                         vecSize )   /* Vector is this wide                       */
{
   for( ; vecSize; vecSize--, filt++, sections++ ) 
   {
      IIRFNx2_Init( filt, *sections, coffs->coffsOneSection, coffs->numSections ); 
   }
}


// -------------------------------- eof ------------------------------------------
