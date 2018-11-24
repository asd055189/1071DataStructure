#ifndef TWO_DIM_ARRAY_H
#define TWO_DIM_ARRAY_H

#include <iostream>
#include <iomanip>
using namespace std;

class TwoDimArray
{
   friend class Matrix;
   friend ostream &operator<<( ostream &os, TwoDimArray &twoDimArray );
public:
   TwoDimArray( int inputNumRows = 0, int inputNumCols = 0 );
   TwoDimArray( const TwoDimArray &twoDimArrayToCopy );
   ~TwoDimArray();
   const TwoDimArray &operator=( const TwoDimArray &op2 );
   void random();
   TwoDimArray operator+( TwoDimArray &op2 );
   TwoDimArray operator*( TwoDimArray &op2 );
private:
   int numRows = 0;
   int numCols = 0;
   int numValues = 0;
   int **ptr = nullptr;
};

#endif
