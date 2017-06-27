#ifndef EE312Project10_DefunNode_h
#define EE312Project10_DefunNode_h

#include "Node.h"
#include "Vector.h"

namespace EE312Project10 {

	class DefunNode : public Node {
	private:
		Node* func_name;
		ParseTree* function;

	public:
		DefunNode() :
		Node{} {
			func_name = nullptr;
			function = nullptr;
		}
		DefunNode(Node* name, ParseTree* func) :
		Node{}	{
			func_name = name;
			function = func;
		}

		//copy constructor
		DefunNode(const DefunNode& rhs) : 
		Node{rhs} {
			func_name = rhs.getFunctionNameNode()->clone();
			function = new ParseTree{*rhs.getFunction()};
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const DefunNode& rhs_subclass = dynamic_cast<const DefunNode&>(rhs);
			func_name = rhs_subclass.getFunctionNameNode()->clone();
			function = new ParseTree{*(rhs_subclass.getFunction())};

			return *this;
		}

		~DefunNode(){
			delete func_name;
			delete function;
		}

		void setFunctionNameNode(Node* n) {
			func_name = n;
		}
		void setFunction(ParseTree* func) {
			function = func;
		}
		Node* getFunctionNameNode() const {
			return func_name;
		}
		ParseTree* getFunction() const {
			return function;
		}

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			
			///guaranteed to be a leaf node
			func_name->execute(global_vars, local_vars, global_funcs, local_funcs, root);
			String name = func_name->getString();
			local_funcs->put(name, function);

			//debug(global_vars, local_vars, global_funcs, local_funcs);
			//printf("[DEFUN]");			

			//execute next_instruction,  if it exists.
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
			return new DefunNode{*this};
		}


	private:
		

	};

}


#endif