#include "math_common.h"
#include "iirFilt1.h"


PUBLIC S16 IIR1_InitVal( S_IIR1 RAM_IS *f, U8 div, S16 initVal )
{
   IIR1_Init(f, div);
   IIR1_LPass_Prime(f, initVal);
   return initVal;
}

/* --------------------------------- eof ----------------------------------- */ 
