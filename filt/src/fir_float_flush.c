/*-------------------------------------------------------------------------------------------------
|
|  FIRFP_Flush
|
|  Fill entire buffer of floating point FIR filter 'f' with 'fillValue'
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"
#include "util.h"       // FillFloatsU8()

PUBLIC void FIRFP_Flush( S_FIRFP *f, float fillValue )
{
   FillFloatsU8( f->buf, fillValue, f->taps );
}

// ----------------------------- eof -------------------------------------------- 
