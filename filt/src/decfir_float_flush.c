/* ------------------------------------------------------------------------------
|
|  DecFIRFP_Flush
|
--------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC void DecFIRFP_Flush( S_DecFIRFP *f, float initVal )
{
   FIRFP_Flush(&f->fir, initVal);
   f->cnt = 0;
   f->acc = 0;
   
   /* So the filter flushes out cleanly when run, set the interpolation points
      equal to the initial output from the FIR filter (which scales input by
      'coffSum').
   */
   f->z1 = initVal * (*(f->coffSum));
   f->z2 = f->z1;
}

// --------------------------------- eof ---------------------------------------- 
