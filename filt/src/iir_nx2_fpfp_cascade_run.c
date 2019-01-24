/*-------------------------------------------------------------------------------------------------
|
|  IIRFFNx2_Run
|
|  Run multiple 2nd-order cascade filter 'f' on 'in', returning result. 
|
|  This version takes a float as a parameter and return the result as a float.
|
|  PARAMETERS:    - 'f'     the filter
|                 - 'in'    input sample
|
|  RETURNS:       filter output (as a float)
|     
-------------------------------------------------------------------------------------------------*/

#include "iirfilt_fp.h"

PUBLIC float IIRFFNx2C_Run( S_IIRFNx2  *f, float in ) 
{
   U8       c;
   float    n;

	/* Parallel: apply 'in' to each 2nd-order section, sum outputs */
   for( c = 0, n = in; c < f->numSections; c++ ) 
      { n = IIRFF2_Run( &f->iir2[c], n ); }
      
   return n;
}

// -------------------------------- eof --------------------------------------------------  
