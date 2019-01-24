/* ------------------------------------------------------------------------------
|
|                 FIR Filter with pre-decimator
|
|  Run filter, using a 16bit accumulator See 'DecFIR_Run()' for a 32 bit accumulator.
|
|  If the decimation ratio isn't an exact power of 2 and a 16bit accumulator won't 
|  overflow, then use this function to avoid the penalty of a 32bit divide.
|
|  Note that 'out' is modified only when the decimation rools over.
|
--------------------------------------------------------------------------------*/

#include "firfilt.h"
#include "arith.h"

PUBLIC BIT DecFIR_RunS( S_DecFIR *f, S16 *out, S16 in)
{
   f->acc.asS16 = AplusBS16(f->acc.asS16, in);     // Update accumulator
   f->cnt++;                                       // and decimator count
   
   if(f->cnt < f->dec)                             // Continue to accumulate?
   {
      return 0;                                    // then return 0
   }
   else                                            // else decimate now
   {
      if(f->rShift)                                // Divide using a right-shift?
      {                                            // then right-shift accumulator to 'out'
         *out = FIR_Run(&f->fir, f->acc.asS16 >> f->rShift);
      }
      else
      {                                            // else divide accumulator to 'out'
         *out = FIR_Run(&f->fir, f->acc.asS16 / f->dec);
      }
      f->acc.asS16 = 0;                            // Zero accumulator and count for next decimation cycle.
      f->cnt = 0;
      return 1;
   }
}

// --------------------------------- eof ----------------------------------- 
