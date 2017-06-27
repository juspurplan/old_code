// Vector.cpp -- implementation of the Vector abstract data type 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "Vector.h"

const uint32_t min_capacity = 8;

/*
 * Two initialization functions for Vectors
 * This one has an integer argument and it creates a Vector with N elements
 * with each element assigned the value zero
 */
Vector createVector(uint32_t N) {
	Vector result;

	result.len = N;
	result.capacity = N;
	result.data = (int32_t*) malloc(N * sizeof(int32_t));
	for (uint32_t k = 0; k < N; k += 1) {
		result.data[k] = 0;
	}

	return result;
}

/* 
 * this initialization function creates an empty vector (nothing in it)
 */
Vector createVector(void) {
	Vector result;

	result.len = 0;
	result.capacity = 0;
	result.data = nullptr;

	return result;
}

Vector duplicateVector(const Vector* source) {
	Vector result;

	result.len = source->len;
	result.capacity = source->capacity;

	if (result.len == 0) {
		result.data = nullptr;
	} else {
		result.data = (int32_t*) malloc(result.len * sizeof(int32_t));
		for (uint32_t k = 0; k < result.len; k += 1) {
			result.data[k] = source->data[k];
		}
	}

	return result;
}

void destroyVector(Vector* vec) {
	if (vec->data) { free(vec->data); }
}

uint32_t size(const Vector* vec) {
	return vec->len;
}

int32_t get(const Vector* vec, uint32_t k) {
	assert(k < vec->len);
	return vec->data[k];
}

void set(Vector* vec, uint32_t k, int32_t val) {
	assert(k < vec->len);
	vec->data[k] = val;
}

void push_back(Vector* vec, int32_t val) {
	if (vec->len == vec->capacity) {
		vec->capacity *= 2;
		vec->capacity += 1;

		int32_t* p = (int32_t*) malloc(vec->capacity * sizeof(int32_t));
		for (uint32_t k = 0; k < vec->len; k += 1) {
			p[k] = vec->data[k];
		}
		if (vec->data != nullptr) { free(vec->data); }
		vec->data = p;
	}
	vec->data[vec->len] = val;
	vec->len += 1;
}

void pop_back(Vector * vec) {
	assert(vec->len > 0);
	vec->len -= 1;
}