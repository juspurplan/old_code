#ifndef EE312Project10_IfNode_h
#define EE312Project10_IfNode_h

#include "Node.h"

namespace EE312Project10 {

	class IfNode : public Node {
	private:
		Node* conditional;
		Node* if_body;
		Node* else_body;

	public:
		IfNode() :
		Node{} {
			conditional = nullptr;
			if_body = nullptr;
			else_body = nullptr;
		}
		IfNode(Node* expr1, Node* expr2) :
		Node{}	{
			conditional = expr1;
			if_body = expr2;
			else_body = nullptr;
		}
		IfNode(Node* expr1, Node* expr2, Node* expr3) :
		Node{} {
			conditional = expr1;
			if_body = expr2;
			else_body = expr3;
		}

		~IfNode(){
			delete conditional;
			delete if_body;
			delete else_body;
		}

		void setConditionalNode(Node* n) {
			conditional = n;
		}
		void setIfBodyNode(Node* n) {
			if_body = n;
		}
		void setElseBodyNode(Node* n){
			else_body = n;
		}

		

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//call execute on conditional
			conditional->execute(global_vars, local_vars, global_funcs, local_funcs);

			//fetch condition result
			int condition_value = conditional->value();

			//check condition and execute a branch
			if(condition_value != 0) {
				if(if_body != nullptr){
					if_body->execute(global_vars, local_vars, global_funcs, local_funcs);
				}
			}
			else if (else_body != nullptr) {
				else_body->execute(global_vars, local_vars, global_funcs, local_funcs);
			}

			//execute next_instruction,  if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs);
			}
			

		}


	private:
		
		//init(){}
		//IfNode should never be copied
		//copy(){}
	};

}


#endif