/* -------------------------------------------------------------------------
|
|  Floating point IIR Filter - Multiple 2nd order sections - parallel
|
|  Pruzina 8/9/04
|
|  This is the IIR_ package with floating point accumulators and coefficients
|  in place of 16bit coffs and 32bit accumulators. In an IIR filter when the
|  transistion frequency is small compared to the sample rate the coffs are
|  small and the accumulator values large. The coffs are therefore not precise
|  and the 32 bit accumulators can overrange. This version of the IIR filter avoids
|  these issues at the expense of speed
|
----------------------------------------------------------------------------- */

#include "iirfilt_fp.h"


/* ================= Vector IIR; each section multiple-2nd-order ================== */



// --------- 2 stage


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRFNx2ndVec_Init
|
|     Init multiple 2-section 2nd-order parallel vector filter. Each vector element gets 
|     the same filter
|
|  PARAMETERS:    - 'f'       the (resulting) filter
|                 - 'coffs'   coefficients
|                 - 'vecSize' number of vector elements
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRF2x2ndVec_Init( S_IIRF2x2ndPar      *f,          /* Init this vector-filter  */
                              S_IIRF2_Coffs  CONST *coffs,      /* each channel has the same coffs */
                            U8                     vecSize )
{
   for( ; vecSize; vecSize--, f++ ) 
   {
      IIRFNx2_Init( &f->filt, f->sections, coffs, 2 ); 
   }
}



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



/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRF2x2ndVec_Run
|
|     Run multiple 2nd-order parallel vector filter. 
|
|  DESCRIPTION:
|
|  PARAMETERS:    - 'f'       the filter
|                 - 'in'      input (vector)
|                 - 'out'     output (vector)
|                 - 'vecSize' number of vector elements
|
|  RETURNS:
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
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




// ------------ 3 -stage



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



/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRF3x2ndVec_Init_MultiCoffs
|
|     Init multiple 2nd-order parallel vector filter. Each vector element gets a different
|     filter
|
|  PARAMETERS:    - 'f'       the (resulting) filter
|                 - 'coffs'   an array of coefficients (arrays)
|                 - 'vecSize' number of vector elements
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRF3x2ndVec_Init_MultiCoffs( 
                           S_IIRF3x2ndPar      *f,                   /* Init this vector-filter  */
                           S_IIRF2_Coffs  CONST * CONST * coffs,     /* each channel has different coffs */
                           U8                     vecSize )
{
   for( ; vecSize; vecSize--, f++, coffs++ ) 
   {
      IIRFNx2_Init( &f->filt, f->sections, *coffs, 3 ); 
   }
}



/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRF3x2ndVec_Run
|
|     Run multiple 2nd-order parallel vector filter. 
|
|  DESCRIPTION:
|
|  PARAMETERS:    - 'f'       the filter
|                 - 'in'      input (vector)
|                 - 'out'     output (vector)
|                 - 'vecSize' number of vector elements
|
|  RETURNS:
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRF3x2ndVec_Run( S_IIRF3x2ndPar *f,             /* Run this vector-filter  */
                             S16             *in,            /* from here */
                             S16             *out,           /* to here */
                             U8              vecSize )
{
   for( ; vecSize; vecSize--, f++, in++, out++ ) 
   { 
      *out = IIRFNx2P_Run( &f->filt, *in ); 
   }
}


/* ========================== end: IIR Filters ======================================= */
