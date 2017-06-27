#ifndef EE312Project10_OutputNode_h
#define EE312Project10_OutputNode_h

#include "Node.h"

namespace EE312Project10 {

	class OutputNode : public Node {
	private:
		Node* value_arg;

	public:
		OutputNode() :
		Node{} {
			value_arg = nullptr;
		}
		OutputNode(Node* expr) :
		Node{}	{
			value_arg = expr;
		}

		~OutputNode(){
			delete value_arg;
		}

		void setExprNode(Node* n) {
			value_arg = n;
		}

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//call execute on value_arg
			value_arg->execute(global_vars, local_vars, global_funcs, local_funcs);

			//fetch data from value_arg
			int value = value_arg->value();
			
			//output to screen
			printf("%i", value);

			
			//execute next_instruction, if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs);
			}

		}


	private:
		//init(){}
		//OutputNode should never be copied
		//copy(){}
	};

}


#endif