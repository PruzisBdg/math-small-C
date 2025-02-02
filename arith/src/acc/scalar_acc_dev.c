/*---------------------------------------------------------------------------
|
|                 Scalar Accumulator with Deviation Sum
|
|--------------------------------------------------------------------------*/

#include "spj_stdint.h"
#include "arith.h"

PUBLIC void AccDev_Add(S_AccDev *a, S16 n)
{
   a->acc += n;
   a->cnt++;

   if(a->cnt > 1)
      { a->devSum += AbsDiffS16(n, a->acc / a->cnt); }
}

PUBLIC S16 AccDev_Read(S_AccDev *a)
{
   return !a->cnt ? 0 : (S16)(a->acc / a->cnt);
}

// -------------------------------- eof -------------------------------------


