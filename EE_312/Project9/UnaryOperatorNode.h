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

		~UnaryOperatorNode(){
			delete arg1;
		}

		void setArgNode(Node* n) {
			arg1 = n;
		}


		

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//call execute on arg1
			arg1->execute(global_vars, local_vars, global_funcs, local_funcs);

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


	private:
		virtual int unaryOperate(int arg) = 0;
		
		//init(){}
		//UnaryOperatorNode should never be copied
		//copy(){}
	};

}


#endif