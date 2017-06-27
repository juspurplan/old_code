#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "Vector.h"

void printVector(const Vector* v) {
	const char* prefix = "";
	for (uint32_t k = 0; k < size(v); k += 1) {
		printf("%s%d", prefix, get(v, k));
		prefix = ", ";
	}
	printf("\n");
}

bool testCreate(void) {
	Vector v = createVector(10);
	assert(size(&v) == 10); // confirm that v has 10 elements
	for (uint32_t k = 0; k < 10; k += 1) {
		assert(get(&v, k) == 0); // confirm that each element is zero
	}
	return true;
}

int main(void) {
	Vector x = createVector(10); // create a vector with 10 elements

	for (uint32_t k = 0; k < 10; k += 1) {
		set(&x, k, k);
	}

	for (int32_t k = 0; k < 10; k += 1) {
		push_back(&x, k + 10);
	}

	set(&x, 3, 42);
	printVector(&x);

	/*
		Vector.cpp
		*nullptr not defined
		*destroyVector declared in Vector.h but no such definition.
		*typo: destoyVector
		*push_back fails to increase capacity of size=0 vectors.
			-changed behavior to new_cap = 2*old_cap + 1 
			when out of space.
	*/

	printf("================\n");
	printf("test vector::push_back\n\n");
	
	printf("creating empty vector.\n");
	printf("attempt to add 99 to vector.\n");
	Vector v = createVector(0);
	push_back(&v, 99);
	printf("v.len = %i\n", v.len);
	printf("v.cap = %i\n", v.capacity);
	assert(v.len == 1);
	assert(v.capacity >= 1);

	printf("\ncreate vector of size = 1\n");
	printf("push_back 99 to vector.\n");
	destroyVector(&v);
	v = createVector(1);
	push_back(&v, 99);
	printf("v.len = %i\n", v.len);
	printf("v.cap = %i\n", v.capacity);
	assert(v.len == 2);
	assert(v.capacity >= 2);

	destroyVector(&v);
	v = createVector(2);
	printf("\ncreate new vector of size = 2\n");
	printf("push_back 99\n");
	push_back(&v, 99);
	printf("pop_back 99\n");
	pop_back(&v);
	printf("v2 = duplicate v\n");
	Vector v2 = duplicateVector(&v);
	printf("v.len = %i\n", v.len);
	printf("v.cap = %i\n", v.capacity);
	printf("v2.len = %i\n", v2.len);
	printf("v2.cap = %i\n", v2.capacity);

	assert(v2.len == v.len);
	assert(v2.capacity == v.capacity);

	printf("\ntest for bad shallow copy\n");
	printf("push_back 88 to v2\n");
	push_back(&v2, 88);
	printf("v.len = %i\n", v.len);
	printf("v.cap = %i\n", v.capacity);
	printf("v2.len = %i\n", v2.len);
	printf("v2.cap = %i\n", v2.capacity);
	assert(v.len +1 == v2.len);

	printf("\nv= new vector of size 1\n");
	printf("push_back 99 to v, then pop_back\n");
	printf("v2 = duplicate v\n");
	destroyVector(&v);
	destroyVector(&v2);
	v = createVector(0);
	push_back(&v, 99);
	pop_back(&v);
	v2 = duplicateVector(&v);

}