/* -------------------------------------------------------------------------
|
|  Integer IIR Filter - Multiple 2nd order sections - parallel
|
|  Pruzina 6/3/03
|
|	Gain of 2nd-order IIRs is >>14 i.e they will have a gain of 1 when
|	used with 14bit coffs. 14bit coffs give reasonable accuracy up to 8th
|	order and allow considerable headroom with 12-14 bit data.
|
|	Public functions:
|
|		single 2nd order IIR, canonical (direct II)
|
|		iir2_Init()		- initialise coffs etc
|		iir2_Run()		- run, return result
|
|		2xn order IIR, multiple 2nd-order, parallel
|
|		iirNx2_Init()
|		iirNx2_RunP()
|
----------------------------------------------------------------------------- */

#include "iirfilt.h"


/* ================ Multiple 2nd order Sections - parallel ======================= */


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIRNx2_Init
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
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void iirNx2_Init( iirNx2_S   _IIR_Mem  *f,				   /* make this filter                 */ 
                         iir2_S     _IIR_Mem  *iir2Blocks,     /* using this RAM	                  */
                         iir2_S_Coffs CONST   *coffs, 		   /* set these as the filter coffs    */
                         U8                   coffsScalePwr2,  /* coeffs scale, as power of 2      */
                         U8                   numSections )    /* number 2nd-order sections		   */
{

   iir2_S _IIR_Mem *s;

   f->numSections = numSections;
   f->iir2 = iir2Blocks;

	/* Init each 2nd-order section */
   for( s = f->iir2 ;numSections; numSections--, coffs++, s++ ) 
      { iir2_Init( s, coffs->coffs, coffsScalePwr2 ); }

}


/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  iirNx2P_Run
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
|
|	DATE        AUTHOR		      DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

PUBLIC S16 iirNx2P_Run( iirNx2_S _IIR_Mem *f, S16 in ) 
{
   U8  c;
   iir2_S _IIR_Mem * iir2;
   S16 n;

	/* Parallel: apply 'in' to each 2nd-order section, sum outputs */
   for( c = f->numSections, iir2 = f->iir2, n = 0; c; c--, iir2++ ) 
   {
      n += iir2_Run( (iir2_S _IIR_Mem *)iir2, in );
   }
   return n;
}




/* ================= Vector IIR; each section multiple-2nd-order ================== */





/* ----------------------------- eof -------------------------------------- */
