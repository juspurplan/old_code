#ifndef EE312Project10_Map_h
#define EE312Project10_Map_h

#include "Vector.h"
#include <cstdio>
#include "String.h"


namespace EE312Project10 {

	template<class T, class V>
	class MapEntry {
	private:
		T key;
		V value;

	public:
		MapEntry():
			key{},
			value{} {
			//init(T, V);
		}
		MapEntry(T key) :
			key{key},
			value{} {
		}
		MapEntry(T key, V value) :
			key{key},
			value{value}{
		}

		//copy constructor
		MapEntry(const MapEntry<T,V>& rhs) {
			init(T{}, V{});
			copy(rhs);
		}
		//assignment copy
		MapEntry<T,V>& operator=(const MapEntry<T,V>& rhs){
			if(this != &rhs){
				//destroy();
				copy(rhs);
			}
			return *this;
		}

		V getValue() const {
			return value;
		}

		T getKey() const {
			return key;
		}

		void setValue(V value){
			this->value = value;
		}

		void setKey(T key){
			this->key = key;
		}

	private:
		void copy(const MapEntry<T,V>& rhs) {
			this->key = rhs.getKey();
			this->value = rhs.getValue();
		}
		//void destroy(){}
	};



	template < class U, class W >
	class Map {
	private:
		Vector < MapEntry<U, W> > pairs;

	public:		
		Map() :
			pairs{} {
		}

		void put(U key, W value){
			if(containsKey(key)){
				int index = findIndex(key);
				MapEntry<U,W>& pair = pairs[index];
				pair.setValue(value);
				//printf("changing existing value at index = %i\n", index);
			}
			else{
				pairs.push_back(MapEntry<U,W>{key, value});
			}
		}

		W get(U key){
			if(containsKey(key)){
				int index = findIndex(key);
				return pairs[index].getValue();
			}
			else{
				printf("key is not in map");
				return W{};
			}

		}

		MapEntry<U,W> get(int index){
			return pairs[index];

		}

		bool containsKey(U key){
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

		int size(){
			return pairs.size();
		}


	private:
		int findIndex(U key){
			int index = 0;
			while(index < pairs.size()) {
				if(pairs[index].getKey() == key){
					break;
				}
				else{
					index++;
				}
				
			}
			return index;
		}

		///Maps cannot be copied...
		//at least not yet.. To be implemented.
		//although i probably dont need it for project 10
		void init(){}
		void destroy(){}
		void copy(){}


	};

}

#endif