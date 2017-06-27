#ifndef EE312Project10_Node_h
#define EE312Project10_Node_h 

#include "Parse.h"
#include "String.h"
#include "Map.h"

namespace EE312Project10 {
	class ParseTree; //forward declare
	
	class Node {
	private:
		int node_value;
		String node_string;
		bool is_returning;

	protected:
		Node* next_node;

	public:

		Node() {
			init(0);
		}

		Node(int value) {
			init(value);
		}

		Node(int value, String str) :
		node_string{str} {
			init(value);
		}

		//copy constructor
		Node(const Node& rhs) {
			this->setValue(rhs.value());
			this->setString(rhs.getString());
			is_returning = false;

			if(rhs.getNextNode() != nullptr){
				Node* cloned_next_node = rhs.getNextNode()->clone();
				this->setNextNode(cloned_next_node);
			}
			else{
				this->setNextNode(nullptr);
			}
		}

		//assignment copy
		//for subclasses overriding this function:
		//I will use static_cast<> and assume that we are assignment copying the exact same type.
		//subclass1 <= sublcass1, works.
		//subclass1 <= subclass2, wont work.
		//baseclass <= subclass1, wont work.
		//subclass1 <= baseclass, wont work.
		virtual Node& operator=(const Node& rhs) {
			this->setValue(rhs.value());
			this->setString(rhs.getString());
			is_returning = false;

			delete next_node;
			next_node = nullptr;
			if(rhs.getNextNode() != nullptr){
				next_node = rhs.getNextNode()->clone();
			}

			return *this;
		}

		virtual ~Node() {	//recursive deleter.
			delete next_node;
		}

		int value() const {
			return node_value;
		}
		void setValue(int value) {
			node_value = value;
		}

		String getString() const {
			return node_string;
		}
		void setString(String str) {
			node_string = str;
		}

		void setNextNode(Node* next_node) {
			this->next_node = next_node;
		}

		Node* getNextNode() const {
			return next_node;
		}

		void setReturnStatus(bool status){
			is_returning = status;
		}
		bool isReturning() const {
			return is_returning;
		}

		virtual void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root) {
			//there is nothing to compute, base Nodes should only be used for int literals (and String literals)
			//subclass Nodes should override this depending on their job.

			//everytime a node executes a subnode, it should check for return status since
			//RETURN statements are not guaranteed to be leaf nodes.
			return;
		}

		//clone function:
		//calls respective copy constructor.
		virtual Node* clone() const {
			return new Node{*this};
		}

	private:
		void init( int n) {
			is_returning = false;
			node_value = n;
			next_node = nullptr;
		}

	protected:
		void debug(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs) {
			/*printf("\n");
			printf("GlobalVars.size = %i\n", global_vars->size());
			printf("LocalVars.size = %i\n", local_vars->size());
			printf("GlobalFuncs.size = %i\n", global_funcs->size());
			printf("LocalFuncs.size = %i\n", local_funcs->size());
			printf("\n");*/

		}


		//do not use, screwy with dynamic dispatch when called from destructor.
		//just copy paste to destructor.
		/*destroy() {
			delete next_node;
		}*/

	};

}


#endif