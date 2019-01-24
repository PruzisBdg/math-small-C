/*-------------------------------------------------------------------------------------------------
|
|  FIRFP_Reset
|
|  Reset floating-point FIR filter 'f'. Fill with 'initValue'
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void FIRFP_Reset( S_FIRFP *f, float initValue ) 
{
   #ifdef _USE_ARRAY_INDICES
   f->put = 0;
   #else
   f->put = f->buf;
   #endif
   
   FIRFP_Flush(f, initValue);
}

// ----------------------------------- eof ----------------------------------------------------- 
