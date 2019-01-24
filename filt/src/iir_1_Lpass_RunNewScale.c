#include "math_common.h"
#include "iirFilt1.h"

PUBLIC S16 IIR1_LPass_RunNewScale( S_IIR1 RAM_IS *f, S16 in, U8 newDiv )
{
   IIR1_Rescale(f, newDiv);
   return IIR1_LPass_Run(f, in);   
}

// -------------------------- eof -------------------------------------- 
