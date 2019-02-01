#include "unity.h"
#include <stdlib.h>
#include <time.h>
#include "tdd_common.h"
#include "util.h"
#include "arith.h"
#include <float.h>

// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    //srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
}

/* ------------------------------------- test_GetPwr10Float ------------------------------------- */

void test_GetPwr10Float(void)
{
   typedef struct { S16 exp; float res; } S_Tst;

      S_Tst const tsts[] = {
         // 10^0 -> 1.0
         { .exp = 0,    .res = 1.0 },


         // Some other positive and negative indices.
         { .exp = 1,    .res = 10.0 },
         { .exp = -1,   .res = 0.1 },
         { .exp = 3,    .res = 1E3 },
         { .exp = 15,   .res = 1E15 },
         { .exp = 23,   .res = 1E23 },
         { .exp = -17,  .res = 1E-17 },

         // 10^38, 10^-37
         { .exp = FLT_MAX_10_EXP,    .res = XCAT(1.0E, FLT_MAX_10_EXP) },
         { .exp = FLT_MIN_10_EXP,    .res = 1.0E-37 },      // Can't construct const from (-37) (has brackets)

         // Overrange exponents are clipped to float min/max.
         { .exp = FLT_MAX_10_EXP+1,    .res = FLT_MAX },
         { .exp = FLT_MIN_10_EXP-1,    .res = FLT_MIN },
      };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      float res = GetPwr10Float(t->exp);

      C8 b0[100];
      sprintf(b0, "10^%d -> %.3e", t->exp, res);
      TEST_ASSERT_EQUAL_FLOAT_MESSAGE( t->res, GetPwr10Float(t->exp), b0);
   }
}

/* ------------------------------------- test_GetPwr10Double ------------------------------------- */

void test_GetPwr10Double(void)
{
   typedef struct { S16 exp; double res; } S_Tst;

      S_Tst const tsts[] = {
         // 10^0 -> 1.0
         { .exp = 0,    .res = 1.0 },

         // Some other positive and negative indices.
         { .exp = 1,    .res = 10.0 },
         { .exp = -1,   .res = 0.1 },
         { .exp = 3,    .res = 1E3 },
         { .exp = 15,   .res = 1E15 },
         { .exp = 23,   .res = 1E23 },
         { .exp = -17,  .res = 1E-17 },
         { .exp = 64,   .res = 1E64 },
         { .exp = -55,   .res = 1E-55 },

         // 10^38, 10^-37
         { .exp = DBL_MAX_10_EXP,    .res = XCAT(1.0E, DBL_MAX_10_EXP) },
         { .exp = DBL_MIN_10_EXP,    .res = 1.0E-307 },      // Can't construct const from (-37) (has brackets)

         // Overrange exponents are clipped to float min/max.
         { .exp = DBL_MAX_10_EXP+1,    .res = DBL_MAX },
         { .exp = DBL_MIN_10_EXP-1,    .res = DBL_MIN },
      };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      double res = GetPwr10Double(t->exp);

      C8 b0[100];
      sprintf(b0, "10^%d -> %.15e diff %e", t->exp, res, t->res-res);
      TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( t->res, res, b0);
   }
}



// ----------------------------------------- eof --------------------------------------------
