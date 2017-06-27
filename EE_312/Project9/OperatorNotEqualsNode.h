#ifndef EE312Project10_OperatorNotEqualsNode_h
#define EE312Project10_OperatorNotEqualsNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorNotEqualsNode : public BinaryOperatorNode {
	private:

	public:
		OperatorNotEqualsNode() :
		BinaryOperatorNode{} {
		}
		OperatorNotEqualsNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorNotEqualsNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 != arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorNotEqualsNode should never be copied
		//copy(){}
	};

}


#endif