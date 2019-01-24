/*---------------------------------------------------------------------------
|
|                 Scalar Accumulator with Deviation Sum
|
|--------------------------------------------------------------------------*/

#include "GenericTypeDefs.h"
#include "arith.h"

PUBLIC void AccDev_Clear(S_AccDev *a)
{
   a->acc = 0;
   a->cnt = 0;
   a->devSum = 0;
}
 
// -------------------------------- eof ------------------------------------- 
