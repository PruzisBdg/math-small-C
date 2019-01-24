/* ---------------------------- Rank Filter -------------------------------------------

   On each iteration, returns the 'rth' sample, sorted by rank, of the last 'n' samples
   applied to the filter. 'n' must be > 'r'. The filter can be used to return the min, max,
   median, or any rank in between viz:

      r = 0;    returns max
      r = n;    returns min
      r = n/2   returns median

   Rather than sorting existng samples each time a new sample is applied to the buffer
   the filter maintains the samples in a time-linear order and tags each sample with
   its rank. This avoids the inefficient shuffling of data each time a new sample
   is processed.

   When the filter is flushed, it starts with just one sample (of the value supplied
   by _Flush() ). Subsequent samples are added to this one until there are 'n' samples.
   Subsequent new samples displace the oldest ones from the filter, whose length
   remains 'n'.
      While the filter length is less than 'n', a read for the sample of rank 'r'
   return the sample of rank normalised to the current filter length i.e

         r(current) = r(requested) * n(current) / n(final)

   This gives the filter 'fast startup' it will return e.g. the median of the samples
   in the filter so far even before the filter buffer is not yet full.

   The filter will also return the mean and deviation of the samples if requested.
*/

#include "common.h"
#include "arith.h"

/* --------------------------- rankFilt_Init ---------------------------------

   Just set up the circular buffer. The filter should be flushed before use.
*/

PUBLIC void rankFilt_Init( rankFilt_S *f, rankFilt_S_Entry *buf, U8 size ) {

   f->start = buf;
   f->put = f->start;
   f->end = f->start + size - 1;
   f->size = size;
   f->sampleCnt = 0;
}


/* --------------------------- rankFilt_Flush --------------------------------

   Flushing the filter involves setting the slot 0 to 'initValue' and the
   rank the slot to 0 (its the only sample). The 'put' pointer is set to the
   next slot (1).

   However, so that the filter functions correctly as more samples are added,
   the ranks in the as yet unused slots muts be set to 0,1,2...
*/
PUBLIC void rankFilt_Flush( rankFilt_S *f, S16 initValue ) {

   U8                  NEAR c;
   rankFilt_S_Entry  * NEAR p;
   U8                  NEAR size = f->size;   /* cache */

   /* Initialise slots in filter with 'initValue' and ranks 0,1,2.. */
   for( c = 0, p = f->start; c < size; c++, p++ ) {
      p->rank = c;
      p->value = initValue;
      p->weight = 0;
      }

   f->put = f->start + 1;        /* next sample into slot 1 */
   f->sampleCnt = 1;             /* this is the only sample */
   f->sampleSum = initValue;
}

/* ---------------------------- rankFilt_Run ---------------------------------------

   Add new sample 'n' to rank filter 'f'. The oldest sample in the filter is excised,
   'n' is added as the newest sample and the ranks are recomputed.

   Returns FALSE if the filter is corrupted (in which case it should be flushed).
*/
PUBLIC BOOL rankFilt_Run( rankFilt_S *f, S16 in ) {

   U8  NEAR      c,
                     inRank,
                     rank,
                     rankOfOldest;

   rankFilt_S_Entry  * NEAR p, * NEAR q;

   f->sampleSum += in;     /* Add new sample to sum */

   c = f->size;                     /* cache these                            */
   p = f->put;

   /* If the filter is at full length, the oldest sample will have to be excised
      ranks of remaining samples adjusted accordingly.
   */
   if( c == f->sampleCnt ) {        /* filter at full length?                 */
      f->sampleSum -= p->value;     /* Subtract oldest sample from sum.       */

      /* Pass through the data and excise the oldest sample; all samples of
         rank lower than the excised one are 'moved up' one.
      */
      rankOfOldest = p->rank;       /* Oldest sample is in the current 'put'  */

      for( q = f->start;
           c;
           c--, q++ )
         {
         if( (rank = q->rank) > rankOfOldest ) { /* lower in rank? move it up. */
            q->rank = --rank;
            }
         }
      }
   /* else the filter isn't at full length, no need to excise a sample and adjust
      ranks; just update the sample count.
   */
   else {
      f->sampleCnt++;
      }

   /* Insert the new sample at the put ptr.  */
   p->value = in;

   /* Revise rankings. Scan the list, Compare each sample with the new one. If the
      list sample is less the new one then move the rank of the list sample down.

      At the same time, reckon the ranking for the new sample by counting the
      number of samples which are greater than or equal to it.
   */
   for( c = f->sampleCnt,        /* for samples in filter so far     */
        q = f->start,
        inRank = 0;
        c;
        c--, q++ )
      {
      if( q->value < in ) {      /* this < new ? ; move this down    */
         q->rank++;
         }
      else {                     /* new <= this? ; increment rank of 'new' */
         inRank++;
         }
      }
   /* In scanning the list, the new sample will have been compared with itself,
      and so 'inRank' will have been incremented one extra. Undo this extra
      increment to get the true rank of the new sample
   */
   inRank--;

   p->rank = inRank;             /* writeback rank of new sample. */

   /* Finally update the put ptr for next sample */
   if( ++p > f->end ) p = f->start;
   f->put = p;

   return TRUE;
}

