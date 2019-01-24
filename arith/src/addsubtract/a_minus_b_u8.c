#include "common.h"
#include "arith.h"

/* The sum of 2 bytes, limited to an byte
 
   For when the arithmetic musn't wrap on overrange.
*/

PUBLIC U8 AminusBU8(U8 a, U8 b)
{
   return (a > b) ? (a - b) : 0;
}

   
