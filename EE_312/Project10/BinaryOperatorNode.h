#ifndef EE312Project10_BinaryOperatorNode_h
#define EE312Project10_BinaryOperatorNode_h

#include "Node.h"

namespace EE312Project10 {

	class BinaryOperatorNode : public Node {
	private:
		Node* arg1;
		Node* arg2;

	public:
		BinaryOperatorNode() :
		Node{} {
			arg1 = nullptr;
			arg2 = nullptr;
		}
		BinaryOperatorNode(Node* expr1, Node* expr2) :
		Node{}	{
			arg1 = expr1;
			arg2 = expr2;
		}

		//copy constructor
		BinaryOperatorNode(const BinaryOperatorNode& rhs) :
		Node{rhs} {
			Node* cloned_arg1 = rhs.getArg1Node()->clone();
			Node* cloned_arg2 = rhs.getArg2Node()->clone();

			this->setArg1Node(cloned_arg1);
			this->setArg2Node(cloned_arg2);
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const BinaryOperatorNode& rhs_subclass = dynamic_cast<const BinaryOperatorNode&>(rhs);
			delete arg1;
			delete arg2;
			//note: rhs's arg1 and arg2 nodes should not be nullptr.. ohterwise we just tried to dereference a nullptr.
			//under normal use, Binary operator nodes kinda need arg1, arg2 to exist so this shouldnt be a problem.
			Node* cloned_arg1 = rhs_subclass.getArg1Node()->clone();
			Node* cloned_arg2 = rhs_subclass.getArg2Node()->clone();
			arg1 = cloned_arg1;
			arg2 = cloned_arg2;

			return *this;
		}

		~BinaryOperatorNode(){
			delete arg1;
			delete arg2;
		}

		void setArg1Node(Node* n) {
			arg1 = n;
		}
		void setArg2Node(Node* n) {
			arg2 = n;
		}

		Node* getArg1Node() const {
			return arg1;
		}
		Node* getArg2Node() const {
			return arg2;
		}

		

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//call execute on arg1 and arg2
			//these should terminate in leaf nodes.. eventually.. Return epxressions should not be in htese expression even though it might be legal
			arg1->execute(global_vars, local_vars, global_funcs, local_funcs, root);
			arg2->execute(global_vars, local_vars, global_funcs, local_funcs, root);

			//fetch data from arg1 and arg2
			int arg1_value = arg1->value();
			int arg2_value = arg2->value();
			
			//operate on Arguments and store as own value
			int result = binaryOperate(arg1_value, arg2_value);
			this->setValue(result);


			//Binary Operators will never have a "next instruction" to call execute on.
			/*if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs)
			}*/

		}

		//no need for clone function.. cannot be manually constructed.

	private:
		virtual int binaryOperate(int arg1, int arg2) = 0;
		
	};

}


#endif