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

		//copy constructor
		IfNode(const IfNode& rhs) :
		Node{rhs} {
			conditional = rhs.getConditionalNode()->clone();
			if_body = rhs.getConditionalNode()->clone();
			else_body = nullptr;
			if(rhs.getElseBodyNode() != nullptr){
				else_body = rhs.getElseBodyNode()->clone();
			}
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const IfNode& rhs_subclass = dynamic_cast<const IfNode&>(rhs);
			delete conditional;
			delete if_body;
			delete else_body;
			//note: rhs's condition, if_body should not be nullptr..
			//else_body might be nullptr
			conditional = rhs_subclass.getConditionalNode()->clone();
			if_body = rhs_subclass.getIfBodyNode()->clone();
			else_body = nullptr;
			if(rhs_subclass.getElseBodyNode() != nullptr) {
				else_body = rhs_subclass.getElseBodyNode()->clone();
			}
			
			return *this;
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
		Node* getConditionalNode() const {
			return conditional;
		}
		Node* getIfBodyNode() const {
			return if_body;
		}
		Node* getElseBodyNode() const {
			return else_body;
		}

		

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//call execute on conditional
			//conditional should never hold return statements even though
			//it might be syntatically legal
			conditional->execute(global_vars, local_vars, global_funcs, local_funcs, root);

			//fetch condition result
			int condition_value = conditional->value();
			bool need_to_return = false;

			//check condition and execute a branch
			if(condition_value != 0) {
				if(if_body != nullptr){
					if_body->execute(global_vars, local_vars, global_funcs, local_funcs, root);
					if(if_body->isReturning()){
						if_body->setReturnStatus(false);
						this->setReturnStatus(true);
						need_to_return = true;
					}
				}
			}
			else if (else_body != nullptr) {
				else_body->execute(global_vars, local_vars, global_funcs, local_funcs, root);
				if(else_body->isReturning()){
					else_body->setReturnStatus(false);
					this->setReturnStatus(true);
					need_to_return = true;
				}
			}

			if(need_to_return){
				return;
			}

			//debug(global_vars, local_vars, global_funcs, local_funcs);
			//printf("[IF]");



			//execute next_instruction,  if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs, root);

				//check for return
				if(next_node->isReturning()){
					next_node->setReturnStatus(false);
					this->setReturnStatus(true);
					return;
				}
			}
			

		}

		//override
		Node* clone() const {
			return new IfNode{*this};
		}

	private:
		
		//init(){}
		//IfNode should never be copied
		//copy(){}
	};

}


#endif