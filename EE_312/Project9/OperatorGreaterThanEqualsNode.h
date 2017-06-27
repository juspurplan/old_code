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

		~OperatorGreaterThanEqualsNode(){
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