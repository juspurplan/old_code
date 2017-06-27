#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}
	
	/* NOT REACHED */
	return 0;
}


/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust); 
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}
	
	return result;
}

void processPurchase() {
	String cust_name{"ivalid_customer"};
	String item_name{"invalid_item"};
	int num_bought = -999;

	readString(cust_name);
	readString(item_name);
	readNum(num_bought);

	int* item_count = selectInventItem(item_name);

	if(num_bought == 0 ){
		//customer didnt by anything
		//do nothing
		//debug line
		//printf("%s bought nothing\n", cust_name.c_str());
	} 
	else if (num_bought > *item_count) {
		//customer tried to buy too much.
		printf("Sorry %s, we only have %i %s\n", cust_name.c_str(), *item_count, item_name.c_str());
	}
	else {
		Customer& cust = database[cust_name];
		int* item = selectInventItem(item_name, cust);
		*item += num_bought;

		int* item_count = selectInventItem(item_name);
		*item_count -= num_bought;
	}
}

void processSummarize() {
	String bottle_str {"Bottles"};
	String diaper_str {"Diapers"};
	String rattle_str {"Rattles"};
	int* bottle_count = selectInventItem(bottle_str);
	int* diaper_count = selectInventItem(diaper_str);
	int* rattle_count = selectInventItem(rattle_str);

	printf("There are %i %s, %i %s and %i %s in inventory\n", *bottle_count, bottle_str.c_str(), *diaper_count, diaper_str.c_str(), *rattle_count, rattle_str.c_str());
	printf("we have had a total of %i different customers\n", database.size());

	Customer* max_bottle = findMax(bottle_str);
	Customer* max_diaper = findMax(diaper_str);
	Customer* max_rattle = findMax(rattle_str);

	if(max_bottle != nullptr) {
		printf("%s has purchased the most %s (%i)\n", max_bottle->name.c_str(), bottle_str.c_str(), max_bottle->bottles);
	}
	else {
		printf("no one has purchased any %s\n", bottle_str.c_str());
	}
	if(max_diaper != nullptr) {
		printf("%s has purchased the most %s (%i)\n", max_diaper->name.c_str(), diaper_str.c_str(), max_diaper->diapers);
	}
	else {
		printf("no one has purchased any %s\n", diaper_str.c_str());
	}
	if(max_rattle != nullptr) {
		printf("%s has purchased the most %s (%i)\n", max_rattle->name.c_str(), rattle_str.c_str(), max_rattle->rattles);
	}
	else {
		printf("no one has purchased any %s\n", rattle_str.c_str());
	}

	/*
	template:
	There are 96 Bottles, 80 Diapers and 50 Rattles in inventory
	we have had a total of 1 different customers
	Craig has puchased the most Bottles (4)
	Craig has purchased the most Diapers (120)
	no one has purchased any Rattles
	*/
}

void processInventory() {
	String item_name {"invalid_item"};
	int item_inc = -999;

	readString(item_name);
	readNum(item_inc);

	int* item_count = selectInventItem(item_name);
	*item_count += item_inc;
}