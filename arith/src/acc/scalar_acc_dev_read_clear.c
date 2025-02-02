/*---------------------------------------------------------------------------
|
|                 Scalar Accumulator with Deviation Sum
|
|--------------------------------------------------------------------------*/

#include "spj_stdint.h"
#include "arith.h"

PUBLIC S16 AccDev_ReadAndClear(S_AccDev *a)
{
   S16 rtn;
   rtn = AccDev_Read(a);
   AccDev_Clear(a);
   return rtn;
}

 // -------------------------------- eof -------------------------------------
