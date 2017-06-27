#ifndef EE312Project10_OperatorOrNode_h
#define EE312Project10_OperatorOrNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorOrNode : public BinaryOperatorNode {
	private:

	public:
		OperatorOrNode() :
		BinaryOperatorNode{} {
		}
		OperatorOrNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorOrNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			if(arg1 != 0  || arg2 != 0) {
				return 1;
			}
			else {
				return 0;
			}
		}
		//init(){}
		//OperatorOrNode should never be copied
		//copy(){}
	};

}


#endif