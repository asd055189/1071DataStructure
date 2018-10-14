#ifndef DEQUE_H
#define DEQUE_H

// deque class template definition
template< typename T >
class deque
{
public:
   deque(); // Constructs an empty deque container, with no elements.

   ~deque(); // Destroys the deque container.

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   deque& operator=( const deque &x );

   // Inserts a new element at the beginning of the deque container,
   // right before its current first element.
   // The content of val is copied to the inserted element.
   // This effectively increases the container size by one.
   void push_front( const T val );

private:
   T **map = nullptr;         // pointer to array of pointers to blocks
   unsigned int mapSize = 0;  // size of map array, zero or 2^N
   unsigned int myOff = 0;    // offset of initial element
   unsigned int mySize = 0;   // current length of sequence, in [ 0 .. 4 * mapSize )
}; // end class template deque


// Constructs an empty deque container, with no elements.
template< typename T >
deque< T >::deque()
   :     map( nullptr ),
     mapSize( 0 ),
       myOff( 0 ),
      mySize( 0 )
{
} // end deque default constructor

// destroys the deque container
template< typename T >
deque< T >::~deque()
{
   if( mapSize > 0 )
   {
      for( unsigned int i = 0; i < mapSize; i++ )
         if( map[ i ] != nullptr )
            delete [] map[ i ];
      delete[] map;
   }
} // end destructor

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
template< typename T >
deque< T >& deque< T >::operator=( const deque< T > &x )
{
   if( &x != this ) // avoid self-assignment
   {
	  
	   if (x.mySize == 0) {
		  	mySize = 0;	  			     //    ｜｜
		   myOff = 0;	  			 	 //    ｜｜
		   mapSize = 0;	  				 //    ｜｜   
		   map = nullptr;				 //    ＼／
		   return *this;				   /*modified*/
	   }
	   if (mapSize >= x.mapSize)
	   {
		   int row1 = myOff / 4;
		   int row2 = x.myOff / 4;
		  while (true)
		   {
			  if (row1 >= mapSize)
				  row1 %= mapSize;
			  if (row2 >= x.mapSize )
			  {
				  for (int FQ = 0; FQ < 4; FQ++)
					  map[row1][FQ] = x.map[row2%(x.mapSize )][FQ];
				  row1++;
				  row2++;
				  if (row2 % (x.mapSize ) == (x.myOff+x.mySize)%(x.mapSize * 4)/4)
					  break;
			  }
			  else {
				  for(int FQ=0;FQ<4;FQ++)
					  map[row1][FQ] = x.map[row2][FQ];
				  row1++;
				  row2++;
			  }
		   }
		  mySize = x.mySize;
	   }
	   else
	   { 
	   	   if (mapSize != 0)											//add
		  		 mapSize = x.mapSize;
		   T **tmp=new T*[x.mapSize];
		   int tmpsize = 0;
		   int row1 =  (mapSize==0)?9:myOff / 4;						//modified
		   int row2 = x.myOff / 4;
		   for (int i = 0; i < x.mapSize; i++)
			   tmp[i] = new T[4];
			   if (mapSize != 0) {										//modified
		   for (int j = row1, i = row1, k = 0; k < mapSize / 2; k++) {  //modified
			   if (map[i] != nullptr) {
				   if (j == mapSize)
					   j %= mapSize;
				 if (i == (mapSize) / 2)								//add
					i %= (mapSize) / 2;
				   tmp[j] = map[i];
				   j++;
				   i++;													//add
				   tmpsize++;
			   }
			   else 													//add
			   	j++;
		   }
		}
			   while (tmpsize != 0) {
				   if (row2 >= x.mapSize)
					   row2 %= x.mapSize;
				   if (row1 >= x.mapSize)
					   row1 %= x.mapSize;
					if (x.map[row2] != nullptr)							//add
				   for (int FQ = 0; FQ < 4; FQ++)
					   tmp[row1][FQ] = x.map[row2][FQ];
				   row1++;
				   row2++;
				   tmpsize--;
			   }
			   while (!(row2 % (x.mapSize) == (x.myOff + x.mySize) % (x.mapSize * 4) / 4))
			   {
				   if (row1 >= x.mapSize )								//modified
					   row1 %= x.mapSize;								//modified
					 if (row2 >= x.mapSize)								//add
					   row2%= x.mapSize;								//add
				   if (tmp[row1] == nullptr)
					   tmp[row1] = new T[4];
				   for (int FQ = 0; FQ < 4; FQ++)
					   tmp[row1][FQ] = x.map[row2][FQ];
				   row1++;
				   row2++;
				}
				map = new T*[x.mapSize];								//add
			   for (int i=0;i<x.mapSize;i++){
			   		map[i] = new T[4];									//add
			   
																		//for (int FQ = 0; FQ < 4; FQ++)//delete
					   if(map[i]!=nullptr)
					   map[i]= tmp[i];									//modified
				}if (mapSize == 0)									//    ｜｜	
				   myOff = 36;										//    ｜｜
				mySize = x.mySize;									//	  ＼／	
			   mapSize = x.mapSize;										/*add*/	
	   }



   } // end outer if
   return *this; // enables x = y = z, for example
} // end function operator=

template< typename T >
void deque< T >::push_front( const T val )
{
	if (mapSize == 0)
		mapSize = 8;
	if (map == nullptr)
		map = new T*[mapSize]();
	int Off = (myOff == 0) ? 4 * mapSize - 1 : myOff - 1;
	if (myOff%4==0 && (myOff+mySize)%(4*mapSize)+3==Off) {
		
		T **newmap = new T*[mapSize*2]();
		for (int i = myOff/4; i <=mapSize ; i++) {
			if (i == mapSize) {
				for (int j = i % mapSize; j < myOff / 4; j++, i++)
					newmap[i] = map[j];
				break;
			}
			else
			newmap[i] = map[i];
			
		}
		if (newmap[Off / 4] == nullptr)
			newmap[Off / 4] = new T[4];
		
		newmap[Off / 4][3] = val;
		map = newmap;
		mapSize *= 2;
	}
	else {
		//if (map[myOff / 4] == nullptr)
		//	map[myOff / 4] = new T[4];
		if (map[Off / 4] == nullptr)
			map[Off / 4] = new T[4];
		map[Off / 4][Off % 4] = val;
	}
	myOff = Off;
	mySize++;
}

#endif

