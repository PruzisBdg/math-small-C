#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

typedef float T_Trig;

/*-----------------------------------------------------------------------------------------
|
|  CosFP()
|
|  Return cos(x) for 'x' radians.
|
------------------------------------------------------------------------------------------*/

PUBLIC T_Trig CosFP(T_Trig x)
{
   return SineFP(x + HALFPI);
}

// --------------------------------- eof -------------------------------------
 
