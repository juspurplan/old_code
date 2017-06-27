#ifndef EE312Project10_ParseTree_h
#define EE312Project10_PraseTree_h

#include "Node.h"
#include "Map.h"
#include "Vector.h"

namespace EE312Project10 {
	class Node; //forward declare
	
	class ParseTree {
	private:
		Node* root;									//ParseTree owns Node

		Map<String, int>* global_vars;				//ParseTree does not own Map, needw R/W access
		Map<String, int> local_vars;

		Map<String, ParseTree*>* global_funcs;		//ParseTree does not own Map, needs R/W access
		Map<String, ParseTree*> local_funcs;

		Vector<String> param_names;

	public:
		//First 2 constructors bind the (global_vars/funcs pointers) with (local_vars/funcs member objects)
		//Call these 2 constructors imply that this ParseTree is some sort of "root" or "main()" tree.
		ParseTree() {
			global_vars = &local_vars;
			global_funcs = &local_funcs;	
			init(nullptr);
		}
		ParseTree(Node* n)  {
			global_vars = &local_vars;
			global_funcs = &local_funcs;
			init(n);
		}

		//Constructs a ParseTree where the global vars/funcs are bound with some memory outside the ParseTree.
		ParseTree(Map<String, int>& global_vars, Map<String, ParseTree*>& global_funcs) {
			this->global_vars = &global_vars;
			this->global_funcs = &global_funcs;
			init(nullptr);
		}
		ParseTree(Node* n, Map<String, int>& global_vars, Map<String, ParseTree*>& global_funcs) {
			this->global_vars = &global_vars;
			this->global_funcs = &global_funcs;
			init(n);
		}

		~ParseTree() {
			destroy();
		}

		//ParseTree now owns n, and all child Nodes.
		void setRoot(Node* n){
			this->root = n;
		}

		int execute(){
			if(root != nullptr){
				root->execute(*global_vars, local_vars, *global_funcs, local_funcs);
				//clear local variables/functions
				local_vars.clear();
				local_funcs.clear();
				return (root->value());
			}
			local_vars.clear();
			local_funcs.clear();
			return 0;
		}

		void setParamNames(Vector<String> list) {
			param_names = list;
		}
		void passArguments(Vector<Node*> args) {
			if(args.size() != param_names.size()) {
				printf("Expected %i arguments, %i found", param_names.size(), args.size());
			}
			for(int i = 0; i<param_names.size(); i++){
				local_vars.put(param_names[i], args[i]->value());
			}

		}


		//ParseTree now owns n, and all child Nodes.
		void init(Node* n){
			root = n;
		}
		void destroy(){
			delete root;
		}

		//ParseTree should never be copied. 
		//void copy(){}
	};

}

#endif