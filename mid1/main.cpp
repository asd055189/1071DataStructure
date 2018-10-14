#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <deque>
#include "Deque - 1061516 - midterm.h"

struct Deque
{
   int **map;
   unsigned int mapSize;
   unsigned int myOff;
   unsigned int mySize;
};

void testMyDeque( unsigned int num1, unsigned int num2 );
void displayMyDeque( deque< int > &myDeque );
void displayStlDeque( std::deque< int > &stlDeque );
void snapshot( deque< int > &myDeque, Deque &dequeCopy, int **&mapCopy );
bool correct( deque< int > &deque1, deque< int > &deque2, Deque &dequeCopy, int **&mapCopy );
bool equal( std::deque< int > &deque1, deque< int > &deque2 );

int main()
{
   testMyDeque( 60, 180 );
  testMyDeque( 120, 180 );
	  testMyDeque( 0, 60 );
	testMyDeque( 60, 60 );
   
   system( "pause" );
}

void testMyDeque( unsigned int num1, unsigned int num2 )
{
   deque< int > myDeque1;
   for( unsigned int i = 0; i < num1; i++ )
      myDeque1.push_front( i );

   //displayMyDeque( myDeque1 );

   deque< int > myDeque2;
   for( unsigned int i = num1; i < num2; i++ )
      myDeque2.push_front( i );

   //displayMyDeque( myDeque2 );

   Deque dequeCopy;
   int **mapCopy;
   snapshot( myDeque2, dequeCopy, mapCopy );
   
   myDeque2 = myDeque1;

  //displayMyDeque( myDeque2 );

   if( correct( myDeque1, myDeque2, dequeCopy, mapCopy ) )
      cout << "Correct\n\n";;
   std::deque< int > stlDeque1;
   for( unsigned int i = 0; i < num1; i++ )
      stlDeque1.push_front( i );

  //displayStlDeque( stlDeque1 );

   std::deque< int > stlDeque2;
   for( unsigned int i = num1; i < num2; i++ )
      stlDeque2.push_front( i );

   //displayStlDeque( stlDeque2 );

   stlDeque2 = stlDeque1;

   //displayStlDeque( stlDeque2 );

   if( equal( stlDeque2, myDeque2 ) )
      cout << "Equal\n\n";
}

void displayMyDeque( deque< int > &myDeque )
{
   int **map = *( reinterpret_cast< int *** > ( &myDeque ) );

   unsigned int mapSize = *( reinterpret_cast< unsigned int * >( &myDeque ) + 1 );
   cout << "mapSize  " << mapSize << endl;

   unsigned int myOff = *( reinterpret_cast< unsigned int * >( &myDeque ) + 2 );
   cout << "myOff  " << myOff << endl;

   unsigned int mySize = *( reinterpret_cast< unsigned int * >( &myDeque ) + 3 );
   cout << "mySize  " << mySize << endl;

   cout << "map  " << map << endl;
   for( unsigned int i = 0; i < mapSize; i++ )
      if( map[ i ] == nullptr )
         cout << setw( 4 ) << "null\n";
      else
      {
         cout << setw( 2 ) << i << setw( 11 ) << map[ i ];
         for( unsigned int j = 0; j < 4; j++ )
            cout << setw( 5 ) << map[ i ][ j ];
         cout << endl;
      }

   cout << endl;
}

void displayStlDeque( std::deque< int > &stlDeque )
{
   int **map = *( reinterpret_cast< int *** > ( &stlDeque ) + 1 );

   unsigned int mapSize = *( reinterpret_cast< unsigned int * >( &stlDeque ) + 2 );
   cout << "mapSize  " << mapSize << endl;

   unsigned int myOff = *( reinterpret_cast< unsigned int * >( &stlDeque ) + 3 );
   cout << "myOff  " << myOff << endl;

   unsigned int mySize = *( reinterpret_cast< unsigned int * >( &stlDeque ) + 4 );
   cout << "mySize  " << mySize << endl;

   cout << "map  " << map << endl;
   for( unsigned int i = 0; i < mapSize; i++ )
      if( map[ i ] == nullptr )
         cout << setw( 4 ) << "null\n";
      else
      {
         cout << setw( 2 ) << i << setw( 11 ) << map[ i ];
         for( unsigned int j = 0; j < 4; j++ )
            cout << setw( 5 ) << map[ i ][ j ];
         cout << endl;
      }

   cout << endl;
}

