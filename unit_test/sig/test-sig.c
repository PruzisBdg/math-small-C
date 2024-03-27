#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include "tdd_common.h"
#include "math_sig.h"


C8 const *tf(bool b) {return b == true ? "true" : "false";}

// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    //srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
}

/* ------------------------------------- test_DownSmplS16_Init ------------------------------------- */

void test_DownSmplS16_Init(void)
{
   S_DownSmplS16 r;

   // Setup to downsample.
   TEST_ASSERT_TRUE(DownSmplS16_Init(&r, &(S_ResampleRatesU8){.in = 12, .out = 5}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 12 && r.outRate == 5);

   // Upsample not allowed.
   TEST_ASSERT_FALSE(DownSmplS16_Init(&r, &(S_ResampleRatesU8){.in = 5, .out = 12}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 0 && r.outRate == 0);

   // In and out rates may be equal.
   TEST_ASSERT_TRUE(DownSmplS16_Init(&r, &(S_ResampleRatesU8){.in = 7, .out = 7}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 7 && r.outRate == 7);

   // Zero rates not allowed.
   TEST_ASSERT_FALSE(DownSmplS16_Init(&r, &(S_ResampleRatesU8){.in = 0, .out = 5}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 0 && r.outRate == 0);

   TEST_ASSERT_FALSE(DownSmplS16_Init(&r, &(S_ResampleRatesU8){.in = 12, .out = 0}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 0 && r.outRate == 0);
}

/* ------------------------------------- test_DownSmplS16_Run ------------------------------------- */

void test_DownSmplS16_Run(void)
{
   S_DownSmplS16 r;

   typedef struct {S16 in; bool ret; S32 out;} S_Tst;

   void runOneSeq(S_Tst const *seq, U8 seqSize, S32 flush, U8 inRate, U8 outRate)
   {
      bool fail = false;
      S32 out;
      DownSmplS16_Init(&r, &(S_ResampleRatesU8){.in = inRate, .out = outRate});

      for(U8 i = 0; i < seqSize; i++)
      {
         S_Tst const *t = &seq[i];

         bool ret = DownSmplS16_Run(&r, &out, t->in);

         if(ret != t->ret)                         // Wrong (bool) return?
         {
            printf("step# %d in = %d   expected %s, got %s\r\n", i, t->in, tf(t->ret), tf(ret));
            fail = true;
         }
         else if(ret == true && out != t->out)     // New output, but it's wrong value?
         {
            printf("step# %d in = %d   expected %ld, got %ld\r\n", i, t->in, t->out, out);
            fail = true;
         }
      }

      // Flush DonSampleS16; should always return true. Check remainder.
      TEST_ASSERT_TRUE(DownSmplS16_Flush(&r, &out));

      if(out != flush) {
           printf("flush:  expected %ld, got %ld\r\n", flush, out);
           fail = true; }

      if(fail == true) {TEST_FAIL();}
   }

   // Simple 3-into-2; with a remainder to flush.
   S_Tst const _3into2[] = {
      {.in = 1000, .ret = false},                  // Eat all of 1st sample; no output
      {.in = 500, .ret = true,      .out = 1250},  // All of 1st sample plus 1/2 of 2nd
      {.in = 800, .ret = true,      .out = 1050},  // Half of 2nd plus all of 3rd.
      {.in = 1000, .ret = false},                  // Eat all of 4th sampl; no output.
      {.in = 1000, .ret = true,     .out = 1500},  // etc..
      {.in = 1033, .ret = true,     .out = 1533},
      {.in = 99,   .ret = false},                  // Extra 99 to flush at end.
   };

   runOneSeq(_3into2, RECORDS_IN(_3into2), 99, 3, 2);

   // Simple 3-into-2; with a remainder to flush.
   S_Tst const _3into2B[] = {
      {.in = 1, .ret = false},
      {.in = 2, .ret = true,     .out = 1},        // Accumulate 2+1 = 3;
      {.in = 3, .ret = true,     .out = 5},
      {.in = 4, .ret = false},
      {.in = 5, .ret = true,     .out = 6},
      {.in = 6, .ret = true,     .out = 9}
   };

   runOneSeq(_3into2, RECORDS_IN(_3into2B), 0, 3, 2);
}


// ----------------------------------------- eof --------------------------------------------
