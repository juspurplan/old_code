#ifndef EE312Project10_OperatorGreaterThanEqualsNode_h
#define EE312Project10_OperatorGreaterThanEqualsNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorGreaterThanEqualsNode : public BinaryOperatorNode {
	private:

	public:
		OperatorGreaterThanEqualsNode() :
		BinaryOperatorNode{} {
		}
		OperatorGreaterThanEqualsNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		//copy constructor
		OperatorGreaterThanEqualsNode(const OperatorGreaterThanEqualsNode& rhs) :
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

		~OperatorGreaterThanEqualsNode(){
		}

		Node* clone() const {
			return new OperatorGreaterThanEqualsNode{*this};
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 >= arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorGreaterThanEqualsNode should never be copied
		//copy(){}
	};

}


#endif