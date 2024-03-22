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

/* ------------------------------------- test_DownSampleS16_Init ------------------------------------- */

void test_DownSampleS16_Init(void)
{
   S_DownSampleS16 r;

   // Setup to downsample.
   TEST_ASSERT_TRUE(DownSampleS16_Init(&r, &(S_ResampleRatesU8){.in = 12, .out = 5}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 12 && r.outRate == 5);

   // Upsample not allowed.
   TEST_ASSERT_FALSE(DownSampleS16_Init(&r, &(S_ResampleRatesU8){.in = 5, .out = 12}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 0 && r.outRate == 0);

   // In and out rates may be equal.
   TEST_ASSERT_TRUE(DownSampleS16_Init(&r, &(S_ResampleRatesU8){.in = 7, .out = 7}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 7 && r.outRate == 7);

   // Zero rates not allowed.
   TEST_ASSERT_FALSE(DownSampleS16_Init(&r, &(S_ResampleRatesU8){.in = 0, .out = 5}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 0 && r.outRate == 0);

   TEST_ASSERT_FALSE(DownSampleS16_Init(&r, &(S_ResampleRatesU8){.in = 12, .out = 0}) );
   TEST_ASSERT_TRUE(r.acc == 0 && r.bucket == 0 && r.inRate == 0 && r.outRate == 0);
}

/* ------------------------------------- test_DownSampleS16_Run ------------------------------------- */

void test_DownSampleS16_Run(void)
{
   S_DownSampleS16 r;

   typedef struct {S16 in; bool ret; S32 out;} S_Tst;

   void runOneSeq(S_Tst const *seq, U8 seqSize, S32 flush, U8 inRate, U8 outRate)
   {
      S32 out;
      DownSampleS16_Init(&r, &(S_ResampleRatesU8){.in = inRate, .out = outRate});

      for(U8 i = 0; i < seqSize; i++)
      {
         S_Tst const *t = &seq[i];

         bool ret = DownSampleS16_Run(&r, &out, t->in);

         if(ret != t->ret)                         // Wrong (bool) return?
         {
            printf("step# %d in = %d   expected %s, got %s\r\n", i, t->in, tf(t->ret), tf(ret));
         }
         else if(ret == true && out != t->out)     // New output, but it's wrong value?
         {
            printf("step# %d in = %d   expected %ld, got %ld\r\n", i, t->in, t->out, out);
         }
      }

      // Flush DonSampleS16; should always return true. Check remainder.
      TEST_ASSERT_TRUE(DownSampleS16_Flush(&r, &out));

      if(out != flush) {
           printf("flush:  expected %ld, got %ld\r\n", flush, out); }
   }

   // Simple 3-into-2; with a remainder to flush.
   S_Tst const _3into2[] = {
      {.in = 1000, .ret = false},
      {.in = 1000, .ret = true,     .out = 1500},
      {.in = 1000, .ret = true,     .out = 1500},
      {.in = 1000, .ret = false},
      {.in = 1000, .ret = true,     .out = 1500},
      {.in = 1033, .ret = true,     .out = 1500},     // Extra 33 to flush at end.
   };

   runOneSeq(_3into2, RECORDS_IN(_3into2), 33, 3, 2);
}


// ----------------------------------------- eof --------------------------------------------
