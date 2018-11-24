#ifndef MATRIX_H
#define MATRIX_H

#include "TwoDimArray.h"

struct Triple
{
   int row;
   int col;
   int value;
};

class MatrixNode
{
   friend class Matrix;
   friend ostream &operator<<( ostream &os, Matrix &matrix );
public:
   MatrixNode( bool b, Triple &t ); // constructor
private:
   MatrixNode *down;
   MatrixNode *right;
   bool head;
   union
   {
      MatrixNode *next;
      Triple triple;
   };
};

class Matrix
{
   // print out matrix in row major form
   friend ostream &operator<<( ostream &os, Matrix &matrix );
public:
   Matrix(); // default constructor with empty body

   // Constructs a matrix with a copy of each of the elements in twoDimArray.
   Matrix( TwoDimArray &twoDimArray );

   Matrix( const Matrix &matrixToCopy ); // copy constructor

   ~Matrix(); // destructor in which the matrix is erased

   const Matrix &operator=( const Matrix &op2 );

   Matrix operator+( Matrix &op2 ); // Returns the sum of two matrices.

   Matrix operator*( Matrix &op2 ); // Returns the product of two matrices.

   void erase(); // Erases the matrix.

   // Checks if the matrix and twoDimArray contain exactly the same elements.
   bool operator==( TwoDimArray &twoDimArray );
private:
   MatrixNode *headNode = nullptr; // a pointer to the header node for the list of header nodes
};

#endif