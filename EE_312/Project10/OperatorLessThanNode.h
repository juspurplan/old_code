#ifndef EE312Project10_OperatorLessThanNode_h
#define EE312Project10_OperatorLessThanNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorLessThanNode : public BinaryOperatorNode {
	private:

	public:
		OperatorLessThanNode() :
		BinaryOperatorNode{} {
		}
		OperatorLessThanNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		//coipy constructor
		OperatorLessThanNode(const OperatorLessThanNode& rhs) :
		BinaryOperatorNode{rhs} {
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			BinaryOperatorNode::operator= (rhs);

			//do subclass assignment copy
			//nothing
			return *this;
		}

		~OperatorLessThanNode(){
		}

		Node* clone() const {
			return new OperatorLessThanNode{*this};
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 < arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorLessThanNode should never be copied
		//copy(){}
	};

}


#endif