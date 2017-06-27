#ifndef EE312Project10_OperatorMinusNode_h
#define EE312Project10_OperatorMinusNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorMinusNode : public BinaryOperatorNode {
	private:

	public:
		OperatorMinusNode() :
		BinaryOperatorNode{} {
		}
		OperatorMinusNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorMinusNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 - arg2) ;
		}
		//init(){}
		//OperatorMinusNode should never be copied
		//copy(){}
	};

}


#endif