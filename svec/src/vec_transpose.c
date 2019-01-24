/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_Transpose
|
|  Transpose in/out of 'mainVec' from/to 'ioVec'. The insert/extract point is [startRow, startCol]
|  in 'mainVec'.
|
|  Vec_Transpose() inserts or extracts a vector of size 'ioVec'. This unless part of 'ioVec' ranges
|  outside 'mainVec', in which only the part in-range is moved. If its an extraction to 'ioVec'
|  then 'ioVec' is shrunk to the amount actually extracted from 'mainVec'.
|  
|  RETURNS:
|     
|
|	DATE	      AUTHOR		      DESCRIPTION OF CHANGE 
|	--------		-------------		-------------------------------------
|
-------------------------------------------------------------------------------------------------*/

#include "vec.h"

PUBLIC void Vec_Transpose( S_Vec *mainVec, S_Vec *ioVec, T_VecRows startRow, T_VecCols startCol, U8 insert )
{
   T_VecRowOrCol rIDATA rows, r,
                        cols, c,
                        d;
   
   rows = ioVec->rows;              // rows to copy to/from 'mainVec'
   d = mainVec->cols - startCol;
   rows = MIN(rows, d);             // but no more than will fit/available
   
   cols = ioVec->cols;              // cols to copy to/from 'mainVec'
   d = mainVec->rows - startRow;
   cols = MIN(cols, d);             // but no more than will fit/available
   
   for( r = 0; r < rows; r++ )
   {
      for( c = 0; c < cols; c++ )
      {
         if( insert )               // mainVec <- ioVec, transposed
            { Vec_Write1(mainVec, _Vec_Read1(ioVec,r,c), startRow+c, startCol+r ); }
         else                       // else mainVec -> ioVec, transposed
            { Vec_Write1(ioVec, _Vec_Read1(mainVec,startRow+c,startCol+r), r, c ); }
      }
   }
   if( !insert )                    // extracted into 'ioVec'?
   {
      ioVec->rows = rows;           // then 'ioVec' is size of data actually extracted
      ioVec->cols = cols;           // which may be smaller than requested.
   }
}


 
