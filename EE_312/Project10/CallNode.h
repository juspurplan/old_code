#ifndef EE312Project10_CallNode_h
#define EE312Project10_CallNode_h

#include "Node.h"
#include "Vector.h"

namespace EE312Project10 {

	class CallNode : public Node {
	private:
		Node* func_name;
		Vector<Node*> arg_list;
		//Vector<int>	values;

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

		//copy constructor
		CallNode(const CallNode& rhs) : 
		Node{rhs} {
			Node* cloned_func_name = rhs.getFunctionNameNode()->clone();
			
			this->setFunctionNameNode(cloned_func_name);
			this->setArgumentList(rhs.getArgumentList());
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const CallNode& rhs_subclass = dynamic_cast<const CallNode&>(rhs);
			delete func_name;
			//note: rhs's func_name should not be nullptr..
			Node* cloned_func_name = rhs_subclass.getFunctionNameNode()->clone();
			func_name = cloned_func_name;

			arg_list = rhs_subclass.getArgumentList();

			return *this;
		}

		~CallNode(){
			delete func_name;
			//delete things in arg_list
			for(int i = 0; i<arg_list.size(); i++){
				delete arg_list[i];
			}
		}

		void setFunctionNameNode(Node* n) {
			func_name = n;
		}
		void setArgumentList(Vector<Node*> list) {
			arg_list = list;
		}

		Node* getFunctionNameNode() const {
			return func_name;
		}
		Vector<Node*> getArgumentList() const {
			return arg_list;
		}
		

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			
			func_name->execute(global_vars, local_vars, global_funcs, local_funcs, root);
			String name = func_name->getString();

			int num_args = arg_list.size();
			for(int i = 0; i<num_args; i++){
				arg_list[i]->execute(global_vars, local_vars, global_funcs, local_funcs, root);
			}


			//check local memory
			if(local_funcs->containsKey(name)){
				//ParseTree* func = new ParseTree{*local_funcs->get(name)};
				ParseTree* func = local_funcs->get(name);
				func->setGlobals(global_vars, global_funcs);
				Map<String,int>* old_v1 = func->getLocalVars();
				Map<String,ParseTree*>* old_v2 = func->getLocalFuncs();
				Map<String, int>* v1 = new Map<String,int>{};
				Map<String, ParseTree*>* v2 = new Map<String, ParseTree*>{};

				func->setLocalVars(v1);
				func->setLocalFuncs(v2);

				func->passArguments(arg_list);
				
				int func_result = func->execute();
				func->setLocalVars(old_v1);
				func->setLocalFuncs(old_v2);

				setValue(func_result);	
				delete v1; delete v2;
				//delete func;
			//printf("[CALL] : %s : val = %i\n", name.c_str(), func_result);

			}
			//check global memory
			else if(global_funcs->containsKey(name)) {
				//ParseTree* func = new ParseTree{*global_funcs->get(name)};
				ParseTree* func = global_funcs->get(name);
				func->setGlobals(global_vars, global_funcs);
				Map<String,int>* old_v1 = func->getLocalVars();
				Map<String,ParseTree*>* old_v2 = func->getLocalFuncs();
				Map<String, int>* v1 = new Map<String,int>{};
				Map<String, ParseTree*>* v2 = new Map<String, ParseTree*>{};

				func->setLocalVars(v1);
				func->setLocalFuncs(v2);

				func->passArguments(arg_list);
				int func_result = func->execute();
				func->setLocalVars(old_v1);
				func->setLocalFuncs(old_v2);

				setValue(func_result);	
				delete v1; delete v2;				
				//delete func;
			//printf("[CALL] : %s : val = %i\n", name.c_str(), func_result);

			}
			else {
				printf("function %s not found\n", name.c_str());
			}

			//debug(global_vars, local_vars, global_funcs, local_funcs);

			//execute next_instruction,  if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs, root);
			
				//check for return status
				if(next_node->isReturning()){
					next_node->setReturnStatus(false);
					this->setReturnStatus(true);
					return;
				}
			}



		}

		Node* clone() const {
			return new CallNode{*this};
		}



	private:
		

	};

}


#endif