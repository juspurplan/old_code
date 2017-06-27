#ifndef EE312Project10_OperatorNotNode_h
#define EE312Project10_OperatorNotNode_h

#include "UnaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorNotNode : public UnaryOperatorNode {
	private:

	public:
		OperatorNotNode() :
		UnaryOperatorNode{} {
		}
		OperatorNotNode(Node* expr1) :
		UnaryOperatorNode{expr1}	{
		}

		~OperatorNotNode(){
		}

	private:
		int unaryOperate(int arg1){
			return (arg1 == 0) ? (1) : (0);
		}
		//init(){}
		//OperatorNotNode should never be copied
		//copy(){}
	};

}


#endif