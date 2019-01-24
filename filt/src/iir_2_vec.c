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
|		iirNx2P_Run()
|
----------------------------------------------------------------------------- */

#include "iirfilt.h"


/* ================= Vector IIR; each section multiple-2nd-order ================== */




/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIR2x2ndVec_Init
|
|     Init multiple 2nd-order parallel vector filter. Each vector element gets the same
|     filter
|
|  DESCRIPTION:
|
|  PARAMETERS:    - 'f'       the (resulting) filter
|                 - 'coffs'   coefficients
|                 - 'vecSize' number of vector elements
|
|  RETURNS:
|
|	DATE        AUTHOR            DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

PUBLIC void iir2x2ndVec_Init( iir2x2ndPar_S _IIR_Mem *f,                // Init this vector-filter 
                            iir2_S_Coffs  CONST      *coffs,            // each channel has the same coffs
                            U8                        coffsScalePwr2,   // which are scaled thus
                            U8                        vecSize ) 
{
   for( ; vecSize; vecSize--, f++ )
      { iirNx2_Init( &f->filt, f->sections, coffs, coffsScalePwr2, 2 ); }
}



/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  IIR2x2ndVec_Run
|
|     Init multiple 2nd-order parallel vector filter. Each vector element gets the same
|     filter
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

PUBLIC void iir2x2ndVec_Run( iir2x2ndPar_S _IIR_Mem *f,             // Run this vector-filter 
                           S16      _IIR_Mem *in,            // from here
                           S16      _IIR_Mem *out,           // to here
                           U8                       vecSize ) 
{
   for( ; vecSize; vecSize--, f++, in++, out++ )
      { *out = iirNx2P_Run( &f->filt, *in ); }
}




/* ----------------------------- eof -------------------------------------- */
