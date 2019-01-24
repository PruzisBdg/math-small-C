#include "common.h"

PUBLIC void FillInts( S16 *dest, S16 n, U16 cnt )
{
   for( ; cnt; cnt-- ) *dest++ = n;
}

 
