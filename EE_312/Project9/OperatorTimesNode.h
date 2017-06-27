#ifndef EE312Project10_OperatorTimesNode_h
#define EE312Project10_OperatorTimesNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorTimesNode : public BinaryOperatorNode {
	private:

	public:
		OperatorTimesNode() :
		BinaryOperatorNode{} {
		}
		OperatorTimesNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		~OperatorTimesNode(){
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 * arg2) ;
		}
		//init(){}
		//OperatorTimesNode should never be copied
		//copy(){}
	};

}


#endif