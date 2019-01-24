/*---------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Normalise
|
|  Normalise 'v' in 'vn', centered to 'center' and with span 'span'. 'v' may be normalised
|  wrt its extents (min/max), rms, or absolute mean amplitude
|
|  PARAMETERS:  'v'        - source vector
|               'vn'       - normalised result
|               'center'   - mean normalised vector
|               'size'     - size of normalised vector
|               'ctl'      - control flags
|
|     control flags are:
|
|        _Vec_Normalise_MinMax   - span (max - min) of 'vn' == 'span'
|        _Vec_Normalise_RMS      - rms of 'vn' == 'span'
|        _Vec_Normalise_Mean     - mean absolute of 'vn' == 'span'
|
|        If none of the above is specified then the vector is just centred but not resized.
|
|  RETURNS: the size of the source vector, using the measurement specified
|
|	DATE		   AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
----------------------------------------------------------------------------------------------*/

#include "vec.h"

#define _Vec_Normalise_MinMax  _BitM(0)
#define _Vec_Normalise_RMS     _BitM(1)
#define _Vec_Normalise_MeanAbs _BitM(2)

PUBLIC S16 Vec_Normalise( S_Vec const *v, S_Vec *vn, S16 center, S16 size, U8 ctl )
{
   S16 LVAR min, max,               /* limits of the source vector            */
            srcSize, srcOfs;        /* center and size of the source vector   */

   /* For all except _MinMax, the source vector center is the mean */
   srcOfs = Vec_Mean(v);

   if( BSET(ctl, _Vec_Normalise_MinMax) )          /* normalise to extents?   */
   {
      min = _Vec_Min(v);
      max = _Vec_Max(v);

      srcSize = max - min;                         /* size is span of vector                    */
      srcOfs = ((S32)min + (S32)max) / 2;          /* and center is midway between min and max  */
   }
   else if( BSET(ctl, _Vec_Normalise_RMS) )        /* normalise to RMS?       */
   {
      srcSize = Vec_RMS(v);
   }
   else if( BSET(ctl, _Vec_Normalise_MeanAbs) )    /* normalise to Mean Abs?  */
   {
      srcSize = Vec_MeanAbs(v);
   }
   else                                            /* else no normalisation specified  */
   {                                               /* will just center the vector      */
      srcSize = 0;
   }
   Vec_AddScalar( vn, v, srcOfs );
   Vec_ByFraction( vn, (S_Vec const *)vn, size, (srcSize - center) );

   return srcSize;
}




 
