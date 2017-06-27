#ifndef EE312Project10_SetNode_h
#define EE312Project10_SetNode_h

#include "Node.h"

namespace EE312Project10 {

	class SetNode : public Node {
	private:
		Node* str_arg;
		Node* value_arg;

	public:
		SetNode() :
		Node{} {
			str_arg = nullptr;
			value_arg = nullptr;
		}
		SetNode(Node* var, Node* expr) :
		Node{}	{
			str_arg = var;
			value_arg = expr;
		}

		//copy constructor
		SetNode(const SetNode& rhs) :
		Node{rhs} {
			str_arg = rhs.getVarStringNode()->clone();
			value_arg = rhs.getExprNode()->clone();
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const SetNode& rhs_subclass = dynamic_cast<const SetNode&>(rhs);
			delete str_arg;
			delete value_arg;
			str_arg = rhs_subclass.getVarStringNode()->clone();
			value_arg = rhs_subclass.getExprNode()->clone();
			
			return *this;
		}

		~SetNode(){
			delete str_arg;
			delete value_arg;
		}

		void setVarStringNode(Node* n) {
			str_arg = n;
		}
		void setExprNode(Node* n) {
			value_arg = n;
		}
		Node* getVarStringNode() const {
			return str_arg;
		}
		Node* getExprNode() const {
			return value_arg;
		}

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//call execute on str_arg, and value_arg
			//these are guaranteed leaf nodes
			str_arg->execute(global_vars, local_vars, global_funcs, local_funcs, root);
			value_arg->execute(global_vars, local_vars, global_funcs, local_funcs, root);

			//fetch data from str_arg, value_arg
			String str = str_arg->getString();
			int value = value_arg->value();
			
			//tries to put (str, value) pair in local vars.
			if( !local_vars->containsKey(str)){
				printf("variable %s not declared\n", str.c_str());
			}
			local_vars->put(str, value);


			
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

		Node* clone() const {
			return new SetNode{*this};
		}


	private:
		//init(){}
		//SetNode should never be copied
		//copy(){}
	};

}


#endif