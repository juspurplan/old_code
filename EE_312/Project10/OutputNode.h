#ifndef EE312Project10_OutputNode_h
#define EE312Project10_OutputNode_h

#include "Node.h"

namespace EE312Project10 {

	class OutputNode : public Node {
	private:
		Node* value_arg;

	public:
		OutputNode() :
		Node{} {
			value_arg = nullptr;
		}
		OutputNode(Node* expr) :
		Node{}	{
			value_arg = expr;
		}

		//copy constructor
		OutputNode(const OutputNode& rhs) :
		Node{rhs} {
			value_arg = rhs.getExprNode()->clone();
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const OutputNode& rhs_subclass = dynamic_cast<const OutputNode&>(rhs);
			delete value_arg;
			value_arg = rhs_subclass.getExprNode()->clone();
			
			return *this;
		}

		~OutputNode(){
			delete value_arg;
		}

		void setExprNode(Node* n) {
			value_arg = n;
		}
		Node* getExprNode() const {
			return value_arg;
		}

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//call execute on value_arg
			//this is a guaranteed leaf node
			value_arg->execute(global_vars, local_vars, global_funcs, local_funcs, root);

			//fetch data from value_arg
			int value = value_arg->value();
			
			//output to screen
			printf("%i", value);

			
			//execute next_instruction, if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs, root);

				//check return status
				if(next_node->isReturning()){
					next_node->setReturnStatus(false);
					this->setReturnStatus(true);
					return;
				}
			}
		}

		//override 
		Node* clone() const {
			return new OutputNode{*this};
		}


	private:
		//init(){}
		//OutputNode should never be copied
		//copy(){}
	};

}


#endif