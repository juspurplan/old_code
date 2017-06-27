#ifndef EE312Project10_OperatorModulusNode_h
#define EE312Project10_OperatorModulusNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorModulusNode : public BinaryOperatorNode {
	private:

	public:
		OperatorModulusNode() :
		BinaryOperatorNode{} {
		}
		OperatorModulusNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorModulusNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 % arg2) ;
		}
		//init(){}
		//OperatorModulusNode should never be copied
		//copy(){}
	};

}


#endif