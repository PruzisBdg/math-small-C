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
} S_DownSmplS16;

PUBLIC bool DownSmplS16_Init(S_DownSmplS16 *d, S_ResampleRatesU8 const *rr);
PUBLIC bool DownSmplS16_SetRates(S_DownSmplS16 *d, S_ResampleRatesU8 const *rr);
PUBLIC bool DownSmplS16_SetOutRate(S_DownSmplS16 *d, U8 outRate);
PUBLIC bool DownSmplS16_Run(S_DownSmplS16 *d, S32 *out, S16 in);
PUBLIC bool DownSmplS16_Flush(S_DownSmplS16 *d, S32 *out);

#endif // MATHSIG_H

// -------------------------------------------- eof ---------------------------------------------------
