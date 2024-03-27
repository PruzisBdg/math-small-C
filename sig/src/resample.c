#include "common.h"
#include "math_common.h"
#include "math_sig.h"
#include "arith.h"

/* ---------------------------- DownSmplS16_Init -----------------------------------------

   Clear 'r' accumulators and buckets. Set 'inRate' & 'outRate'.

   Return false if 'outRate' > 'inRate' - this is a DownSampler only.
*/
PUBLIC bool DownSmplS16_Init(S_DownSmplS16 *d, S_ResampleRatesU8 const *rr)
{
   *d = (S_DownSmplS16){0};

   if(rr->out > rr->in || rr->out == 0 || rr->in == 0) {    // Not a downsampling?
      return false;                                         // Then fail.
   }
   else {
      d->inRate  = rr->in; d->outRate = rr->out;            // else set reampling parms.
      return true;                                          // and say success.
   }
}


/* ------------------------------ DownSmplS16_SetRates ----------------------------------

   Unprotected update of 'inRate' and 'outRate'
*/
PUBLIC bool DownSmplS16_SetRates(S_DownSmplS16 *d, S_ResampleRatesU8 const *rr)
{
   d->inRate = rr->in; d->outRate = rr->out;
   return true;
}

PUBLIC bool DownSmplS16_SetOutRate(S_DownSmplS16 *d, U8 outRate)
{
   d->outRate = outRate;
   return true;
}

/* ---------------------------- DownSmplS16_Run -----------------------------------------

   Apply 'in' to 'r'. Return true if there's a fresh output sample, which will be in 'out';
   otherwise 'out' will be unchanged.

   DownSmplS16 is non-normalising; samples from 'in' to 'out' are scaled by 'inRate'/'outRate'.

   DownSmplS16 does not leak; when 'r' is flushed the sum of all 'out's will equal
   sum of all 'in's.
*/
PUBLIC bool DownSmplS16_Run(S_DownSmplS16 *d, S32 *out, S16 in)
{
   U16 newFill = d->bucket + d->outRate;        // Add 'outRate' to 'bucket', which may overflow (so U16).

   if(newFill < d->inRate)                      // 'bucket' not full yet?
   {
      d->acc += in;                             // then accumulate all of 'in'.
      d->bucket = newFill;                      // and update 'bucket' with new level.
      return false;                             // No new output sample.
   }
   else                                         // else 'bucket' is full, and then some maybe.
   {
      U8 overspill = newFill - d->inRate;       // Overspill, if any, is this.

      // Overage fraction of 'in'
      S16 smplRem = AmulBdivC_S16_U8_U8(in, overspill, d->outRate); //
      // Add to 'acc' that fraction of 'in' which fills 'bucket'. Then push to 'out'
      *out = d->acc + (in - smplRem);
      // Restart 'acc' with the overage of 'in'.
      d->acc = smplRem;

      d->bucket = overspill;                    // Restart 'bucket' with 'overspill'
      return true;                              // Says there's a fresh output sample.
   }
}

/* ---------------------------- DownSmplS16_Flush -----------------------------------------

   Empty 'r' to 'out' (retaining the resampling parameters).
*/
PUBLIC bool DownSmplS16_Flush(S_DownSmplS16 *d, S32 *out)
{
   *out = d->acc;
   d->acc = 0; d->bucket = 0;    // Clear both 'acc' and 'bucket'.
   return true;                  // Always succeeds.
}


// -------------------------------------------- eof ----------------------------------------------------
