 /*---------------------------------------------------------------------------
|
|                  1st-order IIR filters
|
|--------------------------------------------------------------------------*/

#include "math_common.h"
#include "iirFilt1.h"

PUBLIC U8 IIR1_GetCoff( S_IIR1 RAM_IS *f )
{
   return f->div;
}

// -------------------------- eof --------------------------------------
 
