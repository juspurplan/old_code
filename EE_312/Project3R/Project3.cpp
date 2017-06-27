/*
 * Replace this comment with the standard EE312 file header!



NAme: Alan Tan
Name: Alan Tan
EID: AJT 2459
Unique: 16675
TA: Kamran Saleem





 */

#include <assert.h>
#include <cstring>
#include "MemHeap.h"
#include "String.h"

/* use these two macros and the function functions if you want -- not required */
#define SIGNATURE (~0xdeadbeef)
#define STRING(s) (((String*)s)-1)

//Layout of String struct:
//uint32_t check		| 4 bytes
//uint32_t capacity 	| 4 bytes
//uint32_t length		| 4 bytes
//char* data 			| 4 bytes
//string 				| ? bytes


/* this simple function can be useful when you implement stage 4
 * you are not required to use the function, and you can implement stage 4 without it */
int32_t isOurs(char* s) {
    if (!isHeapVar(s)) { return 0; }
    if (STRING(s)->check == SIGNATURE) { return 1; }
    else { return 0; }
}

/* allocate a utstring on the heap, initialize the string correctly by copying
 * the characters from 'src' and return a pointer to the first character of actual string data */
char* utstrdup(const char* src) {
	
	uint32_t length = std::strlen(src);	//length of src. Without NULL character
	//malloc for String struct. and space afterwards to store the string.

	String* result = (String*) malloc(sizeof(String) +length +1);

	//initialize result's members.
	result->check = SIGNATURE;
	result->capacity = length;
	result->length = length;
	result->data = (char*)result + 16;
	std::memcpy(result->data, src, length+1);	//copy characters (+1 to include NULL) from src to data.
	
	return result->data; 						//return pointer to the actual C-string.
}

/* the parameter 'utstr' must be a utstring. Find the length of this string by accessing the meta-data
 * and return that length */
uint32_t utstrlen(const char* utstr) {
	//Refer to layout of String struct (top of page).
	//We are given String.data. 
	String* str_ptr = (String*)(utstr - 16);
	assert(str_ptr->check == SIGNATURE);
	return str_ptr->length;
}

/* s must be a utstring. suffix can be an ordinary string (or a utstring)
 * append the characters from suffix to the string s. Do not allocate any additional storage, and
 * only append as many characters as will actually fit in s. Update the length meta-data for utstring s
 * and then return s */
char* utstrcat(char* s, const char* suffix) {
	//Refer to layout of String struct (top of page).
	String* dest = (String*)(s-16);
	assert(dest->check == SIGNATURE);

	uint32_t num_chars_to_copy = std::strlen(suffix);

	if (dest->capacity == dest->length) {											//no space: don't copy
		return dest->data;
	}
	else if ( dest->capacity - dest->length >= num_chars_to_copy){					//enough space: copy all chars
		std::memcpy(dest->data + dest->length, suffix, num_chars_to_copy+1);
		*(dest->data + dest->length + num_chars_to_copy) = 0;
		dest->length += num_chars_to_copy;
		return dest->data;
	}
	else {																			//only some space: copy only enough to fill up String struct
		std::memcpy(dest->data + dest->length , suffix, (dest->capacity - dest->length));
		*((char*)(dest->data + dest->capacity )) = 0;
		dest->length = dest->capacity;
		return dest->data;
	}
}

/* 'dst' must be a utstring. 'src' can be an ordinary string (or a utstring)
 * overwrite the characters in dst with the characters from src. Do not overflow the capacity of dst
 * For example, if src has five characters and dst has capacity for 10, then copy all five characters
 * However, if src has ten characters and dst only has capacity for 8, then copy only the first 8
 * characters. Do not allocate any additional storage, do not change capacity. Update the length
 * meta-data for dst and then return dst */
char* utstrcpy(char* dst, const char* src) {
	//Refer to layout of String struct (top of page).
	String* dest = (String*)(dst-16);
	assert(dest->check == SIGNATURE);

	uint32_t num_chars_to_copy = std::strlen(src);

	if ( dest->capacity >= num_chars_to_copy){										//enough space: copy all chars
		std::memcpy(dest->data, src, num_chars_to_copy+1);
		dest->length = num_chars_to_copy;
		return dest->data;
	}
	else {																			//only some space: copy only enough to fill up String struct
		std::memcpy(dest->data, src, dest->capacity);
		*((char*)(dest->data + dest->capacity)) = 0;
		dest->length += dest->capacity;
		return dest->data;
	}

}

/* self must be a utstring. deallocate the storage for this string
 * (i.e., locate the start of the chunk and call free to dispose of the chunk, not that the start of
 * the chunk will be 12 bytes before *self) */
void utstrfree(char* self) {
	//Refer to layout of String struct (top of page).
	//pointer to String struct is offset by -12 bytes from self.
	String* str_ptr = (String*)(self-16);
	assert(str_ptr->check == SIGNATURE);
	free( str_ptr );
}

/* s must be a utstring.
 * ensure that s has capacity at least as large as 'new_capacity'
 * if s already has capacity equal to or larger than new_capacity, then return s
 * if s has less capacity than new_capacity, then allocate new storage with sufficient space to store
 * new_capacity characters (plus a terminating zero), copy the current characters from s into this
 * new storage. Update the meta-data to correctly describe new new utstring you've created, deallocate s
 * and then return a pointer to the first character in the newly allocated storage */
char* utstrrealloc(char* s, uint32_t new_capacity) {
	//Refer to layout of String struct (top of page).
	String* str_ptr = (String*)(s-16);

	//check if "s" is a String struct.
	assert(str_ptr->check == SIGNATURE);

	//Check if "s" has more/equal capacity than new_capacity.
	if( str_ptr->capacity >= new_capacity ){
		return s;
	}

	//malloc new String struct with the new capacity.
	String* result = (String*) malloc(sizeof(String)+new_capacity+1);
	result->check = SIGNATURE;
	result->capacity = new_capacity;
	result->length = str_ptr->length;
	result->data = (char*)result + 16;

	std::memcpy(result->data, str_ptr->data, str_ptr->length +1);

	//Free the original String struct.
	free(str_ptr);

	//return pointer to data
	return result->data;
}

