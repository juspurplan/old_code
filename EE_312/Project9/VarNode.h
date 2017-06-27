#ifndef EE312Project10_VarNode_h
#define EE312Project10_VarNode_h

#include "Node.h"

namespace EE312Project10 {

	class VarNode : public Node {
	private:
		Node* str_arg;
		Node* value_arg;

	public:
		VarNode() :
		Node{} {
			str_arg = nullptr;
			value_arg = nullptr;
		}
		VarNode(Node* var, Node* expr) :
		Node{}	{
			str_arg = var;
			value_arg = expr;
		}

		~VarNode(){
			delete str_arg;
			delete value_arg;
		}

		void setVarStringNode(Node* n) {
			str_arg = n;
		}
		void setExprNode(Node* n) {
			value_arg = n;
		}

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//call execute on str_arg, and value_arg
			str_arg->execute(global_vars, local_vars, global_funcs, local_funcs);
			value_arg->execute(global_vars, local_vars, global_funcs, local_funcs);

			//fetch data from str_arg, value_arg
			String str = str_arg->getString();
			int value = value_arg->value();
			
			//tries to put (str, value) pair in local vars.
			if(local_vars.containsKey(str)){
				printf("variable %s incorrectly re-initialized\n", str.c_str());
			}
			local_vars.put(str, value);

			
			//execute next_instruction, if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs);
			}

		}


	private:
		//init(){}
		//VarNode should never be copied
		//copy(){}
	};

}


#endif