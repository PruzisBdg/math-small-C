/* -----------------------------------------------------------------
|
|              Basic Floating Point
|
--------------------------------------------------------------------- */

#include "spj_stdint.h"
#include <math.h>
#include <float.h>
#include "arith.h"

/* ---------------------------------- MinFloat ------------------------------- */

PUBLIC float MinFloat(float a, float b) {
   return
      (isnan(a) || isnan(b))
         ? NAN
         : (a < b ? a : b); }

/* ---------------------------------- MaxFloat ------------------------------- */

PUBLIC float MaxFloat(float a, float b) {
   return
      (isnan(a) || isnan(b))
         ? NAN
         : (a > b ? a : b); }


/* ---------------------------------- ClipFloatToLong -------------------------------

   Corners/transitions

      (S32)(float)MAX_S32 -> MAX_S32 and...
      (S32)(float)MIN_S32 -> MIN_S32.

      The 32bit number is truncated to a 24bit mantissa, so C does not strictly define the
      exact output. But avoid sign-reversal always

      NaN -> 0.

      Per Standard, result is undefined. Choose zero.
*/
PUBLIC S32 ClipFloatToLong(float f)
{
   if(isnan(f))
      return 0;
   // Next 2 clauses use '<=' and ''>=' to capture MIN_S32 and MAX_S32 and avoid sign-reversal trying to (S32)cast.
   else if( f <= (float)MIN_S32 || f == FLT_MIN )
      return MIN_S32;
   else if( f >= (float)MAX_S32 || f == FLT_MAX)
      return MAX_S32;
   else
      return (S32)f;
}

/* ---------------------------------- ClipFloatToU32 -------------------------------

   Same logic as ClipFloatToLong()
*/
PUBLIC U32 ClipFloatToU32(float f)
{
   if(isnan(f))
      return 0;
   else if( f <= 0.0F || f == FLT_MIN )       // Use 'F' to avoid promotion to double (in emabedded targets)
      return 0;
   else if( f >= (float)MAX_U32 || f == FLT_MAX )
      return MAX_U32;
   else
      return (U32)f;
}

/* ---------------------------------- ClipFloatToU16 ------------------------------- */

PUBLIC U16 ClipFloatToU16(float f)
{
   if(isnan(f))
      return 0;
   else if( f <= 0.0F || f == FLT_MIN )
      return 0;
   else if( f >= (float)MAX_U16 || f == FLT_MAX )
      return MAX_U16;
   else
      return (U16)f;
}

/* ---------------------------------- ClipDoubleToS64 ------------------------------- */

PUBLIC S64 ClipDoubleToS64(double d)
{
   if(isnan(d))
      return 0;
   else if( d <= (double)MIN_S64 || d == DBL_MIN )
      return MIN_S64;
   else if( d >= (double)MAX_S64 || d == DBL_MAX )
      return MAX_S64;
   else
      return (S64)d;
}

/* ---------------------------------- ClipFloatToInt ------------------------------- */

PUBLIC S16 ClipFloatToInt(float f)
{
   return ClipS32toS16(ClipFloatToLong(f));
}

/* ----------------------------------- InsideEq_Float --------------------------------- */

PUBLIC BOOL InsideEq_Float(float n, float min, float max) {
   // Note if any of the 3 args is NaN the composite must return false.
   return
      isnan(n) || isnan(min) || isnan(max)
         ? false
         : (n >= min && n <= max); }




/*-----------------------------------------------------------------------------------
|
|  GetPwr10Float
|
|  Return 10^exp for 'exp', which may be anywhere in the legal range for floats
|  or doubles.
|
|  The table lookup method avoids using pow() (<math> power function) which is
|  slow. The function walks down the table and converges on 'exp' in no more FP multiplies
|  than the length of the table itself.
|
--------------------------------------------------------------------------------------*/

typedef struct
{
   S16   exp;        // an exponent
   float num;        // 10^exp
} S_Pwr10FloatMapping;

PRIVATE S_Pwr10FloatMapping const Pwr10FloatTbl[] =
{
   {32,  1E32 },
   {16,  1E16 },
   {8,   1E8  },
   {4,   1E4  },
   {2,   1E2  },
   {1,   10.0 }
};

PUBLIC float GetPwr10Float(S16 exp)
{
   U8    c;
   BIT   negExp;
   float f;

   if( exp == 0 )                            // 10^0?
   {
      return 1.0F;                           // equals 1.0
   }
   else if(exp > FLT_MAX_10_EXP)             // Too large?
   {
      return FLT_MAX;                        // CLip to float max (which is not an exact power of 10)
   }
   else if(exp < FLT_MIN_10_EXP)             // Likewise, too small?
   {
      return FLT_MIN;
   }
   else                                      // else must use Pwr10FloatTbl[]
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

      for( c = 0, f = 1.0F; exp; c++)           // From 1.0, and from table bottom (largest numbers)
      {
         while( exp >= Pwr10FloatTbl[c].exp )   // While remainder of exponent > this table entry
         {
            f *= Pwr10FloatTbl[c].num;          // then multiply 'f' by tables 10^exp
            exp -= Pwr10FloatTbl[c].exp;        // and consume the exponent
         }                                      // and on to try next (smaller) table entry
      }                                         // continue until 'exp' has been eaten

      // Return with 10^exp
      if( negExp )                              // Exponent was negative?
         { return 1.0F/f; }                     // then flip the table result
      else
         { return f; }                          // else return result unchanged
   }
}

