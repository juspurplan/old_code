#ifndef EE312Project10_OperatorMinusNode_h
#define EE312Project10_OperatorMinusNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorMinusNode : public BinaryOperatorNode {
	private:

	public:
		OperatorMinusNode() :
		BinaryOperatorNode{} {
		}
		OperatorMinusNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		//copy constructor
		OperatorMinusNode(const OperatorMinusNode& rhs) :
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

		~OperatorMinusNode(){
		}

		Node* clone() const {
			return new OperatorMinusNode{*this};
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 - arg2) ;
		}
		//init(){}
		//OperatorMinusNode should never be copied
		//copy(){}
	};

}


#endif