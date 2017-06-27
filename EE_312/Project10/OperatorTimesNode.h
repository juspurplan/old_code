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

		//copy constructor
		OperatorTimesNode(const OperatorTimesNode& rhs) :
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

		~OperatorTimesNode(){
		}

		Node* clone() const {
			return new OperatorTimesNode{*this};
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