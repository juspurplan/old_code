#ifndef EE312Project10_OperatorGreaterThanNode_h
#define EE312Project10_OperatorGreaterThanNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorGreaterThanNode : public BinaryOperatorNode {
	private:

	public:
		OperatorGreaterThanNode() :
		BinaryOperatorNode{} {
		}
		OperatorGreaterThanNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorGreaterThanNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 > arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorGreaterThanNode should never be copied
		//copy(){}
	};

}


#endif