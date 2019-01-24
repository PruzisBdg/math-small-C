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
|  Set T_IIRFAcc to float or double depending on the precision required.
|
|  Public functions:
|
|	   single 2nd order IIR, canonical (direct II)
|
|	      IIRF2_Init()		- initialise coffs etc
|	      IIRF2_Run()		- run, return result
|
|	   2xn order IIR, multiple 2nd-order, parallel
|
|	      IIRFNx2_Init()
|	      IIRFNx2_Run()
|
----------------------------------------------------------------------------- */

#include "iirfilt_fp.h"
#include "arith.h"


/* ============ IIR Filter: Multiple 2nd order Sections - parallel ======================= */


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRFNx2_Init
|
|     Make / initialise filter block 'f' using buffer RAM 'iir2Blocks' and filter coefficients
|     'coffs'
|
|  DESCRIPTION:
|
|  PARAMETERS:    - 'f'             the (resulting) filter
|                 - 'iir2Blocks'    allocated for filter buffers
|                 - 'coffs'         coffs for each section
|                 - 'numSections'   number of 2nd order sections
|
|  RETURNS:
|     
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void IIRFNx2_Init( S_IIRFNx2        *f,				   /* make this filter 					   */
                       S_IIRF2             *iir2Blocks,     /* using this RAM						   */
                       S_IIRF2_Coffs CONST *coffs, 		   /* set these as the filter coffs	   */
                       U8                  numSections )    /* number 2nd-order sections		   */
{
   S_IIRF2  *s;

   f->numSections = numSections;
   f->iir2 = iir2Blocks;

	/* Init each 2nd-order section */
   for( s = f->iir2 ;numSections; numSections--, coffs++, s++ ) 
   { 
      IIRF2_Init( s, coffs->coffs ); 
   }
}


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRFNx2_Run
|
|     Run multiple 2nd-order parallel filter 'f' on 'in', returning result
|     
|
|  DESCRIPTION:
|
|  PARAMETERS:    - 'f'     the filter
|                 - 'in'    input sample
|
|  RETURNS:       filter output
|     
-------------------------------------------------------------------------------------------------*/

PUBLIC S16 IIRFNx2P_Run( S_IIRFNx2  *f, S16 in ) 
{
   U8          c;
   S_IIRF2     *iir2;
   float       n;

	/* Parallel: apply 'in' to each 2nd-order section, sum outputs */
   for( c = f->numSections, iir2 = f->iir2, n = 0; c; c--, iir2++ ) 
   {
      /* IIRFF2_Run() returns float, not S16 like IIRF2_Run(). In higher order filters
         the output from individual sections may exceed S16, even though the net output
         from the filter remains within S16.   
      */
      n += IIRFF2_Run( iir2, in );     
   }
   return ClipFloatToInt(n);
}

/* ========================== end: IIR Filters ======================================= */
