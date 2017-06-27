#ifndef EE312Project10_OperatorEqualsNode_h
#define EE312Project10_OperatorEqualsNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorEqualsNode : public BinaryOperatorNode {
	private:

	public:
		OperatorEqualsNode() :
		BinaryOperatorNode{} {
		}
		OperatorEqualsNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorEqualsNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 == arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorEqualsNode should never be copied
		//copy(){}
	};

}


#endif