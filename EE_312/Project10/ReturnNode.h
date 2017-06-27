#ifndef EE312Project10_ReturnNode_h
#define EE312Project10_ReturnNode_h

#include "Node.h"


namespace EE312Project10 {

	class ReturnNode : public Node {
	private:
		Node* func_root;		//should not own this node.. breaks tree hierarchy since it points back to the root
		Node* return_expr;

	public:
		ReturnNode() :
		Node{} {
			func_root = nullptr;
			return_expr = nullptr;
		}
		ReturnNode(Node* func_root, Node* expr) :
		Node{}	{
			this->func_root = func_root;
			return_expr = expr;
		}

		//copy constructor
		ReturnNode(const ReturnNode& rhs) :
		Node{rhs} {
			return_expr = rhs.getReturnExpression()->clone();
			func_root = nullptr;
			//Warning: since funcroot by nature breaks the tree hierarchy (AKA points back to the root),
			//when ReturnNodes are copied, you have to set the func_root yourself manually again.
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const ReturnNode& rhs_subclass = dynamic_cast<const ReturnNode&>(rhs);
			delete return_expr;
			return_expr = rhs_subclass.getReturnExpression()->clone();

			return *this;
		}

		~ReturnNode(){
			delete return_expr;
		}

		void setFunctionRootNode(Node * n) {
			func_root = n;
		}
		void setReturnExpression(Node* n){
			return_expr = n;
		}
		Node* getReturnExpression() const {
			return return_expr;
		}

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//calculate return expression
			return_expr->execute(global_vars, local_vars, global_funcs, local_funcs, root);
			int return_value = return_expr->value();

			//debug(global_vars, local_vars, global_funcs, local_funcs);
			//printf("[RETURN] : %i\n", return_value);

			//set function root node's value as the return value
			//func_root->setValue(return_value);
			root->setValue(return_value);
			//printf("return: %i\n", return_value);

			//Turn on return status
			setReturnStatus(true);
			return;

		}

		Node* clone() const {
			return new ReturnNode{*this};
		}



	};


}



#endif