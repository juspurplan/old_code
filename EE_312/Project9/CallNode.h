#ifndef EE312Project10_CallNode_h
#define EE312Project10_CallNode_h

#include "Node.h"
#include "Vector.h"

namespace EE312Project10 {

	class CallNode : public Node {
	private:
		Node* func_name;
		Vector<Node*> arg_list;

	public:
		CallNode() :
		Node{} {
			func_name = nullptr;
		}
		CallNode(Node* name, Vector<Node*> list) :
		Node{}	{
			func_name = name;
			arg_list = list;
		}

		~CallNode(){
			delete func_name;
		}

		void setFunctionNameNode(Node* n) {
			func_name = n;
		}
		void setArgumentList(Vector<Node*> list) {
			arg_list = list;
		}
		

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			
			func_name->execute(global_vars, local_vars, global_funcs, local_funcs);
			String name = func_name->getString();

			int num_args = arg_list.size();
			for(int i = 0; i<num_args; i++){
				arg_list[i]->execute(global_vars, local_vars, global_funcs, local_funcs);
			}

			//check local memory
			if(local_funcs.containsKey(name)){
				ParseTree* func = local_funcs.get(name);
				func->passArguments(arg_list);
				int func_result = func->execute;
				setValue(func_result);	
			}
			//check global memory
			else if(global_funcs.containsKey(name)) {
				ParseTree* func = global_funcs.get(name);
				func->passArguments(arg_list);
				int func_result = func->execute;
				setValue(func_result);	
			}
			else {
				printf("function %s not found\n", name.c_str());
			}

			//execute next_instruction,  if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs)
			}

		}


	private:
		
		//init(){}
		//CallNode should never be copied
		//copy(){}
	};

}


#endif