/* --------------------------- rankFilt_Read -----------------------------------

   Return the sample in the rank_Filter 'f' whose rank matches 'targetRank'. The
   filter contents are not modified.

   If 'targetRank' exceeds the filter size, then it is clipped to the filter
   size.

   If the filter is not yet at full length, then 'targetRank' is scaled to the
   current length of the filter.

   If a sample 'targetRank' could not be found in the filter the filter is trashed;
   Send an exception and return the 1st sample in the buffer (the best we can do).
*/

PUBLIC S16 rankFilt_Read( rankFilt_S *f, U8 targetRank ) {

   rankFilt_S_Entry  * NEAR p;
   U8             NEAR cnt  = f->sampleCnt;
   U8             NEAR size = f->size;

   if( !cnt ) {               // filter empty?
      return 0;
      }
   else {                     // else has at least one sample
      /* If filter less than full length then normalise target rank to filter
         length. Because 'rank' or 'cnt' may be small mumbers pay correct for
         rounddown.
      */
      if( cnt < size ) {
         targetRank = (((U16)targetRank * cnt) + (targetRank/2) + (cnt/2))/ size;
         }
      /* Make sure 'targetRank is in-bounds; available ranks are 0.. size-1 */
      if( targetRank >= cnt ) {
         targetRank = cnt-1;
         }
      /* Search for the sample labelled with 'targetRank'; return its value */
      for( p = f->start; cnt; cnt--, p++ ) {
         if( p->rank == targetRank )
            return p->value;
         }
      /* Not found! filter is trashed. Return the 1st sample in the buffer; the
         best we can do.
      */
//      PushError(exc_Math_RankFiltBad);
      return f->start->value;
      }

}

/* ---------------------------- rankFilt_Rank --------------------------------------

   Return the 'targetRank' in the rank_Filter 'f' that 'targetValue' would have.
   The filter contents are not modified.

   If the filter is not yet at full length, then 'targetRank' is scaled to the
   full length of the filter.

   Returns 0 if the filter bank is empty

*/
PUBLIC U8 rankFilt_Rank( rankFilt_S *f, S16 targetValue ) {

   rankFilt_S_Entry * NEAR q;
   U8              NEAR c;
   U8              NEAR targetRank;
   U8              NEAR cnt  = f->sampleCnt;
   U8              NEAR size = f->size;

   if( !cnt ) {               // filter empty?
      return 0;
      }
   else {                     // else has at least 1 sample
      for ( c = cnt,
            q = f->start,
            targetRank = 0;
            c;
            c--, q++ ) {

         if ( q->value >= targetValue ) {
            targetRank++;
            }
         }

      /* If filter less than full length then normalise target rank to filter
         length. Because 'rank' or 'cnt' may be small numbers pay correct for
         rounddown.
      */
      if( cnt < size ) {
         targetRank = (((U16)targetRank * size) + (cnt/2))/ cnt;
         }

      return targetRank;
      }
}

/* -------------------------- rankFilt_ReadDev ------------------------------------

   Return the mean (absolute) deviation of the samples in the filter.
*/

PUBLIC S16 rankFilt_Dev( rankFilt_S *f ) {

   S16               NEAR  mean;
   U8             NEAR  c;
   rankFilt_S_Entry * NEAR p;
   long              NEAR  acc;
   U8             NEAR  cnt = f->sampleCnt;
   S16               NEAR  n;

   mean = (S16)(f->sampleSum / cnt);

   for( c = cnt, p = f->start, acc = 0; c; c--, p++ ) {
      n = p->value - mean;
      acc += ABS(n);
      }
   return (S16)(acc / cnt);
}

// ----------------------------------- eof ---------------------------------------
