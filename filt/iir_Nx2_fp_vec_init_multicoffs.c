

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
|  $Workfile:   iir_Nx2_fp_vec_init_multicoffs.c  $
|
|  $Header:   Q:/Software/Archive/CSI_Software_DataBase/archives/Common/spj/math/filt/iir_Nx2_fp_vec_init_multicoffs.c-arc   1.0   May 06 2013 12:28:54   spruzina  $
|
|  $Log:   Q:/Software/Archive/CSI_Software_DataBase/archives/Common/spj/math/filt/iir_Nx2_fp_vec_init_multicoffs.c-arc  $
|   
|      Rev 1.0   May 06 2013 12:28:54   spruzina
|   Initial revision.
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRFNx2ndVec_Init_MultiCoffs( 
               S_IIRFNx2                 *filt,       /* Init this vector-filter                   */
               S_IIRF2          * const  *sections,   /* with these sections for each filter       */
               S_IIRF2_Coffs_Multi CONST *coffs,      /* each channel has different bank of coffs  */
               U8                         vecSize )   /* Vector is this wide                       */
{
   for( ; vecSize; vecSize--, filt++, coffs++, sections++ ) 
   {
      IIRFNx2_Init( filt, *sections, coffs->coffsOneSection, coffs->numSections ); 
   }
}


// -------------------------------- eof ------------------------------------------
