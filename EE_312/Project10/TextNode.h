#ifndef EE312Project10_TextNode_h
#define EE312Project10_TextNode_h

#include "Node.h"

namespace EE312Project10 {

	class TextNode : public Node {
	private:
		Node* str_arg;

	public:
		TextNode() :
		Node{} {
			str_arg = nullptr;
		}
		TextNode(Node* str) :
		Node{}	{
			str_arg = str;
		}

		//copy constructor
		TextNode(const TextNode& rhs) :
		Node{rhs} {
			str_arg = rhs.getStringNode()->clone();
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			Node::operator= (rhs);

			//do subclass assignment copy
			const TextNode& rhs_subclass = dynamic_cast<const TextNode&>(rhs);
			delete str_arg;
			str_arg = rhs_subclass.getStringNode()->clone();

			return *this;
		}

		~TextNode(){
			delete str_arg;
		}

		void setStringNode(Node* n) {
			str_arg = n;
		}
		Node* getStringNode() const {
			return str_arg;
		}

		void execute(Map<String,int>* global_vars, Map<String,int>* local_vars, Map<String, ParseTree*>* global_funcs, Map<String, ParseTree*>* local_funcs, Node* root){
			//call execute on str_arg
			//guaranteed leaf node
			str_arg->execute(global_vars, local_vars, global_funcs, local_funcs, root);

			//fetch data from str_arg
			String str = str_arg->getString();
			
			//output to screen
			printf("%s", str.c_str());



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
			return new TextNode{*this};
		}


	private:
		//init(){}
		//TextNode should never be copied
		//copy(){}
	};

}


#endif