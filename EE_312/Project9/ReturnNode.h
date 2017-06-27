#ifndef EE312Project10_ReturnNode_h
#define EE312Project10_ReturnNode_h

#include "Node.h"


namespace EE312Project10 {

	class ReturnNode : public Node {
	private:
		Node* func_root;
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

		~CallNode(){
			delete func_root;
			delete return_expr;
		}

		void setFunctionRootNode(Node * n) {
			func_root = n;
		}
		void setReturnExpression(Node* n){
			return_expr = n;
		}

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//calculate return expression
			return_expr->execute(global_vars, local_vars, global_funcs, local_funcs);
			int return_value = return_expr->value();

			//set function root node's value as the return value
			func_root->setValue(return_value);

		}



	};


}



#endif