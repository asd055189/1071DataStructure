#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <set>
#include "Set -1061516- hw3.h"

bool duplicate( unsigned int *keys, unsigned int i );

// preorder traversal
template< typename Kty >
void preorder( unsigned int *node, unsigned int *head );

// inorder traversal
template< typename Kty >
void inorder( unsigned int *node, unsigned int *head );

// returns true if and only if set1 == set2
template< typename Kty >
bool equal( std::set< Kty > &set1, set< Kty > &set2 );

// returns true if and only if 
// the subtree rooted at node1 is equal to the subtree rooted at node2
template< typename Kty >
bool equalTree( unsigned int *node1, unsigned int *head1,
                unsigned int *node2, unsigned int *head2 );

int main()
{
   unsigned int numKeys = 1000;
   unsigned int *keys = new unsigned int[ numKeys ];
   for( unsigned int seed = 1; seed <= 50; seed++ )
   {
      srand( seed );
      for( unsigned int i = 0; i < numKeys; i++ )
         do
            keys[ i ] = 1 + rand() % ( 5 * numKeys );
      while( duplicate( keys, i ) );

      std::set< unsigned int > set1;
      set< unsigned int > set2;

      unsigned int numErrors = numKeys + 1;
      if( equal( set1, set2 ) )
         numErrors--;


      unsigned int count = 0;
      for( unsigned int i = 0; i < numKeys; i++ )
      {
         switch( rand() % 3 )
         {
         case 0:
         case 1:
//            cout << "insert " << setw( 5 ) << keys[ count ] << endl;
            set1.insert( keys[ count ] );
            set2.insert( keys[ count ] );
            count++;

			   /*unsigned int *head2;
			   unsigned int *root2;
            head2 = *( reinterpret_cast< unsigned int ** >( &set2 ) );
            root2 = *( reinterpret_cast< unsigned int ** >( head2 + 1 ) );

            cout << "Preorder sequence:\n";
            preorder< unsigned int >( root2, head2 );

            cout << "\nInorder sequence:\n";
            inorder< unsigned int >( root2, head2 );
            cout << endl << endl;*/

            break;
         case 2:
            if( set1.size() > 0 )
            {
				
               unsigned int k = rand() % count;
//               cout << "erase " << setw( 5 ) << keys[ k ] << endl;
               set1.erase( keys[ k ] );
               set2.erase( keys[ k ] );

               for( unsigned int j = k + 1; j < numKeys; j++ )
                  keys[ j - 1 ] = keys[ j ];
               count--;
/*
               head2 = *( reinterpret_cast< unsigned int ** >( &set2 ) );
               root2 = *( reinterpret_cast< unsigned int ** >( head2 + 1 ) );

               cout << "Preorder sequence:\n";
               preorder< unsigned int >( root2, head2 );

               cout << "\nInorder sequence:\n";
               inorder< unsigned int >( root2, head2 );
               cout << endl << endl;
*/
            }
         }

         if( equal( set1, set2 ) )
            numErrors--;
      }

      cout << "There are " << numErrors << " errors.\n";
   }

   delete[] keys;

   system( "pause" );
}

bool duplicate( unsigned int *keys, unsigned int i )
{
   for( unsigned int j = 0; j < i; j++ )
      if( keys[ j ] == keys[ i ] )
         return true;
   return false;
}

// returns true if and only if set1 == set2
template< typename Kty >
bool equal( std::set< Kty > &set1, set< Kty > &set2 )
{
   unsigned int size1 = *( reinterpret_cast< unsigned int * >( &set1 ) + 2 );
   unsigned int size2 = *( reinterpret_cast< unsigned int * >( &set2 ) + 1 );
//   cout << "size1  " << size1 << endl;
//   cout << "size2  " << size2 << endl;

   if( size1 != size2 )
      return false;

   unsigned int *head1 = *( reinterpret_cast< unsigned int ** >( &set1 ) + 1 );
   unsigned int *head2 = *( reinterpret_cast< unsigned int ** >( &set2 ) );

   unsigned int color1 = *( head1 + 3 ) % 256;
   unsigned int color2 = *( head2 + 3 );
//   cout << "color1  " << color1 << endl;
//   cout << "color2  " << color2 << endl;

   if( color1 != color2 )
      return false;

   bool isNil1 = static_cast< bool >( *( head1 + 3 ) / 256 % 256 );
   bool isNil2 = static_cast< bool >( *( head2 + 4 ) );
//   cout << "isNil1  " << isNil1 << endl;
//   cout << "isNil2  " << isNil2 << endl << endl;

   if( isNil1 != isNil2 )
      return false;

   if( size1 == 0 )
      return true;

   unsigned int *root1 = *( reinterpret_cast< unsigned int ** >( head1 + 1 ) );
   unsigned int *root2 = *( reinterpret_cast< unsigned int ** >( head2 + 1 ) );
   return equalTree< Kty >( root1, head1, root2, head2 );
}

