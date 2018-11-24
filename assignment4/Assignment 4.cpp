#include "Matrix - 1061516- hw4.h"
#include <time.h>
void testAddition( int &numErrors );
void testMultiplication( int &numErrors );
int dimUpperBound = 8;

int main()
{
   for( unsigned int seed = 1; seed <= 30; seed++ )
   {
      srand( seed );
      int numErrors = 1000;
      for( int i = 0; i < 1000; i++ )
         testAddition( numErrors );
      cout << "There are " << numErrors << " errors.\n";
   }
   cout << endl;

   for( unsigned int seed = 1; seed <= 30; seed++ )
   {
      srand( seed );
      int numErrors = 1000;
      for( int i = 0; i < 1000; i++ )
         testMultiplication( numErrors );
      cout << "There are " << numErrors << " errors.\n";
   }
   cout << (double)clock() / CLOCKS_PER_SEC << " S";
   system( "pause" );
}

void testAddition( int &numErrors )
{
   int m = 2 + rand() % dimUpperBound;
   int n = 2 + rand() % dimUpperBound;

   TwoDimArray addend1( m, n );
   TwoDimArray adder1( m, n );
   TwoDimArray sum1( m, n );

   addend1.random();
   adder1.random();
   sum1 = addend1 + adder1;

   /*cout << addend1 << endl;
   cout << adder1 << endl;
   cout << sum1 << endl;*/

   Matrix addend2( addend1 );
   Matrix adder2( adder1 );
   Matrix sum2;
   sum2 = addend2 + adder2;
/*
   cout << addend2 << endl;
   cout << adder2 << endl;
   cout << sum2 << endl;
*/
   if( sum2 == sum1 )
      numErrors--;
}

void testMultiplication( int &numErrors )
{
   int m = 2 + rand() % dimUpperBound;
   int p = 2 + rand() % dimUpperBound;
   int n = 2 + rand() % dimUpperBound;

   TwoDimArray multiplicand1( m, p );
   TwoDimArray multiplier1( p, n );
   TwoDimArray product1( m, n );

   multiplicand1.random();
   multiplier1.random();
   product1 = multiplicand1 * multiplier1;

   /*cout << multiplicand1 << endl;
   cout << multiplier1 << endl;
   cout << product1 << endl;*/

   Matrix multiplicand2( multiplicand1 );
   Matrix multiplier2( multiplier1 );
   Matrix product2;

	   product2 = multiplicand2 * multiplier2;
/*
   cout << multiplicand2 << endl;
   cout << multiplier2 << endl;
   cout << product2 << endl;
*/
   if( product2 == product1 )
      numErrors--;
}