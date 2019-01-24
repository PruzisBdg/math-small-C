#include "math_common.h"
#include "iirFilt1.h"

PUBLIC S16 IIR1_HPass_Prime( S_IIR1 RAM_IS *f, S16 init_dy )
{
   IIR1_LPass_Prime(f, -init_dy);
   return init_dy;
}
 
