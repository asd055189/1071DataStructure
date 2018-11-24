#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <unordered_set>
#include "unordered_set - 1061516 - hw2.h"

bool duplicate( unsigned int *values, unsigned int i )
{
   for( unsigned int j = 0; j < i; j++ )
      if( values[ j ] == values[ i ] )
         return true;
   return false;
}

void testUnorderedSet1( unsigned int numData );
void testUnorderedSet2();

int main()
{
   unsigned int numDatas[ 7 ] = { 8, 64, 512, 1024, 2048, 4096, 8192 };
   for( unsigned int i = 0; i < 7; i++ )
   {
      srand( i );
      testUnorderedSet1( numDatas[ i ] );
   }

   cout << endl;

   for( unsigned int i = 1; i <= 10; i++ )
      testUnorderedSet1( 8 + rand() % 8184 );

   cout << endl;

   for( unsigned int seed = 1; seed <= 50; seed++ )
   {
      srand( seed );
      testUnorderedSet2();
   }
   cout << (double)clock() / CLOCKS_PER_SEC << " S";
   system( "pause" );
}

void testUnorderedSet1( unsigned int numData )
{
   std::unordered_set< unsigned int > data1;
   unordered_set< unsigned int > data2;

   unsigned int *values = new unsigned int[ numData ];
   for( unsigned int i = 0; i < numData; i++ )
      do
         values[ i ] = rand() % ( 5 * numData );
   while( duplicate( values, i ) );

   for( unsigned int i = 0; i < numData; i++ )
   {
      data1.insert( values[ i ] );
      data2.insert( values[ i ] );
   }

//   cout << numData << "   " << data1.size() << "   " << data2.size() << endl;

   if (data2 == data1)
	   cout << "Correct.\n";
   else
	   cout << "error= =\n";
}

void testUnorderedSet2()
{
   std::unordered_set< unsigned int > data1;
   unordered_set< unsigned int > data2;

   unsigned int numErrors = 201;
   if( data2 == data1 )
      numErrors--;

   unsigned int value;
   for( unsigned int i = 0; i < 200; i++ )
   {
      value = 1 + rand() % maxValue;
      switch( rand() % 2 )
      {
      case 0:
         data1.insert( value );
         data2.insert( value );
         break;
      case 1:
         if( data1.size() > 0 )
         {
            data1.erase( value );
            data2.erase( value );
         }
         break;
      default:
         break;
      }

      if( data2 == data1 )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}