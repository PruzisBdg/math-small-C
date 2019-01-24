/*-------------------------------------------------------------------------------------------------
|
|  FIRFP_Make
|
|  Make floating point FIR filter 'f'.
|
|  PARAMETERS:   'f'     - the filter
|                'buf'   - buffer, must be at least as long as the coffs
|                'coffs' - filter coefficients
|                'taps'  - number of filter coffs
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void FIRFP_Make( S_FIRFP *f, float *buf, float CONST *coffs, U8 taps )
{
   f->coffs = coffs;
   f->taps = taps;
   f->buf = buf;
   
   #ifdef _USE_ARRAY_INDICES
   f->end = taps - 1;
   #else
   f->end = f->buf + taps - 1;
   #endif

   FIRFP_Reset(f, 0);
}

// -------------------------------------- eof ----------------------------------------------------- 
