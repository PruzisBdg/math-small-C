/*-------------------------------------------------------------------------------------------------
|
|  FIR_Fill
|
|  Fill 'f' from 'fillVec'.
|
|  PARAMETERS:    - 'f'  the filter
|                 - 'fillVec'  vector to insert
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"
#include "util.h"

PUBLIC void FIR_Fill ( S_FIR *f, S16 const *fillVec ) 
{

   CopyIntsU8( f->buf, fillVec, f->taps );
   f->put = f->end;       /* 1st sample, in time-order, is at the end of the buffer */
}

// ------------------------------ eof -------------------------------------- 
