#ifndef EE312Project10_SymbolNode_h
#define EE312Project10_SymbolNode_h

#include "Node.h"

namespace EE312Project10 {

	class SymbolNode : public Node {
	private:

	public:
		SymbolNode() :
		Node{} {
		}
		SymbolNode(String name) :
		Node{0, name}	{
		}

		~SymbolNode(){
		}


		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){

			String var_name = getString();

			//check local memory
			if(local_vars.containsKey(var_name)){
				setValue(local_vars.get(var_name));
				return;
			}
			

			//check global memory
			if(global_vars.containsKey(var_name)) {
				setValue(global_vars.get(var_name));
				return;
			}

			//did not find variable name
			printf("variable %s not found (defaulted to 0)\n", var_name.c_str());
			

		}


	private:
		
		//init(){}
		//SymbolNode should never be copied
		//copy(){}
	};

}


#endif