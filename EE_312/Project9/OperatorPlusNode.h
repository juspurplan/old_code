#ifndef EE312Project10_OperatorPlusNode_h
#define EE312Project10_OperatorPlusNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorPlusNode : public BinaryOperatorNode {
	private:

	public:
		OperatorPlusNode() :
		BinaryOperatorNode{} {
		}
		OperatorPlusNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorPlusNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 + arg2) ;
		}
		//init(){}
		//OperatorPlusNode should never be copied
		//copy(){}
	};

}


#endif