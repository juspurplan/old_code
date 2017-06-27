#ifndef EE312Project10_OperatorTildeNode_h
#define EE312Project10_OperatorTildeNode_h

#include "UnaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorTildeNode : public UnaryOperatorNode {
	private:

	public:
		OperatorTildeNode() :
		UnaryOperatorNode{} {
		}
		OperatorTildeNode(Node* expr1) :
		UnaryOperatorNode{expr1}	{
		}

		//copy constructor
		OperatorTildeNode(const OperatorTildeNode& rhs) :
		UnaryOperatorNode{rhs} {
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			UnaryOperatorNode::operator= (rhs);

			//do subclass assignment copy
			//nothing
			return *this;
		}

		~OperatorTildeNode(){
		}

		Node* clone() const {
			return new OperatorTildeNode{*this};
		}

	private:
		int unaryOperate(int arg1){
			return (-1 * arg1) ;
		}
		//init(){}
		//OperatorTildeNode should never be copied
		//copy(){}
	};

}


#endif