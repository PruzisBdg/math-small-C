/*---------------------------------------------------------------------------
|
|                 Scalar Accumulator with Deviation Sum
|
|--------------------------------------------------------------------------*/

#include "spj_stdint.h"
#include "arith.h"

PUBLIC S16 AccDev_MeanDev(S_AccDev *a)
{
   return !a->cnt ? 0 : (S16)(a->devSum / a->cnt);
}

// -------------------------------- eof -------------------------------------
