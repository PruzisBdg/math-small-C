/* ------------------------------------------------------------------------------
|
|                 FIR Filter with pre-decimator
|
--------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC S16 DecFIR_Flush( S_DecFIR *f, S16 fillValue )
{
   FIR_Flush(&f->fir, fillValue);
   f->cnt = 0;
   f->acc.asS32 = 0;
   return fillValue;
}

// ------------------------------------ eof ------------------------------------------ 
