/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Match
|
|  Given vector 'v', return the index of the element whose value is nearest 'y'.
|
|  Depending on control flags 'ctl', the routine will either search the whole vector for the best
|  match or will scan from one end and return the 1st time that vector crosses the target value.
|  The 2nd method can be used where the vector may cross the target value a number of times and
|  you want to get the 1st crossover from a given end.
|
|  For the directional searches the routine can be made to return the point just before the
|  crossover or just after it.
|
|  If 'v' has one row Vec_Match() returns the index to the match; if 'v' has two rows then the
|  2nd row (row 1) is scanned for a match and the function returns the value of the 1st row
|  vector at the match index. 
|
|  DESCRIPTION:
|
|  PARAMETERS:    
|
|     'v'   -  vector to be scanned, 1-row
|     'y'   -  value to find
|
|     'ctl' - search control flags
|
|                 The 1st two flags select directional searches
|
|                 _Vec_Match_SrchUp    - Search up indices; return 1st match
|                 _Vec_Match_SrchDown  - Search down indices; return 1st match
|
|                 If neither of these flags is set, searches the whole vector returns the best
|                 global match
|
|                 _Vec_Match_Inside    - For search up/down, return 1st point before match
|                 _Vec_Match_Outside   - For search up/down, return 1st point after match
|
|                 If the search is for a global match, then these flags are ignored. If the
|                 search is directional then one ought to be set, but if it isn't, code defaults
|                 to '_Inside'
|
|
|  RETURNS:       index to the best match to 'y'
|
|	DATE		   AUTHOR             DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC S16 Vec_Match( S_Vec const *v, S16 y, U8 ctl )
{
   T_VecCols   LVAR end,                 /* for directional searches               */
                    c,
                    matchIdx,            /* index to match in directional searches */
                    idx2,
                    minIdx;              /* index to best global match             */
   S16       * LVAR p;
   S16         LVAR absDiff, minDiff;    /* used in search for best global match   */
   BOOL        LVAR rampsUp;             /* vector slope in global searches        */
   S_Vec            vi,                  /* for 2-row vectors, the domain row to be searched for match  */
                    vo;                  /* and the range to interpolate match onto                     */
   S16         LVAR x0, x1, y0, y1;      /* for interpolation onto 'x' axis                             */

   /* If > 1 row then search 2nd row */
   if( v->rows == 1 )                        /* just one row?                             */
      { Vec_RefRow(&vi, v, 0); }             /* then search it, return index to match                            */
   else                                      /* else more than one row                    */
   {
      if( BSET(ctl, _Vec_Match_OntoRow0) )   /* search row 1, intepolate onto 0?          */
      {
         Vec_RefRow(&vi, v, 1);
         Vec_RefRow(&vo, v, 0);
      }
      else                                   /* else search row 0, interpolate onto row 1 */
      {
         Vec_RefRow(&vi, v, 0);
         Vec_RefRow(&vo, v, 1);
      }
   }

   /* For directional search, find out whether vector ramps up or down. The slope may be
      specified in 'ctl'; otherwise compare the end values.
   */
   if( BSET(ctl, _Vec_Match_RampsUp) )
      { rampsUp = TRUE; }
   else if( BSET(ctl, _Vec_Match_RampsDown) )
      { rampsUp = FALSE; }
   else
      { if( vi.nums[vi.cols-1] > vi.nums[0] ) rampsUp = TRUE; else rampsUp = FALSE; }

   if( BSET(ctl, _Vec_Match_SrchUp) )                             /* search from start of vector forwards?  */
   {
      end = vi.cols;

      /* If no crossover found below then target > all vector elements, return last = largest */
      matchIdx = end - 1;

      for( c = 0, p = vi.nums; c < end; c++, p++ )
      {
         if( (rampsUp && (*p > y)) || (!rampsUp && (*p < y)) )    /* vector crossed over target? */
         {
            if( BSET(ctl, _Vec_Match_Inside) )                    /* return index before crossover? */
            {
               if(c)                                              /* not 1st element? */
               {
                  matchIdx = c-1; break;                          /* then go back one */
               }
               else
               {
                  matchIdx = 0; break;                            /* else the 1st element */
               }
            }
            else if( (BSET(ctl, _Vec_Match_Outside)) )            /* else return index after crossover? */
            {
               matchIdx = c; break;                               /* which would this one */
            }
            else                                                  /* else get index to nearest */
            {
               if( (ABS(y - *p) < ABS(*(p-1) - y)) || c == 0 )    /* current element 'n+1' is nearest OR current element is 1st in vector?  */
               {
                  matchIdx = c; break;                            /* then return index to current element */
               }
               else
               {
                  matchIdx = c - 1; break;                        /* else its previous one scanned */
               }
            }
         }
      }
   }

   /* .... as above but search back */

   else if( BSET(ctl, _Vec_Match_SrchDown) )
   {
      /* If no crossover found below then target < all vector elements, return 1st = smallest */
      matchIdx = 0;

      for( c = vi.cols-1, p = vi.nums + (vi.cols -1); c; c--, p-- )
      {
         if( (rampsUp && (*p < y)) || (!rampsUp && (*p > y)) )
         {
            if( BSET(ctl, _Vec_Match_Inside) )                    /* return index before crossover? */
            {
               if(c < vi.cols)                                    /* not last element (the 1st we checked)? */
               {
                  matchIdx = c; break;                            /* then return previous element (scanned) */
               }
               else
               {
                  matchIdx = c-1; break;                          /* else this one */
               }
            }
            else if( (BSET(ctl, _Vec_Match_Outside)) )            /* else return index after crossover? */
            {
               matchIdx = c; break;                               /* which would this one */
            }
            else                                                  /* else get index to nearest */
            {
               if( (ABS(y - *p) > ABS(*(p+1) - y)) && c < v->cols ) /* previous point is closer AND not the last point? */
               {
                  matchIdx = c; break;                            /* then return previous */
               }
               else
               {
                  matchIdx = c-1; break;                          /* else its current */
               }
            }
         }
      }
   }

   /* .... else neither fwd or back specified; get global match */

   else
   {
      end = vi.cols;
      for( c = 0,
           minIdx = 0,                 /*  */
           minDiff = MAX_S16,          /* start with largest value; comparisons can only be smaller  */
           p = vi.nums;
           c < end;
           c++, p++ )
      {
         absDiff = ABS(y - *p);
         if( minDiff > absDiff )       /* better match? */
         {
            minDiff = absDiff;         /* then log it. */
            minIdx = c;
         }
      }
      matchIdx = minIdx;
   }

   if( v->rows == 1 || BSET(ctl, _Vec_Match_NoInterpolate)) /* source vector is 1 row OR no interpolation?     */
      { return matchIdx; }                                  /* then return index to match on 'y'               */
   else                                                     /* else interpolate onto row 0                     */
   {
      if( y > _Vec_Max((S_Vec const *)&vi) || 
          y < _Vec_Min((S_Vec const *)&vi) )                /* match value outside bounds of vector?           */
      {
         return Vec_Read1( v, 0, matchIdx );                /* then return 'x' value at the end point          */
      }
      else                                                  /* else 'x' value will lie between two 'x' points  */
      {
         /* Interpolate from domain of 'v', referenced by 'vi' onto the range row of 'v', referenced
            by 'vo'.

            Because we handled above when 'y' is outside the range of 'vi', there's no need to
            test again below.
         */
         x0 = Vec_Read1( (S_Vec const *)&vi, 0, matchIdx ); /* Get row 1 value at the match index */

         /* Based on gradient, determine whther 2nd point for interpolation
            lies to left or right of current one.
         */
         if( ((y > x0) && rampsUp) || ((y < x0) && !rampsUp))
            { idx2 = matchIdx + 1; }                        /* then 'y' lies on row 1 between matchIdx and matchIdx + 1 */
         else
            { idx2 = matchIdx - 1; }                        /* else its between matchIdx and matchIdx - 1               */

         y0 = Vec_Read1( (S_Vec const *)&vo, 0, matchIdx ); /* Get remaining points for interpolation                   */
         x1 = Vec_Read1( (S_Vec const *)&vi, 0, idx2 );
         y1 = Vec_Read1( (S_Vec const *)&vo, 0, idx2 );
                                                            /* and do linear interpolation                              */
         if( x1 == x0 )                                     /* x's equal?                                               */
            { return (y0 + y1) / 2; }                       /* then return mean of y's (avoids div by 0)                */
         else                                               /* else linear interpolation onto interval y0 -> y1         */
            { return y0 + ( ((y - x0) * (S32)(y1 - y0)) / (x1 - x0) ); }
      }
   }
}
 
