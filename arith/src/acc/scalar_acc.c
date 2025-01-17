/*---------------------------------------------------------------------------
|
|                          Scalar Accumulator
|
|--------------------------------------------------------------------------*/

#include "spj_stdint.h"
#include "arith.h"

PUBLIC void Acc_Add(S_Acc *a, S16 n)
{
   a->acc += n;
   a->cnt++;
}

PUBLIC void Acc_Clear(S_Acc *a)
{
   a->acc = 0;
   a->cnt = 0;
}

PUBLIC S16 Acc_Read(S_Acc *a)
{
   return !a->cnt ? 0 : (S16)(a->acc / a->cnt);
}

PUBLIC S16 Acc_ReadAndClear(S_Acc *a)
{
   S16 rtn;
   rtn = Acc_Read(a);
   Acc_Clear(a);
   return rtn;
}

 // -------------------------------- eof -------------------------------------


