#include "Matrix - 1061516- hw4.h"

MatrixNode::MatrixNode( bool b, Triple &t )  // constructor
{
   head = b;
   if( b )
      right = down = next = this; // row/column header node
   else
      triple = t; // element node or header node for list of header nodes
}

Matrix::Matrix()
   : headNode( nullptr )
{
}

Matrix::Matrix( TwoDimArray &twoDimArray )
{
   Triple s;
   s.row = twoDimArray.numRows;
   s.col = twoDimArray.numCols;
   s.value = twoDimArray.numValues;

   if( s.col <= 0 || s.row <= 0 )
      return;

   // set up header node for the list of header nodes.
   headNode = new MatrixNode( false, s );

   Triple *triples = new Triple[ s.value ];
   int count = 0;
   for( int i = 0; i < s.row; i++ )
      for( int j = 0; j < s.col; j++ )
         if( twoDimArray.ptr[ i ][ j ] != 0 ) {
            triples[ count ].row = i;
            triples[ count ].col = j;
            triples[ count ].value = twoDimArray.ptr[ i ][ j ];
            count++;
         }

   int p = ( s.col > s.row ) ? s.col : s.row;

   // at least one row and column
   MatrixNode **head = new MatrixNode *[ p ];
   Triple zeroTriple = {};
   for( int i = 0; i < p; i++ )
      head[ i ] = new MatrixNode( true, zeroTriple ); // create header nodes

   int currentRow = 0;
   MatrixNode *last = head[ 0 ]; // last node in current row
   for( int i = 0; i < s.value; i++ ) // input triples
   {
      if( triples[ i ].row > currentRow ) // close current row
      {
         last->right = head[ currentRow ];
         currentRow = triples[ i ].row;
         last = head[ currentRow ];
      }

      // link new node into row list
      last = last->right = new MatrixNode( false, triples[ i ] );

      // link into column list
      head[ triples[ i ].col ]->next = head[ triples[ i ].col ]->next->down = last;
   }

   last->right = head[ currentRow ];// close last row

   // close all column lists
   for( int i = 0; i < s.col; i++ )
      head[ i ]->next->down = head[ i ];

   // link the header nodes together
   for( int i = 0; i < p - 1; i++ )
      head[ i ]->next = head[ i + 1 ];

   head[ p - 1 ]->next = headNode;
   headNode->right = head[ 0 ];
   delete[] head;
}

Matrix::Matrix( const Matrix &matrixToCopy )
{
	this->Matrix::Matrix();
	*this = matrixToCopy;
}

Matrix::~Matrix()
{
   erase();
}

const Matrix &Matrix::operator=( const Matrix &op2 )
{
	if (this != &op2) {
		erase();
			Triple zero = {};
			int Col = op2.headNode->triple.col;
			int Row = op2.headNode->triple.row;
			Triple Head = { Row,Col,op2.headNode->triple.value };
				headNode = new MatrixNode(false, Head);
			int Size = (Col > Row) ? Col : Row;
			MatrixNode ** body = new MatrixNode*[Size];
			for (int i = 0; i < Size; i++) {
				body[i] = new MatrixNode(true, zero);
			}
			for (int i = 0; i < Size; i++) {
				if (i == Size - 1)
					body[i]->next = headNode;
				else
					body[i]->next = body[i + 1];
			}
			headNode->right = body[0];
			MatrixNode *lhs = headNode->right;
			MatrixNode *rhs = op2.headNode->right;
			while (rhs->next != op2.headNode){
			
				MatrixNode *RColhead = rhs;
				MatrixNode *LColhead = lhs;
				while (rhs->down != RColhead){
					rhs = rhs->down;
					Triple tri = { rhs->triple.row,rhs->triple.col,rhs->triple.value };
					lhs->down = new MatrixNode (false, tri);
					lhs->down->down = LColhead;
					lhs = lhs->down;
				}
				lhs = lhs->down;
				rhs = rhs->down;
				rhs = rhs->next;
				lhs = lhs->next;
			}
	}
	return *this;
}

