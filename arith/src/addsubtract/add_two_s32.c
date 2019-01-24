#include "arith.h"

/* The 'safe' addition of two 32-bit numbers, by way of floating point.
*/

PUBLIC S32 AddTwoS32(S32 a, S32 b)
{
   return ClipFloatToLong((float)a + (float)b);
}
 
