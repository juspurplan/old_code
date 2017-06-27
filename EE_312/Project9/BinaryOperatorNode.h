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

		

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//call execute on arg1 and arg2
			arg1->execute(global_vars, local_vars, global_funcs, local_funcs);
			arg2->execute(global_vars, local_vars, global_funcs, local_funcs);

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


	private:
		virtual int binaryOperate(int arg1, int arg2) = 0;
		
		//init(){}
		//BinaryOperatorNode should never be copied
		//copy(){}
	};

}


#endif