Matrix Matrix::operator+( Matrix &op2 )
{
	Matrix sum;
	Triple zero = {};
	int Col = op2.headNode->triple.col;
	int Row = op2.headNode->triple.row;
	Triple Head = {Row,Col,op2.headNode->triple.value };
	sum.headNode = new MatrixNode(false, Head);
	int Size = (Col > Row) ? Col : Row;
	MatrixNode ** result = new MatrixNode*[Size];
	for (int i = 0; i < Size; i++) 
		result[i] = new MatrixNode(true, zero);
	for (int i = 0; i < Size; i++) 
		if (i == Size - 1)
			result[i]->next = sum.headNode;
		else
			result[i]->next = result[i + 1];
	MatrixNode *lhs=headNode->right;
	MatrixNode *rhs = op2.headNode->right;
	MatrixNode *Cpointer;
	MatrixNode *Rpointer;
	int counter = 0;
	for (int i = 0; i < Col; i++) {
		Cpointer = result[i];
		for (int j = 0; j < Row; j++) {
			Rpointer = result[j];
			int Lval=0, Rval=0;
			if (lhs->down->triple.row == j) {
				lhs = lhs->down;
				Lval = lhs->triple.value;
			}
			if (rhs->down->triple.row == j) {
				rhs = rhs->down;
				Rval = rhs->triple.value;
			}
			if (Rval + Lval != 0) {
				counter++;
				Triple tri = { j,i,Rval + Lval };
				Cpointer->down = new MatrixNode(false, tri);
				
				if (Rpointer->right == result[j])
					Rpointer->right = Cpointer->down;
				else {
					while (Rpointer->right != result[j]) 
						Rpointer = Rpointer->right;
					Rpointer->right = Cpointer->down;
				}
				Rpointer->right->right = result[j];
				Cpointer = Cpointer->down;
			}
		}
		rhs = rhs->down;
		lhs = lhs->down;
		rhs=rhs->next;
		lhs=lhs->next;
		Cpointer->down = result[i];
	}
	sum.headNode->triple.value = counter;
	sum.headNode->right = result[0];
	return sum;
}

Matrix Matrix::operator*( Matrix &op2 )
{
	Matrix mult;
	Triple zero = {};
	int counter = 0;
	int Col = op2.headNode->triple.col;
	int Row =headNode->triple.row;
	Triple Head = { Row,Col,op2.headNode->triple.value };
	mult.headNode = new MatrixNode(false , Head);
	int size = (Col > Row) ? Col : Row;
	MatrixNode **result = new MatrixNode*[size];
	for (int i = 0; i < size; i++)
		result[i] = new MatrixNode(true, zero);
	for (int i = 0; i < size; i++)
		if (i == size - 1)
			result[i]->next = mult.headNode;
		else
			result[i]->next = result[i + 1];

	MatrixNode *lhs =headNode->right;
	MatrixNode *rhs = op2.headNode->right;
	MatrixNode *Lhead=lhs;
	MatrixNode *Rhead=rhs ;
		for (int j = 0; j < Row; j++){
			int val = 0;
			rhs = op2.headNode->right;
			for (int i = 0; i < Col; i++) {
				val = 0;
				
				if(rhs->down != rhs && lhs->right!= lhs) {
					
					Lhead = lhs;
					Rhead = rhs;
					lhs = lhs->right;
					rhs = rhs->down;
					while (true) {
						if (lhs->triple.col == rhs->triple.row) {
							val += rhs->triple.value*lhs->triple.value;
							rhs = rhs->down;
 							lhs = lhs->right;
						}
						else if (lhs->triple.col < rhs->triple.row) {
							lhs = lhs->right;
						}
						else if (lhs->triple.col > rhs->triple.row) {
							rhs = rhs->down;
						}
						if (lhs == Lhead) {
							rhs = Rhead;
							break;
						}
						if (rhs == Rhead) {
							lhs = Lhead;
							break;
						}
					}
				}
				if (val != 0)
				{
					MatrixNode *Cpointer, *Rpointer;
					Cpointer = result[i];
					Rpointer = result[j];
					counter++;
					Triple tri = { j,i,val };
					while (Cpointer->down != result[i]) {
						Cpointer = Cpointer->down;
					}
					Cpointer->down = new MatrixNode(false,tri);
					Cpointer->down->down = result[i];
					Cpointer->down->right = result[j];
					while (Rpointer->right != result[j]) {
						Rpointer = Rpointer ->right;
					}
					Rpointer->right = Cpointer->down;
				}
					rhs = rhs->next;
			}
			lhs = lhs->next;
		}
		mult.headNode->right = result[0];
		mult.headNode->triple.value = counter;
		return mult;
	}



