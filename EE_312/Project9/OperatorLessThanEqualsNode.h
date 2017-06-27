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

		~OperatorLessThanEqualsNode(){
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