bool equal( std::deque< int > &deque1, deque< int > &deque2 )
{
   int **map1 = *( reinterpret_cast< int *** > ( &deque1 ) + 1 );
   unsigned int mapSize1 = *( reinterpret_cast< unsigned int * >( &deque1 ) + 2 );
   unsigned int myOff1 = *( reinterpret_cast< unsigned int * >( &deque1 ) + 3 );
   unsigned int mySize1 = *( reinterpret_cast< unsigned int * >( &deque1 ) + 4 );

   int **map2 = *( reinterpret_cast< int *** > ( &deque2 ) );
   unsigned int mapSize2 = *( reinterpret_cast< unsigned int * >( &deque2 ) + 1 );
   unsigned int myOff2 = *( reinterpret_cast< unsigned int * >( &deque2 ) + 2 );
   unsigned int mySize2 = *( reinterpret_cast< unsigned int * >( &deque2 ) + 3 );

//   cout << mapSize1 << "  " << mapSize2 << endl;
//   cout << myOff1 << "  " << myOff2 << endl;
//   cout << mySize1 << "  " << mySize2 << endl << endl;

   if( mapSize1 != mapSize2 )
      return false;

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
         return true;
      else
         return false;

   if( myOff1 % ( 4 * mapSize1 ) != myOff2 % ( 4 * mapSize2 ) )
      return false;

   if( mySize1 != mySize2 )
      return false;

   unsigned int row, col;
   for( unsigned int i = myOff1; i < myOff1 + mySize1; ++i )
   {
      row = ( i / 4 ) % mapSize1;
//      cout << map1[ row ] << "  " << map2[ row ] << endl;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % 4;
        //cout << map1[ row ][ col ] << "  " << map2[ row ][ col ] << endl;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
      }
   }

   return true;
}

void snapshot( deque< int > &myDeque, Deque &dequeCopy, int **&mapCopy )
{
   int **map = *( reinterpret_cast< int *** > ( &myDeque ) );

   dequeCopy.mapSize = *( reinterpret_cast< unsigned int * >( &myDeque ) + 1 );
   dequeCopy.myOff = *( reinterpret_cast< unsigned int * >( &myDeque ) + 2 );
   dequeCopy.mySize = *( reinterpret_cast< unsigned int * >( &myDeque ) + 3 );

   dequeCopy.map = new int*[ dequeCopy.mapSize ];
   for( unsigned int i = 0; i < dequeCopy.mapSize; ++i )
      dequeCopy.map[ i ] = map[ i ];

   mapCopy = map;
}

bool correct( deque< int > &deque1, deque< int > &deque2, Deque &dequeCopy, int **&mapCopy )
{
   int **map2 = *( reinterpret_cast< int *** > ( &deque2 ) );
   unsigned int mapSize2 = *( reinterpret_cast< unsigned int * >( &deque2 ) + 1 );
   unsigned int myOff2 = *( reinterpret_cast< unsigned int * >( &deque2 ) + 2 );
   unsigned int mySize2 = *( reinterpret_cast< unsigned int * >( &deque2 ) + 3 );

   unsigned int mapSize1 = *( reinterpret_cast< unsigned int * >( &deque1 ) + 1 );
   unsigned int mySize1 = *( reinterpret_cast< unsigned int * >( &deque1 ) + 3 );
   unsigned int minSize = ( dequeCopy.mySize < mySize1 ) ? dequeCopy.mySize : mySize1;

   if( mapSize1 == 0 )
      if( mapSize2 == 0 )
         return true;
      else
         return false;

   if( dequeCopy.mySize > 0 && dequeCopy.myOff != myOff2 )
      return false;

//   cout << setw( 11 ) << mapCopy << setw( 11 ) << map2 << endl;
   if( dequeCopy.mapSize > mapSize1 )
      if( mapCopy != map2 )
         return false;

   for( unsigned int i = dequeCopy.myOff / 4; i < ( dequeCopy.myOff + minSize ) / 4; i++ )
   {
    //cout << setw( 2 ) << i << setw( 11 ) << dequeCopy.map[ i % dequeCopy.mapSize ]                             << setw( 11 ) << map2[ i % mapSize2 ] << endl;
      if( dequeCopy.map[ i % dequeCopy.mapSize ] != map2[ i % mapSize2 ] )
         return false;
   }

   return true;
}