// returns true if and only if 
// the subtree rooted at node1 is equal to the subtree rooted at node2
template< typename Kty >
bool equalTree( unsigned int *node1, unsigned int *head1,
                unsigned int *node2, unsigned int *head2 )
{
   // node1 == head1 if and only if node1 is an external node
   // node2 == head2 if and only if node2 is an external node
   if( node1 == head1 && node2 == head2 )
      return true;

   if( node1 == head1 && node2 != head2 )
      return false;

   if( node1 != head1 && node2 == head2 )
      return false;

   Kty myVal1 = static_cast< Kty >( *( node1 + 4 ) );
   Kty myVal2 = static_cast< Kty >( *( node2 + 5 ) );


   if (myVal1 != myVal2)
   {
	      cout << "myVal1  " << myVal1 << endl;
		   cout << "myVal2  " << myVal2 << endl;
	   return false;
   }

   unsigned int color1 = *( node1 + 3 ) % 256;
   unsigned int color2 = *( node2 + 3 );

   if (color1 != color2) {
	     cout << "color1  " << color1 << endl;
  cout << "color2  " << color2 << endl;
	   return false;
   }

   bool isNil1 = static_cast< bool >( *( node1 + 3 ) / 256 % 256 );
   bool isNil2 = static_cast< bool >( *( node2 + 4 ) % 256 );

   if (isNil1 != isNil2) {
	     cout << "isNil1  " << isNil1 << endl;
  cout << "isNil2  " << isNil2 << endl << endl;
	   return false;
   }

   unsigned int *leftChild1 = *( reinterpret_cast< unsigned int ** >( node1 ) );
   unsigned int *rightChild1 = *( reinterpret_cast< unsigned int ** >( node1 + 2 ) );
   unsigned int *leftChild2 = *( reinterpret_cast< unsigned int ** >( node2 ) );
   unsigned int *rightChild2 = *( reinterpret_cast< unsigned int ** >( node2 + 2 ) );

   return equalTree< Kty >( leftChild1, head1, leftChild2, head2 ) &&
          equalTree< Kty >( rightChild1, head1, rightChild2, head2 );
}

// preorder traversal
template< typename Kty >
void preorder( unsigned int *node, unsigned int *head )
{
   if( node != head )
   {
      Kty myVal = static_cast< Kty >( *( node + 5 ) );
      unsigned int color = *( node + 3 ) % 256;
      cout << setw( 5 ) << myVal << ( color == Red ? "  R" : "  B" );

      unsigned int *leftChild = *( reinterpret_cast< unsigned int ** >( node ) );
      unsigned int *rightChild = *( reinterpret_cast< unsigned int ** >( node + 2 ) );
      preorder< unsigned int >( leftChild, head );
      preorder< unsigned int >( rightChild, head );
   }
}

// inorder traversal
template< typename Kty >
void inorder( unsigned int *node, unsigned int *head )
{
   if( node != head )
   {
      unsigned int *leftChild = *( reinterpret_cast< unsigned int ** >( node ) );
      inorder< unsigned int >( leftChild, head );

      Kty myVal = static_cast< Kty >( *( node + 5 ) );
      unsigned int color = *( node + 3 ) % 256;
      cout << setw( 5 ) << myVal << ( color == Red ? "R" : "B" );

      unsigned int *rightChild = *( reinterpret_cast< unsigned int ** >( node + 2 ) );
      inorder< unsigned int >( rightChild, head );
   }
}