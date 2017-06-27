/* Project2.cpp
 * Ima Student
 * EE312, Spring 2014
 * Project 2, Matrix Multiplication




Name: Alan Tan
EID: AJT 2459
Unique: 16675
TA: Kamran Saleem





 
 */

#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include "MatrixMultiply.h"

void printMatrixTest(double a[],  uint32_t rows,  uint32_t cols);
void matrixCopy(double* a_mat, double * b_mat, uint32_t rows, uint32_t cols);

/*
 * An example routine demonstrating the use of row-major ordering
 *
 * You do not need to use this function in your solution
 * (I didn't use it in mine!)
 *
 * given two matrices a and b, where the number of rows in b is equal
 * to the number of columns in a,
 * and given a row number 'row' and a column number 'col',
 * calculate the dot product of the row'th row from a and the col'th column from b
 *
 * recall the dot product is the sum of the element-by-element product of
 * the two vectors.
 */
double dotProduct(double a[], const uint32_t a_rows, const uint32_t a_cols,
    /* a is a matrix with a_rows rows and a_cols columns */
    double b[], const uint32_t b_cols,
    /* b is also a matrix.  It has a_cols rows and b_cols columns */
    uint32_t row, // an index of a row of a
    uint32_t col) { // an index of a column of b

        double sum = 0.0; // the result of the dot product is stored here
        uint32_t k = 0;
        while (k < a_cols) { // recall: a_cols == b_rows
            /* we need to multiply a[row, k] and b[k, col] and add that to sum */
            sum = sum + a[(row * a_cols) + k] * b[k * b_cols + col];
            /* recall a[i,j] is stored at a[(i * a_cols) + j] and b[i, j] is at b[(i * b_cols) + j] */
            k += 1;
        }

        return sum;
}

void multiplyMatrices(double a[], const uint32_t a_rows, const uint32_t a_cols, double b[], const uint32_t b_cols, double c[]) {
	//C = AR x BC
	//check if Matrix Multiplication exists.. a_cols == b_rows
	
	for (uint32_t row = 0; row < a_rows; row+=1) {
		for(uint32_t col = 0; col < b_cols; col+=1) {
			//Select element @ [r,c] from C
			//compute value for element @ [r,c]
			double sum = 0;
			for(uint32_t i = 0; i < a_cols; i++){
				//row major... array[c][r] = **()
				sum += (a[row*a_cols + i] * b[i*b_cols + col]);
			}
			//printf("%ix%i Ele @ [R=%i, C=%i] = %f\n", a_rows, b_cols, row, col, sum );
			c[row*b_cols + col] = sum;
		}
	}
}

#define READY_FOR_STAGE2

#ifdef READY_FOR_STAGE2

/* these three variables are used in Stage 2 to implement allocateSpace */
#define TOTAL_SPACE 10000
double memory_pool[TOTAL_SPACE];
uint32_t top_of_pool = 0;

/* you need to write this function. clearly it doesn't currently do anything */
PtrDouble allocateSpace(uint32_t size) {
	//check if there is not enough memory to allocate. 
	PtrDouble result;
	if ( top_of_pool + size >= TOTAL_SPACE ) {
		result = NULL;
	}
	else{
		//return pointer to allocated memory.
		//increment top_of_pool by size to show where the next available pice of memory is.
		result = memory_pool + top_of_pool;
		top_of_pool += size;
	}
	return result;
}

void multiplyMatrixChain(
    PtrDouble matrix_list[],
    uint32_t rows[],
    uint32_t cols[],
    uint32_t num_matrices,
    double out[],
    uint32_t out_rows,
    uint32_t out_cols) {
	/* NOTE:
	* the following comments and code are excerpts from my solution
	* If this stuff doesn't make sense to you, DELETE IT.
	* You will be better off developing your own approach from scratch
	* than trying to use code or an algorithm that you do not understand!
	*/

	/* The loop works by continually multiplying the a_mat
	* and b_mat matrix to obtain the c_mat matrix.
	* After each iteration, the previous "c_mat" becomes the
	* next "a_mat" matrix.  the b_mat matrix will be the
	* next matrix in the matrix_list array.
	*
	* For example, on the first time through a_mat is matrix_list[0]
	* b_mat is matrix_list[1]
	* c_mat (the output) will be a temporary matrix that you must allocate
	* space for.
	* After multiplying a_mat and b_mat together, you need to
	* take the result and multiply it by matrix_list[2],
	* so a_mat will be set to c_mat, and b_mat will be matrix_list[2]
	* you must again allocate a new temporary array to hold the result.
	*
	* There's no guarantee that the temporary arrays are the same size,
	* so there's no practical way to reuse the temporary arrays.
	* Therefore, allocate a new array each iteration.  We'll clean up when we're done.
	*/

	double* a_mat = matrix_list[0];
	uint32_t a_rows = rows[0]; // number of rows in a matrix
	uint32_t a_cols = cols[0]; // number of cols in a matrix
	uint32_t next_src = 1; // index of next matrix to multiply by
	double* b_mat;
	double* c_mat = 0;
	uint32_t b_cols;

	while (next_src < num_matrices) {
		/* Each iteration of the loop perform the following
		 * set c_mat = a_mat * b_mat where
		 * a_mat is the result from the previous iteration of the loop (or matrix_list[0] on the first iteration)
		 * b_mat is the next matrix in the matrix list
		 * c_mat is allocated space (using our handy-dandy memory allocator function) */
		b_mat = matrix_list[next_src];
		b_cols = cols[next_src];
		/* lots of really important code has been deleted from this loop 
		 * if it's easier for you, delete the entire loop an start from scratch */

		c_mat = allocateSpace(a_rows * b_cols);
		//c_mat = (double*) malloc(a_rows*b_cols*sizeof(double));

		multiplyMatrices(a_mat, a_rows, a_cols, b_mat, b_cols, c_mat);
		//printf("%i Mult ", next_src);
		//printf("%ix%i with %ix%i = %ix%i\n", a_rows, a_cols, a_cols, b_cols, a_rows, b_cols);
		//printMatrixTest(c_mat, a_rows, b_cols);

		//copy c_mat to a_mat.. update a_cols accordingly. 
		//There is no need to update a_rows because C's number of rows is equal to the original A's number of rows.
		a_mat = c_mat;
 		a_cols = b_cols;

		next_src += 1;
	}
	/* when the loop completes, c_mat points to the final matrix result */

	/* don't forget to ensure that the final result matrix is put
	* into the 'out' array!!! */
	matrixCopy(out, c_mat, out_rows, out_cols);

	/* deallocate all memory (this only takes one line, 'cause we have such a simple memory allocator) */
	//deallocates all memory;
	top_of_pool = 0;
}

void matrixCopy (double* dest_mat, double* source_mat, uint32_t rows, uint32_t cols) {
	for (uint32_t r = 0; r < rows; r+=1){
		for (uint32_t c = 0; c < cols; c+=1) {
			dest_mat[r*cols + c] = source_mat[r*cols + c];
		}
	}
}

void printMatrixTest(double a[],  uint32_t rows, uint32_t cols) {

	uint32_t i = 0;
	while (i < rows) {
		uint32_t j = 0;
		while (j < cols) {
			printf("%g, ", a[(i * cols) + j]); // %g is just like %f, only better
			j += 1;
		}
		printf("\n");
		i += 1;
	}
}

#endif /* READY_FOR_STAGE_2 */