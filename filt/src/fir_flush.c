 /*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIR_Flush
|
|  DESCRIPTION:
|     Fill entire buffer of 'f' with 'fillValue'
|
|  PARAMETERS:    - 'f'  the filter
|                 - 'fillValue'  vector to insert
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"
#include "util.h"

PUBLIC void FIR_Flush( S_FIR *f, S16 fillValue )
{
   FillIntsU8( f->buf, fillValue, f->taps );
}

// ---------------------------------- eof -------------------------------------------------------
