#ifndef EE312Project10_DoNode_h
#define EE312Project10_DoNode_h

#include "Node.h"

namespace EE312Project10 {

	class DoNode : public Node {
	private:
		Node* conditional;
		Node* body;

	public:
		DoNode() :
		Node{} {
			conditional = nullptr;
			body = nullptr;
		}
		DoNode(Node* expr1, Node* expr2) :
		Node{}	{
			conditional = expr1;
			body = expr2;
		}

		~DoNode(){
			delete conditional;
			delete body;
		}

		void setConditionalNode(Node* n) {
			conditional = n;
		}
		void setBodyNode(Node* n) {
			body = n;
		}

		

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//call execute on conditional
			conditional->execute(global_vars, local_vars, global_funcs, local_funcs);

			//fetch condition result
			int condition_value = conditional->value();

			//loop by calling execute on body repeatedly
			while(condition_value != 0) {
				if(body != nullptr){
					body->execute(global_vars, local_vars, global_funcs, local_funcs);
				}

				//re-evaluate conditional
				conditional->execute(global_vars, local_vars, global_funcs, local_funcs);
				condition_value = conditional->value();
			}


			//execute next_instruction,  if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs);
			}
			

		}


	private:
		
		//init(){}
		//DoNode should never be copied
		//copy(){}
	};

}


#endif