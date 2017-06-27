#ifndef EE312Project10_OperatorDivideNode_h
#define EE312Project10_OperatorDivideNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorDivideNode : public BinaryOperatorNode {
	private:

	public:
		OperatorDivideNode() :
		BinaryOperatorNode{} {
		}
		OperatorDivideNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorDivideNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 / arg2) ;
		}
		//init(){}
		//OperatorDivideNode should never be copied
		//copy(){}
	};

}


#endif