#ifndef EE312Project10_OperatorEqualsNode_h
#define EE312Project10_OperatorEqualsNode_h

#include "BinaryOperatorNode.h"

namespace EE312Project10 {

	class OperatorEqualsNode : public BinaryOperatorNode {
	private:

	public:
		OperatorEqualsNode() :
		BinaryOperatorNode{} {
		}
		OperatorEqualsNode(Node* expr1, Node* expr2) :
		BinaryOperatorNode{expr1, expr2}	{
		}

		//copy constructor
		OperatorEqualsNode(const OperatorEqualsNode& rhs) :
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

		~OperatorEqualsNode(){
		}

		//override
		Node* clone() const {
			return new OperatorEqualsNode{*this};
		}

	private:
		int binaryOperate(int arg1, int arg2){
			return (arg1 == arg2) ? (1) : (0) ;
		}
		//init(){}
		//OperatorEqualsNode should never be copied
		//copy(){}
	};

}


#endif