 /*---------------------------------------------------------------------------
|
|                  1st-order IIR filters
|
|--------------------------------------------------------------------------*/

#include "math_common.h"
#include "iirFilt1.h"
#include "vec.h"


PUBLIC void IIR1Vec_LPass_Init(S_IIR1Vec CONST *f)
{
   FillInts((S16*)f->acc, 0, 2*f->size);       // zero the accumulators
}

PUBLIC void IIR1Vec_LPass_Run(S_IIR1Vec CONST *f, S16 *out, S16 *in )
{
   U8 c, div;

   for( c = 0, div = f->div; c < f->size; c++ )
   {
      f->acc[c] = (((div - 1) * f->acc[c]) / div) + in[c];
      out[c] = f->acc[c] / div;
   }
}


// ------------------------------ eof --------------------------------------- 
