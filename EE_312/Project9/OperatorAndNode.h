#ifndef EE312Project10_OperatorAndNode_h
#define EE312Project10_OperatorAndNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorAndNode : public BinaryOperatorNode {
	private:

	public:
		OperatorAndNode() :
		BinaryOperatorNode{} {
		}
		OperatorAndNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorAndNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			if(arg1 != 0 && arg2 != 0) {
				return 1;
			}
			else{
				return 0;
			}
		}
		//init(){}
		//OperatorAndNode should never be copied
		//copy(){}
	};

}


#endif