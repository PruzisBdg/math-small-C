/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIR_Make
|
|  DESCRIPTION:
|
|  Make FIR 'f'.
|
|  PARAMETERS:   'f'     - the filter
|                'buf'   - buffer
|                'coffs' - filter coefficients
|                'taps'  - number of filter taps
|
|  RETURNS:
|     
|
|	DATE		AUTHOR		DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void FIR_Make( S_FIR *f, S16 *buf, S16 CONST *coffs, U8 taps, U8 rShift )
{
   f->coffs = coffs;
   f->taps = taps;
   f->buf = buf;
   f->rShift = rShift;
   
   #ifdef _USE_ARRAY_INDICES
   f->end = taps - 1;
   #else
   f->end = f->buf + taps - 1;
   #endif

   FIR_Reset(f, 0);
}



// ---------------------------------- eof ------------------------------------------ 
