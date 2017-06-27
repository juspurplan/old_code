#ifndef EE312Project10_OperatorGreaterThanNode_h
#define EE312Project10_OperatorGreaterThanNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorGreaterThanNode : public BinaryOperatorNode {
	private:

	public:
		OperatorGreaterThanNode() :
		BinaryOperatorNode{} {
		}
		OperatorGreaterThanNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		//copy constructor
		OperatorGreaterThanNode(const OperatorGreaterThanNode& rhs) : 
		BinaryOperatorNode{rhs} {
		}

		//assignment copy
		//override.
		Node& operator= (const Node& rhs) {
			//do BaseClass's assignment copy
			BinaryOperatorNode::operator= (rhs);

			//do subclass assignment copy
			//nothing
			return *this;
		}

		~OperatorGreaterThanNode(){
		}

		Node* clone() const {
			return new OperatorGreaterThanNode{*this};
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 > arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorGreaterThanNode should never be copied
		//copy(){}
	};

}


#endif