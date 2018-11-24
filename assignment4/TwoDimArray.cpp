#include "TwoDimArray.h"

TwoDimArray::TwoDimArray( int inputNumRows, int inputNumCols )
{
   if( inputNumRows == 0 || inputNumCols == 0 )
   {
      numRows = 0;
      numCols = 0;
      ptr = nullptr;
   }
   else
   {
      numRows = inputNumRows;
      numCols = inputNumCols;
      ptr = new int*[ numRows ];
      for( int i = 0; i < numRows; i++ )
         ptr[ i ] = new int[ numCols ]();
   }

   numValues = 0;
}

TwoDimArray::TwoDimArray( const TwoDimArray &twoDimArrayToCopy )
{
   if( twoDimArrayToCopy.numRows != 0 )
   {
      numRows = twoDimArrayToCopy.numRows;
      numCols = twoDimArrayToCopy.numCols;
      numValues = twoDimArrayToCopy.numValues;
      ptr = new int*[ numRows ];
      for( int i = 0; i < numRows; i++ )
         ptr[ i ] = new int[ numCols ];

      for( int i = 0; i < numRows; i++ )
         for( int j = 0; j < numCols; j++ )
            ptr[ i ][ j ] = twoDimArrayToCopy.ptr[ i ][ j ];
   }
}

TwoDimArray::~TwoDimArray()
{
   if( numRows != 0 )
   {
      for( int i = 0; i < numRows; i++ )
         delete[] ptr[ i ];
      delete[] ptr;
   }
}

const TwoDimArray& TwoDimArray::operator=( const TwoDimArray &op2 )
{
   if( &op2 != this ) // avoid self-assignment
   {
      if( op2.numRows == 0 )
      {
         if( numRows != 0 )
         {
            for( int i = 0; i < numRows; i++ )
               delete[] ptr[ i ];
            delete[] ptr;
            ptr = nullptr;
            numRows = 0;
            numCols = 0;
            numValues = 0;
         }
      }
      else
      {
         if( numRows != 0 )
            if( numRows != op2.numRows || numCols != op2.numCols )
            {
               for( int i = 0; i < numRows; i++ )
                  delete[] ptr[ i ];
               delete[] ptr;
            }

         numRows = op2.numRows;
         numCols = op2.numCols;
         numValues = op2.numValues;
         ptr = new int*[ numRows ];
         for( int i = 0; i < numRows; i++ )
            ptr[ i ] = new int[ numCols ];

         for( int i = 0; i < numRows; i++ )
            for( int j = 0; j < numCols; j++ )
               ptr[ i ][ j ] = op2.ptr[ i ][ j ];
      }
   }

   return *this; // enables x = y = z, for example
}

void TwoDimArray::random()
{
   numValues = 1 + rand() % ( numRows * numCols );
   int row;
   int col;
   int value;
   for( int i = 0; i < numValues; i++ )
   {
      do {
         row = rand() % numRows;
         col = rand() % numCols;
      } while( ptr[ row ][ col ] != 0 );

      do value = -9 + rand() % 19;
      while( value == 0 );

      ptr[ row ][ col ] = value;
   }
}

TwoDimArray TwoDimArray::operator+( TwoDimArray &op2 )
{
   if( ptr == nullptr )
      return op2;

   if( op2.ptr == nullptr )
      return *this;

   TwoDimArray sum( numRows, numCols );
   if( numRows != op2.numRows || numCols != op2.numCols )
      return sum;

   if( numRows <= 0 || numCols <= 0 )
      return sum;

   sum.numValues = 0;
   for( int i = 0; i < numRows; i++ )
      for( int j = 0; j < numCols; j++ )
      {
         sum.ptr[ i ][ j ] = ptr[ i ][ j ] + op2.ptr[ i ][ j ];
         if( sum.ptr[ i ][ j ] != 0 )
            sum.numValues++;
      }

   return sum;
}

TwoDimArray TwoDimArray::operator*( TwoDimArray &op2 )
{
   TwoDimArray product( numRows, op2.numCols );
   product.numValues = 0;
   for( int i = 0; i < numRows; i++ )
      for( int j = 0; j < op2.numCols; j++ )
      {
         for( int k = 0; k < numCols; k++ )
            product.ptr[ i ][ j ] += ptr[ i ][ k ] * op2.ptr[ k ][ j ];

         if( product.ptr[ i ][ j ] != 0 )
            product.numValues++;
      }

   return product;
}

ostream& operator<<( ostream &os, TwoDimArray &twoDimArray )
{
   for( int i = 0; i < twoDimArray.numRows; i++ )
   {
      for( int j = 0; j < twoDimArray.numCols; j++ )
         os << setw( 4 ) << twoDimArray.ptr[ i ][ j ];
      os << endl;
   }

   return os; // enables cout << x << y;
}