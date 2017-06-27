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

		virtual void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs) {
			//there is nothing to compute, base Nodes should only be used for int literals (and String literals)
			//subclass Nodes should override this depending on their job.
			return;
		}

	private:
		void init( int n) {
			node_value = n;
			next_node = nullptr;
		}
		//Node's should never be copied.
		//copy() {}

		//do not use, screwy with dynamic dispatch when called from destructor.
		//just copy paste to destructor.
		/*destroy() {
			delete next_node;
		}*/

	};

}


#endif