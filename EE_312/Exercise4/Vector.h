// Vector.h -- specification of the Vector abstract data type
#include <stdint.h>

/* The Vector we do as our C-language case study is limited to simulating
 * an array of integers (type int32_t). When we redo this data structure
 * in C++, we'll make a more useful Vector that can simulate an array of 
 * of anything. Also, as we're limited to C, this data structure will be
 * somewhat clunky to use, again, we'll fix that when we have the C++ tools
 *
 *
 * A Vector is always implemented using a dynamically allocated array
 * in practice, the abstract data type (i.e., the "class") for Vector is
 * just an interface wrapper around dynamically allocated arrays. The 
 * "improved" interface we provide includes
 *
 * 1. Bounds checking (no more buffer overlows creeping into production code)
 * 2. Adjustable size -- we can increase or decrease the size by adding or
 *    removing elements at the end of the array.
 *
 * In C, there are some stiff penalties (that clunkiness I talked about) to pay
 * to get these features. Most notably, it becomes incumbant upon our clients
 * (anyone who writes code using our Vector) to ensure that Vectors are always
 * properly initialized and always properly destroyed.
 *
 * The list of functions below is undoubtedly incomplete for a real-world
 * abstract data type. However, it is sufficient to do some basic ops on
 * Vectors. Recall that the "implied contract" states that client code will
 * NOT access the components inside the Vector struct (ever). Therefore 
 * anything that a client programmer might want to do must be provided by
 * the functions below
 */

struct Vector {
	/* hands off, please */
	uint32_t len;
	uint32_t capacity;
	int32_t* data;
};

#define nullptr NULL


/*
 * Creating, copying and destroying Vectors
 * These functions are used by the client to get a new Vector or to dispose of an old one
 */

/* create and return a new Vector with N elements, all elements are initialized to zeroe */
Vector createVector(uint32_t N);

/* create and return a new, empty Vector (no elements) */
Vector createVector(void);

/* duplicate an exiting Vector, do not change the source Vector
 * create and return a new Vector that is a duplicate of the source Vector
 * the new Vector will have the same number of elements as source and each
 * element in the new Vector will have the value of the corresponding element from source
 * (i.e., the new vector that's created is a duplicate) */
Vector duplicateVector(const Vector* source);

/* destroy a vector 
 * this function must be called by the client program when the client is done
 * with the Vector. The client must not use the Vector after calling this function */
void destroyVector(Vector* self);

/*
 * Basic ops on Vectors 
 */

/* return the kth element of the Vector (crash if k is out of bounds) */
int32_t get(const Vector* vec, uint32_t idx);

/* change the kth element of the Vector to be val (crash if k is out of bounds) */
void set(Vector* vec, uint32_t k, int32_t val);

/* return the number of elements in the Vector */
uint32_t size(const Vector* vec);

/*
 * changing size of a Vector
 */

/* add the value val to the end of the Vector (increases size by 1) */
void push_back(Vector* vec, int32_t val);

/* remove the value at the end of the Vector 
 * (drecreases size by 1, crashes if the Vector is empty) */
void pop_back(Vector* vec);