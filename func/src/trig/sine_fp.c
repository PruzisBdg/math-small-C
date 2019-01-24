#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

typedef float T_Trig;

/*-----------------------------------------------------------------------------------------
|
|  SineFP()
|
|  Return sin(x) for 'x' radians.
|
|	By quadrants, counter-clockwise:
|		0 <- 315 - 45deg
|		1 <- 45  - 135deg
|		2 <- 135 - 225deg
|		3 <- 225 - 315deg
|
------------------------------------------------------------------------------------------*/

PUBLIC T_Trig SineFP(T_Trig x)
{
   S32 n;

   n = (S32)(x/HALFPI + 0.5);				// Get quadrant counts (4 * rotations, zero offset is -45deg)
   x -= n * HALFPI;							// Remainder into the quadrant

   switch(n % 4L)								// And the quadrant is?
   {                                   // Remember! sin, cos, -sin, -cos
      case 0:  return SineFP_90(x);		// 315 -> 45
      case 1:  return CosFP_90(x);     // 45  -> 135
      case 2:  return -SineFP_90(x);   // 135 -> 225
      case 3:  return -CosFP_90(x);    // 225 -> 315
      default: return 0.0;
   }
}

// --------------------------------- eof -------------------------------------

