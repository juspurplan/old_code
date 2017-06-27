#ifndef EE312Project10_OperatorLessThanEqualsNode_h
#define EE312Project10_OperatorLessThanEqualsNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorLessThanEqualsNode : public BinaryOperatorNode {
	private:

	public:
		OperatorLessThanEqualsNode() :
		BinaryOperatorNode{} {
		}
		OperatorLessThanEqualsNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		//copy constructor
		OperatorLessThanEqualsNode(const OperatorLessThanEqualsNode& rhs) :
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

		~OperatorLessThanEqualsNode(){
		}

		Node* clone() const {
			return new OperatorLessThanEqualsNode{*this};
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 <= arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorLessThanEqualsNode should never be copied
		//copy(){}
	};

}


#endif