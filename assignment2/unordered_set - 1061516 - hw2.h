#ifndef UNORDERED_SET
#define UNORDERED_SET

unsigned int maxValue = 99;

// unordered_set class template definition
template< typename T >
class unordered_set
{
public:
   using iterator = typename list< T >::iterator;

   unordered_set();

   ~unordered_set();

   // Returns the number of elements in the unordered_set container.
   unsigned int size() const;

   // Searches the container for an element with k as value and
   // returns an iterator to it if found,
   // otherwise it returns an iterator to unordered_set::end
   // (the element past the end of the container).
   iterator find( const T &k );

   // Inserts a new element in the unordered_set.
   // The element is inserted only if it is not equivalent(µ¥»ù) to any other element
   // already in the container ( elements in an unordered_set have unique values ).
   // This effectively increases the container size by one.
   void insert( const T &val );

   // Removes from the unordered_set container a single element.
   // This effectively reduces the container size by one.
   void erase( const T &k );

   // Returns the number of buckets in the unordered_set container.
   unsigned int bucket_count() const;

   // Returns the number of elements in bucket n.
   unsigned int bucket_size( unsigned int n ) const;

   // Returns the bucket number where the element with value k is located.
   unsigned int bucket( const T &k ) const;

   // Returns true iff the current object is equal to data
   bool operator==( std::unordered_set< T > &data );

//   void verify( std::unordered_set< T > &data );

private:
   list< T > myList;	   // list of elements, must initialize before myVec

   vector< iterator > myVec;  // vector of list iterators, begin() then end() - 1

   unsigned int maxidx = 8; // current maximum key value

   // put a new element in the unordered_set when myVec is large enough
   void putIn( const T& val );

   // Computes hash value which will be used to compute bucket number
   unsigned int hashSeq( const unsigned int &key, unsigned int count ) const;
}; // end class template unordered_set


template< typename T >
unordered_set< T >::unordered_set()
{
   myVec.reserve( 16 );
   myVec.assign( 16, myList.end() );
}

template< typename T >
unordered_set< T >::~unordered_set()
{
   myList.clear();
   myVec.clear();
}

template< typename T >
unsigned int unordered_set< T >::size() const
{
   return myList.size();
}

template< typename T >
typename unordered_set< T >::iterator unordered_set< T >::find( const T &k )
{
	iterator tmp;
	int number_of_vec = 2 * bucket(k);
	tmp = myVec[number_of_vec];
	if(tmp== myList.end())
		return myList.end();
	while (*tmp != k&&tmp!= myVec[number_of_vec+1]) {
		++tmp;
	}
	if (*tmp != k && tmp == myVec[number_of_vec+1] )
		return myList.end();

	return tmp;
}

template< typename T >
void unordered_set< T >::insert( const T& val )
{
		if (size()== maxidx && find(val)==myList.end())
	{
		list<T> num_tmp(myList);
		maxidx = (size() < 512 ? size() * 8 : size() * 2);
		myVec.reserve(maxidx*2);
		myVec.assign(maxidx * 2, myList.end());
		myList.clear();

		iterator it ;
		 int i;
		 putIn(val);
		for (it = num_tmp.begin(),i = 0; i < num_tmp.size(); i++,it++)		
			putIn(*it);
	}
		else if(find(val) == myList.end())
			putIn(val);
}

template< typename T >
void unordered_set< T >::erase( const T &k )
{
	iterator pos = find(k);
	if (pos != myList.end()) {
		int num_of_vector = bucket(k) * 2;
		if (*(myVec[num_of_vector]) == k&&myVec[num_of_vector] == myVec[num_of_vector + 1])
			myVec[num_of_vector] = myVec[num_of_vector + 1] = myList.end();
		else if (*(myVec[num_of_vector]) == k) {
			myVec[bucket(k) * 2] = ++pos;
			pos--;
		}
		else if (*(myVec[num_of_vector + 1]) == k)
		{
			myVec[bucket(k) * 2 + 1] = --pos;
			pos++;
		}
		myList.erase(pos);
	}
	//pos= myList.end();
}

template< typename T >
unsigned int unordered_set< T >::bucket_count() const
{
   return maxidx;
}

template< typename T >
unsigned int unordered_set< T >::bucket_size( unsigned int n ) const
{	
	if (myVec[2*n] == myList.end())
		return 0;
	int count = 1;
	for (iterator it = myVec[2*n];  it != myVec[2*n +1]; it++)
		count++;
	return count;
}

template< typename T >
unsigned int unordered_set< T >::bucket( const T &k ) const
{
   unsigned int hashValue = hashSeq( k, sizeof( T ) );
   return hashValue % maxidx; // bucket number
}

template< typename T >
void unordered_set< T >::putIn( const T& val )
{
 	int number_of_vec = 2 * bucket(val);
	iterator pos;
	if (myVec[number_of_vec] == myList.end())
		pos = myList.end();
	else
		pos = myVec[number_of_vec];

	myList.insert(pos, val);
	--pos;

	myVec[number_of_vec] = pos;
	if (myVec[number_of_vec + 1] == myList.end())
		myVec[number_of_vec + 1] = pos;
}

template< typename T >
unsigned int unordered_set< T >::hashSeq( const unsigned int &key, unsigned int count ) const
{
   const unsigned int _FNV_offset_basis = 2166136261U; // 10000001 00011100 10011101 11000101
   const unsigned int _FNV_prime = 16777619U;          // 00000001 00000000 00000001 10010011
   const unsigned char *first = reinterpret_cast< const unsigned char * >( &key );
   unsigned int val = _FNV_offset_basis;
   for( unsigned int next = 0; next < count; ++next )
   {	// fold in another byte
      val ^= static_cast< unsigned int >( first[ next ] );
      val *= _FNV_prime;
   }

   return val;
}

template< typename T >
bool unordered_set< T >::operator==( std::unordered_set< T > &data )
{
   if( myList.size() != data.size() )
      return false;

   unsigned int *firstVec = *( reinterpret_cast< unsigned int ** >( &data ) + 5 );
   vector< list< T >::iterator >::iterator it = myVec.begin();
   for( unsigned int bucketNo = 0; it != myVec.end(); ++it, bucketNo++ )
   {
      if( data.bucket_size( bucketNo ) != bucket_size( bucketNo ) )
         return false;

      unsigned int *stlBucketFirst = *( reinterpret_cast< unsigned int ** >( &firstVec[ 2 * bucketNo ] ) );
      unsigned int *stlBucketLast = *( reinterpret_cast< unsigned int ** >( &firstVec[ 2 * bucketNo + 1 ] ) );

      list< T >::iterator myBucketFirst = *it;
      ++it;
      list< T >::iterator myBucketLast = *it;
      if( myBucketFirst != myList.end() )
      {
         if( myBucketFirst == myBucketLast )
         {
            if( *myBucketFirst != *( stlBucketFirst + 2 ) )
               return false;
         }
         else
         {
            unsigned int *stlPtr = stlBucketFirst;
            list< T >::iterator myIt = myBucketFirst;
            while( myIt != myBucketLast )
            {
               if( *myIt != *( stlPtr + 2 ) )
                  return false;
               stlPtr = *( reinterpret_cast< unsigned int ** >( stlPtr ) );
               ++myIt;
            }

            if( *myBucketLast != *( stlBucketLast + 2 ) )
               return false;
         }
      }
   }

   for( unsigned int key = 1; key <= maxValue; key++ )
      if( data.bucket( key ) != bucket( key ) )
         return false;

   return true;
}

#endif