#include "bldcfg.h"
#include "common.h"
#include "mathfunc.h"

/*-----------------------------------------------------------------------------------------
|
|  RewireU16
|
|  'Rewire the bits in 'n' according to 'map'. Each bit gets moved to a new location;
|  no 2 bits go to the same place.
|
|  'map' is an array of 16 words which detail the bit swaps. map[n] has one bit set
|  That bit specifies where the nth bit in 'n' is copied to. map[0] routes the lsb
|  of 'n'.
|
------------------------------------------------------------------------------------------*/

PUBLIC U16 RewireU16(U16 CONST *map, U16 n)
{
   U8    c;
   U16   out;
   
   for(c = 0, out = 0; c < 16; c++ )      // For each of bit0..15
   {
      if( n & 0x01 )                      // That bit is set?
         { out |= map[c]; }               // then set bit specified by map[c] in 'out'.
      n >>= 1;                            // RS next bit to lsb position.
   }
   return out;
}

// ------------------------------------- eof ------------------------------------------- 
