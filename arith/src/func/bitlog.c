/*-----------------------------------------------------------------------------------------
|
|  BitLogS16()
|
|  Integer logarithim base 2,   c/o Lehman & Crenshaw
|
|  The 'bitlog' of 'n' is:
|
|     8 * (b-1) + r
|
|  where:
|        'b' is the 'bit number' of the msb, with 0 being the low-order bit
|              e.g for 0x1001, 'b' = 3;  for 0x00110111, 'b' = 5
|        'r' are the next 3 bits after the msb (right zero-padded if 'b' is < 3)
|
------------------------------------------------------------------------------------------*/

#include "spj_stdint.h"
#include "arith.h"

PUBLIC U8 BitLogU16(U16 n)
{
   U8 b;

   b = 2;

   while(1)
   {
      if(n == 0)
      {
         return 0;
      }
      else if(n >= 32)
      {
         n >>= 1;
         b++;
      }
      else if( n <= 7 )
      {
         n <<= 1;
         b--;
      }
      else
      {
         return (8 * b) + (n & 0x07);
      }
   }
}

PUBLIC U16 BitLogU32(U32 n)
{
   U16 b;

   b = 2;

   while(1)
   {
      if(n == 0)
      {
         return 0;
      }
      else if(n >= 32)
      {
         n >>= 1;
         b++;
      }
      else if( n <= 7 )
      {
         n <<= 1;
         b--;
      }
      else
      {
         return (8 * b) + (n & 0x07);
      }
   }
}



// ------------------------------- eof ----------------------------------------
