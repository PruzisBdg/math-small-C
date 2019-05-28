#include "unity.h"
#include <stdlib.h>
//#include <time.h>
#include "tdd_common.h"
//#include "util.h"
//#include "arith.h"
#include <float.h>
#include "mathfunc.h"
#include <math.h>

// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    //srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
}

/* ------------------------------------- test_InvSqrtFP ------------------------------------- */

void test_InvSqrtFP(void)
{
   TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.0, InvSqrtFP(0.0), "Zero should return zero.");

   typedef struct { float n, tol; } S_Tst;

   #define _DfltTol 0.002

   S_Tst const tsts[] = {
      // Many of these should be on the same mantissa, but check powers anyway.
      { .n = 1.0,       .tol = _DfltTol },
      { .n = 2.0,       .tol = _DfltTol },
      { .n = 5.0,       .tol = _DfltTol },
      { .n = 10.0,      .tol = _DfltTol },
      { .n = 100.0,     .tol = _DfltTol },
      { .n = 1E3,       .tol = _DfltTol },
      { .n = 1E10,      .tol = _DfltTol },
      { .n = FLT_MAX,   .tol = _DfltTol },

      { .n = 0.5,       .tol = _DfltTol },
      { .n = 0.2,       .tol = _DfltTol },
      { .n = 0.1,       .tol = _DfltTol },
      { .n = 1E-3,      .tol = _DfltTol },
      { .n = FLT_MIN,   .tol = _DfltTol },
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      // With positive (+) input.
      float expected = 1.0/sqrt(t->n);
      float got = InvSqrtFP(t->n);

      C8 b0[100];
      sprintf(b0, "tsts #%d %4.3e -> %4.3e", i, t->n, got);
      TEST_ASSERT_FLOAT_WITHIN_MESSAGE( t->tol * expected, expected, got, b0);

      // With negative (-) input.
      expected = -1.0/sqrt(t->n);
      got = InvSqrtFP(-t->n);

      sprintf(b0, "tsts #%d %4.3e -> %4.3e", i, t->n, got);
      TEST_ASSERT_FLOAT_WITHIN_MESSAGE( t->tol * expected, expected, got, b0);

   }
}


// ----------------------------------------- eof --------------------------------------------
