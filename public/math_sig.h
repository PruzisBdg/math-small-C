#ifndef MATHSIG_H
#define MATHSIG_H

#include <stdbool.h>
#include "GenericTypeDefs.h"

/* Essential non-normalising Downsampler.

   Fill 'bucket', size 'outRate' with 'inRate's and acc(mulate) corresponding input samples
   until bucket is full or past full.  'acc' gets gets a proportionate part of the last
   input sample; 'acc' is emptied to output and refilled with the leftover. 'overspill'
   gets the remainder of 'inRate'.
*/
typedef struct {U8 in, out;} S_ResampleRatesU8;

typedef struct {
   S32 acc;                // Accumulates incoming samples & frac tions thereof.
   U8  bucket,            // Fill this with (divisible) token of incoming samples...
       inRate, outRate;
} S_DownSampleS16;

PUBLIC bool DownSampleS16_Init(S_DownSampleS16 *d, S_ResampleRatesU8 const *rr);
PUBLIC bool DownSampleS16_SetRates(S_DownSampleS16 *d, S_ResampleRatesU8 const *rr);
PUBLIC bool DownSampleS16_Run(S_DownSampleS16 *d, S32 *out, S16 in);
PUBLIC bool DownSampleS16_Flush(S_DownSampleS16 *d, S32 *out);

#endif // MATHSIG_H

// -------------------------------------------- eof ---------------------------------------------------
