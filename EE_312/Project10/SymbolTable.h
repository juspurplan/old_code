#ifndef EE312Project10_SymbolTable_h
#define EE312Project10_SymbolTable_h

#include "Vector.h"
#include "String.h"


/*
		==================
		|| 	IMPORTNANT  ||
		==================

		+ This file is unused in Project 10
		+ This is basically the hardcoded version of a Map.
*/

namespace EE312Project10 {

	class SymbolEntry {
	private:
		String key;
		int value;

	public:
		SymbolEntry(String key) {
			init(key,0);
		}
		SymbolEntry(String key, int value) {
			init(key, value);
		}

		//copy constructor
		SymbolEntry(SymbolEntry& rhs) {
			init(String{"COPYING"}, 0);
			copy(rhs)
		}
		//assignment copy
		SymbolEntry& operator=(SymbolEntry& rhs){
			if(this != &rhs){
				destroy();
				copy(rhs);
			}
			return *this;
		}

		int value(){
			return value;
		}

		String getKey() {
			return key;
		}

		void setValue(int value){
			this->value = value;
		}

		void setKey(String key){
			this->key = key;
		}

	private:
		void init(String s, int val){
			key = s;
			value = val;
		}
		void copy(SymbolEntry& rhs){
			key = rhs.getKey();
			value = rhs.value();
		}
		void destroy(){}
	};



	class SymbolTable {
	private:
		Vector<SymbolEntry> pairs;

	public:		
		SymbolTable(){

		}

		void put(String key, int value){
			if(containsKey(key)){
				int index = 0;
				for(; index<pairs.size(); index++){
					if(pairs[index].getKey() == key){
						break;
					}
				}
				SymbolEntry& pair = pairs[index];
				pair.setValue(value);
			}
			else{
				pairs.push_back(SymbolEntry{key, value});
			}
		}
		int get(String key){}

		bool containsKey(String key){
			for(int i = 0; i<pairs.size(); i++){
				if( pairs[i].getKey() == key){
					return true;
				}
			}
			return false;
		}

		void clear(){
			pairs.clear();
		}


	};

}

#endif