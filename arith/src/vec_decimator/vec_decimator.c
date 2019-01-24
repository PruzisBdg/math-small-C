// --------------------------- Vector Decimator ----------------------------------------

#include "arith.h"
#include "util.h"    // ZeroBytesU8()

/*-----------------------------------------------------------------------------------------
|
|  VecDecimator_Init()
|
------------------------------------------------------------------------------------------*/

PUBLIC void VecDecimator_Init(S_VecDecimator *d, S_VecDecimatorCfg CONST *cfg)
{
   d->cfg = cfg;
   d->cnt = 0;
   ZeroBytesU8(cfg->acc, sizeof(S32)*cfg->size);
}

/*-----------------------------------------------------------------------------------------
|
|  VecDecimator_Run()
|
------------------------------------------------------------------------------------------*/

PUBLIC BIT VecDecimator_Run(S_VecDecimator *d)
{
   U8 c;

   for( c = 0; c < d->cfg->size; c++ )                // For each vector element
   {
      d->cfg->acc[c] += d->cfg->in[c];                // Add current input to accumulator
   }
   d->cnt++;                                          // and bump input count

   if( d->cnt < d->cfg->div )                         // Accumulate more?
   {
      return 0;                                       // then return 0, output not updated yet.
   }
   else                                               // else accumulated emough, time to decimate
   {
      d->cnt = 0;                                     // zero count for next go-around

      for( c = 0; c < d->cfg->size; c++ )             // For each vector element
      {
         d->cfg->out[c] += d->cfg->acc[c]/d->cfg->div;// output is acc/decimation_ratio
         d->cfg->acc[c] = 0;                          // and zero accumaulator for next go-around
      }
      return 1;
   }
}

// --------------------------------------- eof ----------------------------------------------
