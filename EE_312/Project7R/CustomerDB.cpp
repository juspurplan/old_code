#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) {
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	String copy = name;
	if(isMember(name)) {
		for(int i = 0; i<length; i++){
			Customer& cust = data[i];
			if(cust.name == name){
				return cust;
			}
		}
	}
	else {
		if(length >= capacity) {
			capacity *= 2;
			Customer* new_data = new Customer[capacity];
			//copy over values from old DB to new DB
			for(int i = 0; i<length ; i++) {
				Customer& old_cust = data[i];
				Customer& new_cust = new_data[i];
				new_cust.name = old_cust.name;
				new_cust.bottles = old_cust.bottles;
				new_cust.rattles = old_cust.rattles;
				new_cust.diapers = old_cust.diapers;
			}
			//delete old DB , copy over pointer to new DB.
			delete[] data;
			data = new_data;
		}

		Customer& new_cust = data[length];
		new_cust.name = name;
		new_cust.bottles = 0;
		new_cust.rattles = 0;
		new_cust.diapers = 0;
		length ++;
		return new_cust;
	}
}



bool CustomerDB::isMember(String name) { // not done, your effort goes here
	for(int i = 0; i< length; i++) {
		Customer& cust = data[i];
		if(cust.name == name) {
			return true;
		}
	}

	return false;
}



