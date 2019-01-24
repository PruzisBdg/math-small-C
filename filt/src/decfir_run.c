/* ------------------------------------------------------------------------------
|
|                 FIR Filter with pre-decimator
|
|  Run filter, using a 32bit accumulator See 'DecFIR_RunS()' for a 16 bit accumulator.
|
|  Note that 'out' is modified only when the decimation rools over.
|
--------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC BIT DecFIR_Run( S_DecFIR *f, S16 *out, S16 in)
{
   f->acc.asS32 += in;                    // Update accumulator
   f->cnt++;                              // and decimator count
   
   if(f->cnt < f->dec)                    // Continue to accumulate?
   {
      return 0;                           // then return 0
   }
   else                                   // else decimate now
   {
      if(f->rShift)                       // Divide using a right-shift?
      {                                   // then right-shift accumulator to 'out'
         *out = FIR_Run(&f->fir, f->acc.asS32 >> f->rShift);
      }
      else
      {                                   // else divide accumulator to 'out'
         *out = FIR_Run(&f->fir, f->acc.asS32 / f->dec);
      }
      f->acc.asS32 = 0;                   // Zero accumulator and count for next decimation cycle.
      f->cnt = 0;
      return 1;
   }
}

// ------------------------------------- eof ------------------------------------- 
