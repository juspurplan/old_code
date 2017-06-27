#ifndef EE312Project10_UnaryOperatorNode_h
#define EE312Project10_UnaryOperatorNode_h

#include "Node.h"

namespace EE312Project10 {

	class UnaryOperatorNode : public Node {
	private:
		Node* arg1;

	public:
		UnaryOperatorNode() :
		Node{} {
			arg1 = nullptr;
		}
		UnaryOperatorNode(Node* expr1) :
		Node{}	{
			arg1 = expr1;
		}

		//copy constructor
		UnaryOperatorNode(const UnaryOperatorNode& rhs) :
		Node{rhs} {
			arg1 = rhs.getArgNode()->clone();
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const UnaryOperatorNode& rhs_subclass = dynamic_cast<const UnaryOperatorNode&>(rhs);
			delete arg1;
			arg1 = rhs_subclass.getArgNode()->clone();
			
			return *this;
		}

		~UnaryOperatorNode(){
			delete arg1;
		}

		void setArgNode(Node* n) {
			arg1 = n;
		}
		Node* getArgNode() const {
			return arg1;
		}


		

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//call execute on arg1
			//shoudl end in leaf nodes
			//Return statements should not be in here even though it might be syntatically legal
			arg1->execute(global_vars, local_vars, global_funcs, local_funcs, root);

			//fetch data from arg1
			int arg1_value = arg1->value();
			
			//operate on Argument and store as own value
			int result = unaryOperate(arg1_value);
			this->setValue(result);

			//Unary Operators will never have a "next instruction" to call execute on.
			/*if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs)
			}*/
		}

		//there is no need for clone function.. purely abstract class.


	private:
		virtual int unaryOperate(int arg) = 0;
		
		//init(){}
		//UnaryOperatorNode should never be copied
		//copy(){}
	};

}


#endif