/*---------------------------------------------------------------------------
|
|                 Scalar Accumulator with Deviation Sum
|
|--------------------------------------------------------------------------*/

#include "GenericTypeDefs.h"
#include "arith.h"

PUBLIC S16 AccDev_DevSum(S_AccDev *a)
{
   return ClipS32toS16(a->devSum);
}
 
 // -------------------------------- eof ------------------------------------- 
