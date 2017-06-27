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

		//copy constructor
		OperatorPlusNode(const OperatorPlusNode& rhs) :
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

		~OperatorPlusNode(){
		}

		//override
		Node* clone() const {
			return new OperatorPlusNode{*this};
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