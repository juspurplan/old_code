#ifndef EE312Project10_OperatorTildeNode_h
#define EE312Project10_OperatorTildeNode_h

#include "UnaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorTildeNode : public UnaryOperatorNode {
	private:

	public:
		OperatorTildeNode() :
		UnaryOperatorNode{} {
		}
		OperatorTildeNode(Node* expr1) :
		UnaryOperatorNode{expr1}	{
		}

		~OperatorTildeNode(){
		}

	private:
		int unaryOperate(int arg1){
			return (-1 * arg1) ;
		}
		//init(){}
		//OperatorTildeNode should never be copied
		//copy(){}
	};

}


#endif