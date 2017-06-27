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
		Map<String, int>* local_vars;

		Map<String, ParseTree*>* global_funcs;		//ParseTree does not own Map, needs R/W access
		Map<String, ParseTree*>* local_funcs;

		Vector<String> param_names;

	public:
		//First 2 constructors bind the (global_vars/funcs pointers) with (local_vars/funcs member objects)
		//Call these 2 constructors imply that this ParseTree is some sort of "root" or "main()" tree.
		ParseTree() {
			local_vars = new Map<String, int>{};
			local_funcs = new Map<String, ParseTree*>{};

			global_vars = local_vars;
			global_funcs = local_funcs;	
			init(nullptr);
		}
		ParseTree(Node* n)  {
			local_vars = new Map<String, int>{};
			local_funcs = new Map<String, ParseTree*>{};

			global_vars = local_vars;
			global_funcs = local_funcs;
			init(n);
		}

		//Constructs a ParseTree where the global vars/funcs are bound with some memory outside the ParseTree.
		/*ParseTree(Map<String, int>& global_vars, Map<String, ParseTree*>& global_funcs) {
			this->global_vars = &global_vars;
			this->global_funcs = &global_funcs;
			init(nullptr);
		}
		ParseTree(Node* n, Map<String, int>& global_vars, Map<String, ParseTree*>& global_funcs) {
			this->global_vars = &global_vars;
			this->global_funcs = &global_funcs;
			init(n);
		}*/

		//copy constructor
		ParseTree(const ParseTree& rhs) {
			printf("copying tree\n");
			local_vars = new Map<String, int>{};
			local_funcs = new Map<String, ParseTree*>{};

		
			//global_vars = rhs.getGlobalVars();
			//global_funcs = rhs.getGlobalFuncs();

			//global variables and global function names have to be re-pointed to something.

			root = rhs.getRoot()->clone();

			param_names = rhs.getParamNames();

		}
		//assignment copy
		ParseTree& operator= (const ParseTree& rhs) {
			if(this == &rhs){
				return *this;
			}

			delete local_vars;
			delete local_funcs;
			local_vars = new Map<String, int>{};
			local_funcs = new Map<String, ParseTree*>{};

			//global_vars = rhs.getGlobalVars();
			//global_funcs = rhs.getGlobalFuncs();

			//root = rhs.getRoot()->clone();
			param_names = rhs.getParamNames();
			
			return *this;
		}

		~ParseTree() {
			destroy();
		}

		//ParseTree now owns n, and all child Nodes.
		void setRoot(Node* n){
			this->root = n;
		}
		Node* getRoot() const {
			return root;
		}

		int execute(){
			if(root != nullptr){
				root->execute(global_vars, local_vars, global_funcs, local_funcs, root);
				//clear return status
				if(! root->isReturning()){
					root->setValue(0);
				}
				root->setReturnStatus(false);
				//clear local variables/functions
				local_vars->clear();
				local_funcs->clear();
				int num = root->value();
				return (num);
			}
			else{
				//clear local variables/functions
				local_vars->clear();
				local_funcs->clear();
				return 0;
			}
		}

		void setParamNames(Vector<String> list) {
			param_names = list;
		}
		Vector<String> getParamNames() const {
			return param_names;
		}
		void passArguments(Vector<Node*> args) {
			if(args.size() != param_names.size()) {
				printf("Expected %i arguments, %i found\n", param_names.size(), args.size());
			}
			for(int i = 0; i<param_names.size(); i++){
				local_vars->put(param_names[i], args[i]->value());
			}

		}

		void setGlobals(Map<String, int>* g_vars, Map<String, ParseTree*>* g_funcs) {
			global_vars = g_vars;
			global_funcs = g_funcs;
		}
		void setGlobalsToLocals() {
			global_vars = local_vars;
			global_funcs = local_funcs;
		}
		void setLocalVars(Map<String, int>* v){
			local_vars = v;
		}
		void setLocalFuncs(Map<String, ParseTree*>* v){
			local_funcs = v;
		}

		Map<String,int>* getLocalVars() const {
			return local_vars;
		}
		Map<String, ParseTree*>* getLocalFuncs() const {
			return local_funcs;
		}
		Map<String,int>* getGlobalVars() const {
			return global_vars;
		}
		Map<String, ParseTree*>* getGlobalFuncs() const {
			return global_funcs;
		}


		//ParseTree now owns n, and all child Nodes.
		void init(Node* n){
			root = n;
		}
		void destroy(){
			delete root;
			delete local_vars;
			delete local_funcs;
		}


	};

}

#endif