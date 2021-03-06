
#include "arith.h"
#include <float.h>
#include <math.h>

/*-----------------------------------------------------------------------------------
|
|  GetPwr10Float
|
|  Return 10^exp for 'exp', which may be anywhere in the legal range for floats
|  or doubles.
|
|  The table lookup method avoids using pow() (<math> power function) which is
|  slow. The function walks down the table an converges on 'exp' in at most a
|  few cycles.
|
|  Overrange exponents are clppped to double min/max
|
--------------------------------------------------------------------------------------*/

typedef struct
{
   S16   exp;        // an exponent
   double num;        // 10^exp
} S_Pwr10Mapping;

PRIVATE S_Pwr10Mapping CONST Pwr10Tbl[] =
{
   {32,  1E32 },
   {16,  1E16 },
   {8,   1E8  },
   {4,   1E4  },
   {2,   1E2  },
   {1,   10.0 }
};

PUBLIC double GetPwr10Double(S16 exp)
{
   U8    c;
   BIT   negExp;
   double f;

   if( exp == 0 )                            // 10^0?
   {
      return 1.0;                            // equals 1.0
   }
   else if(exp > DBL_MAX_10_EXP)             // Too large?
   {
      return DBL_MAX;                        // CLip to float max (which is not an exact power of 10)
   }
   else if(exp < DBL_MIN_10_EXP)             // Likewise, too small?
   {
      return DBL_MIN;
   }
   else                                      // else must use Pwr10Tbl[]
   {
      /* Table is for positive exponents. Handle negative ones by flipping the
         exponent and then returning reciprocal of result from table.
      */
      if( exp < 0 )                          // Negative exponent?
      {
         negExp = 1;                         // then mark that is so
         exp = -exp;                         // and flip it.
      }
      else
         { negExp = 0; }

      for( c = 0, f = 1.0; exp; c++)            // From 1.0, and from table bottom (largest numbers)
      {
         while( exp >= Pwr10Tbl[c].exp )        // While remainder of exponent > this table entry
         {
            f *= Pwr10Tbl[c].num;               // then multiply 'f' by tables 10^exp
            exp -= Pwr10Tbl[c].exp;             // and consume the exponent
         }                                      // and on to try next (smaller) table entry
      }                                         // continue until 'exp' has been eaten

      // Return with 10^exp
      if( negExp )                              // Exponent was negative?
         { return 1.0/f; }                      // then flip the table result
      else
         { return f; }                          // else return result unchanged
   }
}

// ---------------------------------------- eof -------------------------------------------
