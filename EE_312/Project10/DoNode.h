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

		//copy constructor
		DoNode(const DoNode& rhs ) :
		Node{rhs} {
			conditional = rhs.getConditionalNode()->clone();
			body = rhs.getBodyNode()->clone();
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const DoNode& rhs_subclass = dynamic_cast<const DoNode&>(rhs);
			delete conditional;
			delete body;
			//note: rhs's condition, body should not be nullptr..
			conditional = rhs_subclass.getConditionalNode()->clone();
			body = rhs_subclass.getBodyNode()->clone();

			return *this;
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

		Node* getConditionalNode() const {
			return conditional;
		}
		Node* getBodyNode() const {
			return body;
		}

		
		//ovverride
		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//call execute on conditional
			//conditionals should not have return expressions in them (although it's sort legal syntatically)
			conditional->execute(global_vars, local_vars, global_funcs, local_funcs, root);

			//fetch condition result
			int condition_value = conditional->value();
			bool need_to_return = false;

			//loop by calling execute on body repeatedly
			while(condition_value != 0) {
				if(body != nullptr){
					body->execute(global_vars, local_vars, global_funcs, local_funcs, root);
					//check return status of looping body
					if(body->isReturning()){
						body->setReturnStatus(false);
						this->setReturnStatus(true);
						need_to_return = true;
						break;
					}
				}


				//re-evaluate conditional
				conditional->execute(global_vars, local_vars, global_funcs, local_funcs, root);
				condition_value = conditional->value();
			}

			if(need_to_return){
				return;
			}


			//debug(global_vars, local_vars, global_funcs, local_funcs);
			//printf("[LOOP]");

			//execute next_instruction,  if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs, root);

				//check return status of stuff after loop
				if(next_node->isReturning()){
					next_node->setReturnStatus(false);
					this->setReturnStatus(true);
					return;
				}

			}
			

		}

		//override
		Node* clone() const {
			return new DoNode{*this};
		}


	private:
		
		//init(){}
		//DoNode should never be copied
		//copy(){}
	};

}


#endif