void Matrix::erase()
{  // erase the matrix, return the nodes to the heap
   MatrixNode *x, *y;
   if( headNode != nullptr )
   {
      MatrixNode *head = headNode->right;

      while( head != headNode ) // free the triple and header nodes by row
      {
         y = head->right;
         while( y != head )
         {
            x = y;
            y = y->right;
            delete x;
         }

         x = head;
         head = head->next;
         delete x;
      }

      delete headNode;
      headNode = nullptr;
   }
}

bool Matrix::operator==( TwoDimArray &twoDimArray )
{
   int numRows = headNode->triple.row;
   int numCols = headNode->triple.col;

   if( numRows != twoDimArray.numRows )
      return false;

   if( numCols != twoDimArray.numCols )
      return false;

   if( headNode->triple.value != twoDimArray.numValues )
      return false;

   int col;
   MatrixNode *head = headNode->right;
   // scan header nodes one by one
   for( int row = 0; row < numRows; row++, head = head->next )
   {
      col = 0;
      // scan elements in the current row
      for( MatrixNode *temp = head->right; temp != head; temp = temp->right )
      {
         if( row != temp->triple.row )
            return false;

         // find next nonzero element in the current row
         while( twoDimArray.ptr[ row ][ col ] == 0 )
            col++;

         if( col != temp->triple.col )
            return false;

         if( twoDimArray.ptr[ row ][ col ] != temp->triple.value )
            return false;

         col++;
      }
   }
   
   int row;
   head = headNode->right;
   // scan header nodes one by one
   for( int col = 0; col < numRows; col++, head = head->next )
   {
      row = 0;
      // scan elements in the current column
      for( MatrixNode *temp = head->down; temp != head; temp = temp->down )
      {
         if( col != temp->triple.col )
            return false;

         // find next nonzero element in the current column
         while( twoDimArray.ptr[ row ][ col ] == 0 )
            row++;

         if( row != temp->triple.row )
            return false;

         if( twoDimArray.ptr[ row ][ col ] != temp->triple.value )
            return false;

         row++;
      }
   }

   return true;
}

ostream &operator<<( ostream &os, Matrix &matrix )
{  // print out the matrix in row major form
   int preCol;
   int numRows = matrix.headNode->triple.row;
   MatrixNode *head = matrix.headNode->right;
   // scan header nodes one by one
   for( int row = 0; row < numRows; row++, head = head->next )
   {
      preCol = -1;
      // scan elements in the current row
      for( MatrixNode *temp = head->right; temp != head; temp = temp->right )
      {
         // display zero elements
         for( int i = 1; i < temp->triple.col - preCol; i++ )
            os << setw( 4 ) << 0;
         os << setw( 4 ) << temp->triple.value; // display nonzero element
         preCol = temp->triple.col;
      }

      for( int i = 1; i < matrix.headNode->triple.col - preCol; i++ )
         os << setw( 4 ) << 0;
      os << endl;
   }

   return os; // enables os << x << y;
}