/*-----------------------------------------------------------------------------------
|
|  GetPwr10Double
|
|  Return 10^exp for 'exp', which may be anywhere in the legal range for doubles.
|
|  The table lookup method avoids using pow() (<math> power function) which is
|  slow. The function walks down the table and converges on 'exp' in no FP multiplies
|  than the length of the table itself.
|
--------------------------------------------------------------------------------------*/

typedef struct
{
   S16   exp;        // an exponent
   double num;        // 10^exp
} S_Pwr10DoubleMapping;

PRIVATE S_Pwr10DoubleMapping const Pwr10DoubleTbl[] =
{
   {256, 1E256 },
   {128, 1E128 },
   {64,  1E64  },
   {32,  1E32  },
   {16,  1E16  },
   {8,   1E8   },
   {4,   1E4   },
   {2,   1E2   },
   {1,   10.0  }
};

PUBLIC double GetPwr10Double(S16 exp)
{
   U8    c;
   BIT   negExp;
   double d;

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
   else                                      // else must use Pwr10DoubleTbl[]
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

      for( c = 0, d = 1.0; exp; c++)            // From 1.0, and from table bottom (largest numbers)
      {
         while( exp >= Pwr10DoubleTbl[c].exp )   // While remainder of exponent > this table entry
         {
            d *= Pwr10DoubleTbl[c].num;          // then multiply 'f' by tables 10^exp
            exp -= Pwr10DoubleTbl[c].exp;        // and consume the exponent
         }                                      // and on to try next (smaller) table entry
      }                                         // continue until 'exp' has been eaten

      // Return with 10^exp
      if( negExp )                              // Exponent was negative?
         { return 1.0/d; }                      // then flip the table result
      else
         { return d; }                          // else return result unchanged
   }
}



/*-----------------------------------------------------------------------------------
|
|  Mod_Float
|
|  Returns 'n' mod 'd'.
|
|  'mod' is to the nearest, above or below. E.g  1.3 mod 1.0 = 0.3 but 1.7 mod 1.0
|  is also 0.3 because 2.0 - 1.7 = 0.3.
|
--------------------------------------------------------------------------------------*/

PUBLIC float Mod_Float(float n, float d)
{
    float m;

    if(isnan(n) || isnan(d))
    {
       return NAN;
    }
    else if(d == 0.0f)
    {
        return 0.0;
    }
    else
    {
        m = floor(n/d);
        return MinFloat(n-(m*d), (d * (m+1)) - n);
    }
}

/*-----------------------------------------------------------------------------------
|
|  DecSizeFloat/Double
|
|  Get the nearest power of 10 for 'f', from the binary exponent mantissa x 2^exp,
|  where 'mantissa' is [0.5.. 1.0].
|
|  Note: Use single-precision (float) functions to avoid defaulting to double
|  (which is overkill for a diagnostic embedded printf).
|
--------------------------------------------------------------------------------------*/

PUBLIC S16 DecSizeFloat(float f)
{
   if(f == 0.0f)
   {
      return MIN_S16;
   }
   else if(isnan(f))
   {
      return 0;
   }
   else
   {
      int  exp2N;    // exponent as 2^N

      // Hack the float, returns the exponent.
      frexpf(f, &exp2N);

      // Get the corresponding power of 10, ( 10 = 2^3.3219.... )
      S16 s = (S16)floorf( exp2N/3.32192809489f);

      // With 'FLT_MIN' above evaluates to 10^-38. Clip to 10^-37, the true minimum float exponent.
      return MaxS16(s, FLT_MIN_10_EXP);
   }
}

PUBLIC S16 DecSizeDouble(double d)
{
   if(d == 0.0)
   {
      return MIN_S16;
   }
   else if(isnan(d))
   {
      return 0;
   }
   else
   {
      int  exp2N;    // exponent as 2^N

      // Hack the double, returns the exponent.
      frexp(d, &exp2N);

      // Get the corresponding power of 10, ( 10 = 2^3.3219.... )
      S16 s = (S16)floorf(exp2N/3.32192809489);

      // With 'DBL_MIN' above evaluates to 10^-308. Clip to 10^-307, the true minimum double exponent.
      return MaxS16(s, DBL_MIN_10_EXP);
   }
}

/*-----------------------------------------------------------------------------------
|
|  FloatsEqual
|
|  Safe float comparison, handles infinities.
|
--------------------------------------------------------------------------------------*/

PUBLIC BOOL FloatsEqual(float a, float b, float epsilon) {

   // If any arg is NAN, must return false. DOn't allow short circuit to return something else.
   if(isnan(a) || isnan(b) || isnan(epsilon)) {
      return FALSE; }
   else
   {
      float absA = fabsf(a);
      float absB = fabsf(b);
      float diff = fabsf(a - b);

      if (a == b) {                                               // shortcut, handles infinities
         return TRUE; }
      else if (a == 0 || b == 0 || (absA + absB < FLT_MIN )) {    // Zero, or close to
         return diff < (epsilon * FLT_MIN ); }                    // use and absolute error
      else {
         return diff / MIN((absA + absB), FLT_MAX ) < epsilon; }  // else relative error less-then
   }
}
// ------------------------------------ eof ------------------------------------------------------
