/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIR_Reset
|
|  DESCRIPTION:
|     Make filter 'f' from 'cfg'. The filter is flushed with 'initValue'
|
|  PARAMETERS:    - 'f'  the filter
|                 - 'coffs'  new filter coefficients
|
|  RETURNS:
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void FIR_Reset( S_FIR *f, S16 initValue ) 
{
   #ifdef _USE_ARRAY_INDICES
   f->put = 0;
   #else
   f->put = f->buf;
   #endif
   
   FIR_Flush(f, initValue);
}

// ----------------------------------- eof -------------------------------------------- 
