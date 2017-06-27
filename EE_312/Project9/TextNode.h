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

		~TextNode(){
			delete str_arg;
		}

		void setStringNode(Node* n) {
			str_arg = n;
		}

		void execute(Map<String,int>& global_vars, Map<String,int>& local_vars, Map<String, ParseTree*>& global_funcs, Map<String, ParseTree*>& local_funcs){
			//call execute on str_arg
			str_arg->execute(global_vars, local_vars, global_funcs, local_funcs);

			//fetch data from str_arg
			String str = str_arg->getString();
			
			//output to screen
			printf("%s", str.c_str());


			//execute next_instruction, if it exists.
			if(! (next_node == nullptr)) {
				next_node->execute(global_vars, local_vars, global_funcs, local_funcs);
			}

		}


	private:
		//init(){}
		//TextNode should never be copied
		//copy(){}
	};

}


#endif