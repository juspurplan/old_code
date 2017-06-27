/* 
 * EE312 Simple CRM Project
 *
 * YOUR INFO HERE!


NAme: Alan Tan
Name: Alan Tan
EID: AJT 2459
Unique: 16675
TA: Kamran Saleem


 */

#include <stdio.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <assert.h>
#include "Invent.h"
#include "MyString.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

const int32_t MAX_ITEMS = 3;

int32_t* inventory_count = (int32_t*) calloc(MAX_ITEMS, sizeof(int32_t) );

int32_t getItemID(String* s) {
	String BOTTLE = StringCreate("Bottles");
	String DIAPER = StringCreate("Diapers");
	String RATTLE = StringCreate("Rattles");
	String NOT_AN_ITEM = StringCreate("NOT AN ITEM");
	int32_t result = 0;

	if (StringIsEqualTo(s, &BOTTLE)) {
		result = 0;
	} 
	else if (StringIsEqualTo(s, &DIAPER)) {
		result = 1;
	} 
	else if (StringIsEqualTo(s, &RATTLE)) {
		result = 2;
	}
	else{
		result = -1;
	}

	StringDestroy(&BOTTLE);
	StringDestroy(&DIAPER);
	StringDestroy(&RATTLE);
	StringDestroy(&NOT_AN_ITEM);
	return result;
}

//callee has ownership of the returned String
String getItemName(int32_t item_id){
	switch(item_id){
	case 0:
		return StringCreate("Bottles");
		break;
	case 1:
		return StringCreate("Diapers");
		break;
	case 2:
		return StringCreate("Rattles");
		break;
	default:
		return StringCreate("NOT AN ITEM");
		break;
	}
}

//returns ID or index of customer in array.
int32_t getCustomerID(String* s){
	int id = 0;
	for(;id < num_customers; id++){
		if( StringIsEqualTo(s, &(customers[id].name)) ) {
			return id;
		}
	}
	//end of loop:  id == num_customers + 1
	//name not found, return id == -1
	return -1;
}

int32_t getCustomerWithMostDiapers(){
	int32_t max = 0;
	int32_t id = -1;
	for(int32_t k = 0; k<num_customers; k++){
		if(customers[k].diapers > max && customers[k].diapers != 0){
			id = k;
			max = customers[k].diapers;
		}
	}
	return id;
}
int32_t getCustomerWithMostBottles(){
	int32_t max = 0;
	int32_t id = -1;
	for(int32_t k = 0; k<num_customers; k++){
		if(customers[k].bottles > max && customers[k].bottles != 0){
			id = k;
			max = customers[k].bottles;
		}
	}
	return id;

}
int32_t getCustomerWithMostRattles(){
	int32_t max = 0;
	int32_t id = -1;
	for(int32_t k = 0; k<num_customers; k++){
		if(customers[k].rattles > max && customers[k].rattles != 0){
			id = k;
			max = customers[k].rattles;
		}
	}
	return id;

}

//callee has ownership of returned c-string
char* toCString(String* s){
	char* result = (char*) malloc(sizeof(char) * (s->len +1));
	std::memcpy(result, s->ptr, sizeof(char) * s->len);
	*(result + s->len) = 0;									//write NULL character
	return result;

}

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */

	//clear inventory
	for(int k = 0; k < MAX_ITEMS; k++) {
		inventory_count[k] = 0;
	}

	//delete all customers
	for (int k = 0; k < num_customers; k++){
		StringDestroy( &customers[k].name );
	}
	num_customers = 0;
}

void processSummarize() {
	//printf("#processing summary\n" );
	printf("There are %i diapers, %i bottles and %i rattles in inventory\n", inventory_count[1] , inventory_count[0], inventory_count[2]);
	printf("we have had a total of %i different customers\n", num_customers);
	int32_t id_for_max_diapers=getCustomerWithMostDiapers();
	int32_t id_for_max_bottles=getCustomerWithMostBottles();
	int32_t id_for_max_rattles=getCustomerWithMostRattles();
	if(id_for_max_diapers != -1){
		char* name_diapers = toCString(& customers[id_for_max_diapers].name);
		printf("%s has purchased the most diapers (%i)\n", name_diapers, customers[id_for_max_diapers].diapers);
		free(name_diapers);
	}
	else{
		printf("no one has purchased any diapers\n");
	}
	if(id_for_max_bottles != -1){
		char* name_bottles = toCString(& customers[id_for_max_bottles].name);
		printf("%s has purchased the most bottles (%i)\n", name_bottles, customers[id_for_max_bottles].bottles);
		free(name_bottles);
	}
	else{
		printf("no one has purchased any bottles\n");
	}
	if(id_for_max_rattles != -1){
		char* name_rattles = toCString(& customers[id_for_max_rattles].name);
		printf("%s has purchased the most rattles (%i)\n", name_rattles, customers[id_for_max_rattles].rattles);
		free(name_rattles);
	}
	else{
		printf("no one has purchased any rattles\n");
	}
}

void processPurchase() {
	//printf("#processing purchase\n");
	String name;
	String item;
	int32_t count;

	//printf("	-reading 2 string, 1 num\n" ); 
	readString(&name);
	readString(&item);
	readNum(&count);
	//printf("	-finish read\n");

	int32_t customer_id = getCustomerID(&name);
	int32_t item_id = getItemID(&item);

	assert(item_id != -1);


	String item_name = getItemName(item_id);
	char* item_name_cstring = toCString(&item_name);
	char* customer_name_cstring = toCString( &name );
	if (count > inventory_count[item_id]) {
		printf("Sorry %s, we only have %i %s\n", customer_name_cstring, inventory_count[item_id], item_name_cstring);
	}
	else {
		inventory_count[item_id] -= count;
		if(customer_id == -1){			//first time customer, create an entry
			customer_id = num_customers;
			num_customers +=1;
			customers[customer_id].name = StringDup(&name);
			customers[customer_id].bottles = 0;
			customers[customer_id].diapers = 0;
			customers[customer_id].rattles = 0;
		}
		switch(item_id){
			case 0:
				customers[customer_id].bottles += count;
				break;
			case 1:
				customers[customer_id].diapers += count;
				break;
			case 2:
				customers[customer_id].rattles += count;
				break;
		}
		/*String temp0 = getItemName(item_id);
		char* temp1 = toCString(&  temp0);
		printf("	-%s:%i buys %i of %s\n", customer_name_cstring, customer_id, count, temp1);
		StringDestroy(&temp0);
		free(temp1);*/
	}
	StringDestroy(&item_name);
	free(item_name_cstring);
	free(customer_name_cstring);

	//printf("	-freeing input\n");
	StringDestroy(&name);
	StringDestroy(&item);
	free(&count);
	//printf("	-finish freeing\n");
}

void processInventory() {
	//printf("#processing inventory\n");
	String input;
	int32_t count;

	//printf("	-reading 1 string, 1 num\n" ); 
	readString(&input);
	readNum(&count);
	//printf("	-finish read\n");

	int32_t item_id = getItemID(&input);
	assert(item_id != -1);					//Error, we have a bad item id.
	inventory_count[item_id] += count;
	//printf("	-adding %i of item %i\n", count, item_id);

	//printf("	-freeing input\n");
	StringDestroy(&input);
	free(&count);
	//printf("	-finish freeing\n");
}