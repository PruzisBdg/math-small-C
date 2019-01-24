/* ------------------------------------------------------------------------------
|
|  DecFIRFP_Run
|
|  Run 'in' thru 'f', returnng the result. The 'in' stream is decimated before
|  the FIR and (linearly) interpolated to give the output.
|
--------------------------------------------------------------------------------*/

#include "firfilt.h"

PUBLIC float DecFIRFP_Run( S_DecFIRFP *f, float in)
{
	float out;

   f->acc += in;                          // Update accumulator
   f->cnt++;                              // and decimator count
   
   if(f->cnt < f->dec)                    // Continue to accumulate?
   {                                      // Return interpolation from z2 -> z1.
      out = f->z2 + ((f->z1 - f->z2) * ((float)f->cnt / f->dec) );
      return out;
   }
   else                                   // else decimate now
   {
      f->z2 = f->z1;                      // Shift history
      f->z1 = FIRFP_Run(&f->fir, f->acc / f->dec);    // Get new output from FIR
      f->acc = 0;                         // Zero accumulator and count for next decimation cycle.
      f->cnt = 0;
      return f->z2;                       // Return oldest; will interpolate forward from there.
   }
}

// --------------------------------- eof -------------------------------------- 
