/*
 * Project4.c 
 *
 * My Name
 * My Section Time
 *
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {	
	int* array = self->elements;
	
	int bot = 0;
	int top = self->len;
	int i;
	while (top-bot > 0) {
		i = bot + ((top-bot)/2);
		int value = *(array+i);
		if ( value == x ) {
			return true;
		}
		else if (value > x) {
			top = i;
		}
		else { // (value < x)
			bot = i+1;
		}
	}
	return false;
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
	if (isMemberSet(self, x)){				//isMember is O(N)
		return;
	}

	//do insert
	int* array = self->elements;
	int i = 0;
	for ( ; i<self->len; i++) {
		if(*(array+i) > x){
			break;
		}
	}
	//i now points to the location to insert x into
	int* new_array = (int*) /*std::*/realloc(array, (self->len +1)*sizeof(int));  	//resize array
	std::memmove(new_array+i+1, new_array+i, (self->len - i)*sizeof(int));					//shift remaining contents over by 1
	*(new_array+i) = x;															//insert at i

	//update metadata, new pointer
	self->len = self->len +1;
	self->elements = new_array;
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
	if ( !isMemberSet(self, x) ){
		return;
	}

	//remove x
	int* array = self->elements;
	int i = 0;
	for ( ; i<self->len; i++){
		if( *(array+i) == x){
			break;
		}
	}
	std::memmove(array+i, array+i+1, (self->len - i -1)*sizeof(int));			//shift elements to the left by 1, overwriting the value at i.
	self->len = self->len -1;									
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
	if(self->len != other->len) {
		return false;
	}

	int* array0 = self->elements;
	int* array1 = other->elements;
	for(int i = 0; i<self->len; i++){
		if( *(array0+i) != *(array1+i) ){
			return false;
		}
	}
	return true;

}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
	int* array = self->elements;
	int* other_array = other->elements;

	//special case empty subset.. Emtpy subsets are always a subset of a bigger set
	if (self->len == 0){
		return true;
	}

	//non empty subsets.
	int index = 0;
	for (int i = 0; i<other->len; i++) {
		if (*(array+index) == *(other_array+i)) {
			index++;
		}
		if (index== self->len){
			return true;
		}
	}

	if (index == self->len) {
		return true;
	}
	else {
		return false;
	}
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
	int* self_arr = self->elements;
	int* other_arr = other->elements;

	int self_index = 0;
	int other_index = 0;
	int num_removed_elements = 0;
	int write_index = 0;

	while (self_index < self->len && other_index < other->len) {
		int self_value = *(self_arr+self_index);
		int other_value = *(other_arr+other_index);
		if (self_value == other_value) {
			*(self_arr+write_index) = self_value;
			write_index++;
			self_index++;
			other_index++;
		}
		else if (self_value < other_value) {
			num_removed_elements++;
			self_index++;
		}
		else { /* (self_value > other_value) */
			other_index++;
		}
	}
	if (self_index < self->len) {
		num_removed_elements += (self->len - self_index);
	}
	self->len -= num_removed_elements;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
	int* self_arr = self->elements;
	int* other_arr = other->elements;

	int self_index = 0;
	int other_index = 0;
	int num_removed_elements = 0;
	int write_index = 0;

	while (self_index < self->len && other_index < other->len) {
		int self_value = *(self_arr+self_index);
		int other_value = *(other_arr+other_index);
		if (self_value == other_value) {
			num_removed_elements++;
			self_index++;
			other_index++;
		}
		else if (self_value < other_value) {
			*(self_arr+write_index) = self_value;
			write_index++;
			self_index++;
		}
		else { /* (self_value > other_value) */	
			other_index++;
		}
	}
	while (self_index < self->len) {
		*(self_arr+write_index) = *(self_arr+self_index);
		write_index++;
		self_index++;
	}
	self->len -= num_removed_elements;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
	self->elements = (int*) /*std::*/realloc(self->elements, (self->len + other->len +1)*sizeof(int));		//realloc more space for potential union.

	//shift self array over by other->len to prevent elements from being overwritten when we still need the value.
	std::memmove(self->elements+other->len, self->elements, (self->len)*sizeof(int));

	int* self_arr = self->elements;
	int* other_arr = other->elements;

	int self_index = other->len;
	int other_index = 0;
	int num_elements = 0;
	int write_index = 0;

	while (self_index < self->len + other->len && other_index < other->len) {
		int self_value = *(self_arr+self_index);
		int other_value = *(other_arr+other_index);
		if (self_value == other_value) {
			*(self_arr+write_index) = self_value;
			write_index++;
			num_elements++;
			self_index++;
			other_index++;
		}
		else if (self_value < other_value) {
			*(self_arr+write_index) = self_value;
			write_index++;
			num_elements++;
			self_index++;
		}
		else { /* (self_value > other_value) */	
			*(self_arr+write_index) = other_value;
			write_index++;
			num_elements++;
			other_index++;
		}
	}

	while (self_index < self->len +other->len) {
		*(self_arr+write_index) = *(self_arr+self_index);
		write_index++;
		num_elements++;
		self_index++;
	}
	while (other_index < other->len) {
		*(self_arr+write_index) = *(other_arr+other_index);
		write_index++;
		num_elements++;
		other_index++;
	}

	self->len = num_elements;
}