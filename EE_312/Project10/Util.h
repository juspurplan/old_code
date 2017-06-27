#ifndef EE312Project10_Util_h
#define EE312Project10_Util_h

#include "Parse.h"
#include "String.h"

//including Nodes
#include "Node.h"
#include "SymbolNode.h"

#include "BinaryOperatorNode.h"
#include "OperatorPlusNode.h"
#include "OperatorMinusNode.h"
#include "OperatorTimesNode.h"
#include "OperatorDivideNode.h"
#include "OperatorModulusNode.h"
#include "OperatorAndNode.h"
#include "OperatorOrNode.h"
#include "OperatorGreaterThanNode.h"
#include "OperatorGreaterThanEqualsNode.h"
#include "OperatorLessThanNode.h"
#include "OperatorLessThanEqualsNode.h"
#include "OperatorEqualsNode.h"
#include "OperatorNotEqualsNode.h"

#include "UnaryOperatorNode.h"
#include "OperatorTildeNode.h"
#include "OperatorNotNode.h"


#include "VarNode.h"
#include "SetNode.h"
#include "OutputNode.h"
#include "TextNode.h"

//part B
#include "DoNode.h"
#include "IfNode.h"
#include "DefunNode.h"
#include "CallNode.h"
#include "ReturnNode.h"

namespace EE312Project10 {

	const bool VERBOSE = false;

	ParseTree& buildParseTree();
	void peekTest();

	void parseComment();
	
	Node* parseVar();
	Node* parseSet();
	Node* parseOutput();
	Node* parseText();

	Node* parseDo();
	Node* parseIf();
	
	Node* parseDefun();
	Node* parseCall();
	Node* parseReturn();

	Vector<String> parseParams();
	Vector<Node*> parseArgs();

	Node* parseExpr();
	BinaryOperatorNode* createBinaryOperatorNode(String op);
	UnaryOperatorNode* createUnaryOperatorNode(String op);


	//passes ownership of returned ParseTree to caller.
	ParseTree& buildParseTree() {
		ParseTree& pt = *(new ParseTree{});
		Node* root = nullptr;
		Node* current = root;

		//note to self:
		//with my edits to Input.cpp
		//peeking, and reading appear to be working properly with my design.

		while(true) {
			
			const char* token = peek_next_token();
			read_next_token();
			TokenType tt = next_token_type;

			//check what tokens we're trying to parse
			if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
			}

			if(tt == END){
				break;
			}

			switch(tt){
			case NUMBER:{
				break;
			}
			case SYMBOL: {
				if(String{token} == String{"//"}){
					parseComment();
				}
				break;
			}
			case NAME: {
				Node* next_node = nullptr;
				//give command, parse command.
				if(String{token} == String{"var"}){
					next_node = parseVar();
				} 
				else if(String{token} == String{"set"}){
					next_node = parseSet();
				} 
				else if(String{token} == String{"output"}){
					next_node = parseOutput();
				} 
				else if(String{token} == String{"text"}){
					next_node = parseText();
				} 
				else if(String{token} == String{"do"}){
					next_node = parseDo();
				} 
				else if(String{token} == String{"if"}){
					next_node = parseIf();
				} 
				else if(String{token} == String{"defun"}){
					next_node = parseDefun();
				} 
				else if(String{token} == String{"call"}){
					next_node = parseCall();
				} 
				else if(String{token} == String{"return"}){
					next_node = parseReturn();
				} 

				//add next_node to tree
				if(root == nullptr) {
					root = next_node;
					current = next_node;
				}
				else {
					current->setNextNode(next_node);
					current = next_node;
				}
				break;
			}
			default:{
				printf("Build Tree error. Unexpected token type. Token type = %i\n", tt);
				break;
			}
			case KEYWORD:
				break;
			case STRING:
				break;
			case INVALID:
				break;
			case END:
				break;
			}

		}

		pt.setRoot(root);
		return pt;
	}



	void parseComment() {
		while(true){
			const char* c_peek = peek_next_token();
			String peek = String{c_peek};

			if(peek == String{"\n"}){
				read_next_token();
				break;
			}
			read_next_token();
		}
	}

	BinaryOperatorNode* createBinaryOperatorNode(String op){
		if(op == String{"+"}){
			return new OperatorPlusNode{};
		}
		else if(op == String{"-"}){
			return new OperatorMinusNode{};
		}
		else if(op == String{"*"}){
			return new OperatorTimesNode{};
		}
		else if(op == String{"/"}){
			return new OperatorDivideNode{};
		}
		else if(op == String{"%"}){
			return new OperatorModulusNode{};
		}
		else if(op == String{"&&"}){
			return new OperatorAndNode{};
		}
		else if(op == String{"||"}){
			return new OperatorOrNode{};
		}
		else if(op == String{">"}){
			return new OperatorGreaterThanNode{};
		}
		else if(op == String{">="}){
			return new OperatorGreaterThanEqualsNode{};
		}
		else if(op == String{"<"}){
			return new OperatorLessThanNode{};
		}
		else if(op == String{"<="}){
			return new OperatorLessThanEqualsNode{};
		}
		else if(op == String{"=="}){
			return new OperatorEqualsNode{};
		}
		else if(op == String{"!="}){
			return new OperatorNotEqualsNode{};
		}
		else {
			return nullptr;
		}
	}
	UnaryOperatorNode* createUnaryOperatorNode(String op){
		if(op == String{"~"}){
			return new OperatorTildeNode{};
		}
		else if(op == String{"!"}){
			return new OperatorNotNode{};
		}
		else {
			return nullptr;
		}
	}

	Node* parseExpr(){
		Node* result = nullptr;
		const char* token = peek_next_token();
		read_next_token();
		TokenType tt = next_token_type;

		if(VERBOSE){
			printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
		}


		switch(tt){
		case NUMBER: {
			result = new Node{token_number_value};
			return result;
			break;
		}
		case SYMBOL: {
			result = createUnaryOperatorNode(String{token});
			if(result == nullptr){
				//we have a binary operator
				result = createBinaryOperatorNode(String{token});
				Node* arg1 = parseExpr();
				Node* arg2 = parseExpr();
				((BinaryOperatorNode*)result)->setArg1Node(arg1);
				((BinaryOperatorNode*)result)->setArg2Node(arg2);
				return result;
			}
			else{
				//we have unary operator
				Node* arg1 = parseExpr();
				((UnaryOperatorNode*)result)->setArgNode(arg1);
				return result;
			}
		}
		case NAME: {
			if(String{token} == String{"call"}) {
				result = parseCall();
			}
			else{
				result = new SymbolNode{String{token}};
			}
			return result;
		}
		case KEYWORD:
			break;
		case STRING:
			break;
		case INVALID:
			break;
		case END:
			break;
		}
	}

	Node* parseVar(){
		Node* result = new VarNode{};

		const char* token = peek_next_token();
		read_next_token();
		TokenType tt = next_token_type;

		if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
		}

		Node* var_name = new Node{0, String{token}};
		((VarNode*)result)->setVarStringNode(var_name);

		Node* expr = parseExpr();
		((VarNode*)result)->setExprNode(expr);


		return result;
	}

	Node* parseSet(){
		Node* result = new SetNode{};

		const char* token = peek_next_token();
		read_next_token();
		TokenType tt = next_token_type;

		if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
		}

		Node* var_name = new Node{0, String{token}};
		((SetNode*)result)->setVarStringNode(var_name);

		Node* expr = parseExpr();
		((SetNode*)result)->setExprNode(expr);

		return result;
	}

	Node* parseOutput(){
		Node* result = new OutputNode{};


		Node* expr = parseExpr();
		((OutputNode*)result)->setExprNode(expr);

		return result;

	}

	Node* parseText(){
		Node* result = new TextNode{};

		const char* token = peek_next_token();
		read_next_token();
		TokenType tt = next_token_type;

		if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
		}

		Node* str = new Node{};
		str->setString(String{token});

		((TextNode*)result)->setStringNode(str);

		return result;
	}


	Node* parseDo(){
		Node* result = new DoNode{};

		Node* conditional = parseExpr();
		((DoNode*)result)->setConditionalNode(conditional);

		Node* body = nullptr;
		Node* current = nullptr;

		//create body node
		//copy pasta-ed from main buildTree function
		//todo: wrap big phat loop in a parseLoopBody() function
		while(true) {
			
			const char* token = peek_next_token();
			read_next_token();
			TokenType tt = next_token_type;

			if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
			}

			if(String{token} == String{"od"}){
				break;
			}

			switch(tt){
			case NUMBER:{
				break;
			}
			case SYMBOL: {
				if(String{token} == String{"//"}){
					parseComment();
				}
				break;
			}
			case NAME: {
				Node* next_node = nullptr;
				//give command, parse command.
				if(String{token} == String{"var"}){
					next_node = parseVar();
				} 
				else if(String{token} == String{"set"}){
					next_node = parseSet();
				} 
				else if(String{token} == String{"output"}){
					next_node = parseOutput();
				} 
				else if(String{token} == String{"text"}){
					next_node = parseText();
				} 
				else if(String{token} == String{"do"}){
					next_node = parseDo();
				} 
				else if(String{token} == String{"if"}){
					next_node = parseIf();
				} 
				else if(String{token} == String{"defun"}){
					next_node = parseDefun();
				} 
				else if(String{token} == String{"call"}){
					next_node = parseCall();
				} 
				else if(String{token} == String{"return"}){
					next_node = parseReturn();
				} 



				//add next_node to tree
				if(body == nullptr) {
					body = next_node;
					current = next_node;
				}
				else {
					current->setNextNode(next_node);
					current = next_node;
				}
				break;
			}
			default:{
				printf("Build Tree error. Unexpected token type. Token type = %i\n", tt);
				break;
			}
			case KEYWORD:
				break;
			case STRING:
				break;
			case INVALID:
				break;
			case END:
				break;
			}

		}
		//

		((DoNode*)result)->setBodyNode(body);
		return result;
	}

	Node* parseIf() {
		Node* result = new IfNode{};
		
		Node* conditional = parseExpr();
		((IfNode*)result)->setConditionalNode(conditional);

		Node* if_body = nullptr;
		bool has_else_body = false;
		Node* else_body = nullptr;

		Node* current = nullptr;

		//create if_body node
		//copy pasta-ed from main buildTree function
		//todo: wrap big phat loop in a parseIfBody() function
		while(true) {
			
			const char* token = peek_next_token();
			read_next_token();
			TokenType tt = next_token_type;

			if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
			}

			if(String{token} == String{"fi"}){
				break;
			}
			if(String{token} == String{"else"}){
				has_else_body = true;
				break;
			}

			switch(tt){
			case NUMBER:{
				break;
			}
			case SYMBOL: {
				if(String{token} == String{"//"}){
					parseComment();
				}
				break;
			}
			case NAME: {
				Node* next_node = nullptr;
				//give command, parse command.
				if(String{token} == String{"var"}){
					next_node = parseVar();
				} 
				else if(String{token} == String{"set"}){
					next_node = parseSet();
				} 
				else if(String{token} == String{"output"}){
					next_node = parseOutput();
				} 
				else if(String{token} == String{"text"}){
					next_node = parseText();
				} 
				else if(String{token} == String{"do"}){
					next_node = parseDo();
				} 
				else if(String{token} == String{"if"}){
					next_node = parseIf();
				} 
				else if(String{token} == String{"defun"}){
					next_node = parseDefun();
				} 
				else if(String{token} == String{"call"}){
					next_node = parseCall();
				} 
				else if(String{token} == String{"return"}){
					next_node = parseReturn();
				} 



				//add next_node to tree
				if(if_body == nullptr) {
					if_body = next_node;
					current = next_node;
				}
				else {
					current->setNextNode(next_node);
					current = next_node;
				}
				break;
			}
			default:{
				printf("Build Tree error. Unexpected token type. Token type = %i\n", tt);
				break;
			}
			case KEYWORD:
				break;
			case STRING:
				break;
			case INVALID:
				break;
			case END:
				break;
			}

		}

		//create if_body node
		//copy pasta-ed from main buildTree function
		//todo: wrap big phat loop in a parseIfBody() function
		if(has_else_body){
			current = nullptr;
			while(true) {
			
				const char* token = peek_next_token();
				read_next_token();
				TokenType tt = next_token_type;

				if(VERBOSE){
					printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
				}

				if(String{token} == String{"fi"}){
					break;
				}

				switch(tt){
				case NUMBER:{
					break;
				}
				case SYMBOL: {
					if(String{token} == String{"//"}){
						parseComment();
					}
					break;
				}
				case NAME: {
					Node* next_node = nullptr;
					//give command, parse command.
					if(String{token} == String{"var"}){
						next_node = parseVar();
					} 
					else if(String{token} == String{"set"}){
						next_node = parseSet();
					} 
					else if(String{token} == String{"output"}){
						next_node = parseOutput();
					} 
					else if(String{token} == String{"text"}){
						next_node = parseText();
					} 
					else if(String{token} == String{"do"}){
						next_node = parseDo();
					} 
					else if(String{token} == String{"if"}){
						next_node = parseIf();
					} 
					else if(String{token} == String{"defun"}){
						next_node = parseDefun();
					} 
					else if(String{token} == String{"call"}){
						next_node = parseCall();
					} 
					else if(String{token} == String{"return"}){
						next_node = parseReturn();
					} 


					//add next_node to tree
					if(else_body == nullptr) {
						else_body = next_node;
						current = next_node;
					}
					else {
						current->setNextNode(next_node);
						current = next_node;
					}
					break;
				}
				default:{
					printf("Build Tree error. Unexpected token type. Token type = %i\n", tt);
					break;
				}
				case KEYWORD:
					break;
				case STRING:
					break;
				case INVALID:
					break;
				case END:
					break;
				}

			}

		}



		((IfNode*)result)->setIfBodyNode(if_body);
		((IfNode*)result)->setElseBodyNode(else_body);
		return result;

	}

	Node* parseDefun(){	

		Node* function = new DefunNode{};

		const char* token = peek_next_token();
		TokenType tt = next_token_type;
		read_next_token();

		if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
		}

		Node* func_name = new Node{0, String{token}};

		((DefunNode*)function) -> setFunctionNameNode(func_name);

		ParseTree& f_pt = *(new ParseTree{});

		//parse param names
		f_pt.setParamNames(parseParams());

		//giant copy-pasta from buildTree function
		Node* root = nullptr;
		Node* current = root;

		while(true) {
			
			const char* token = peek_next_token();
			TokenType tt = next_token_type;
			
			if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
			}

			if(String{token} == String{"nufed"}) {
				read_next_token();
				break;
			}

			read_next_token();

			switch(tt){
			case NUMBER:{
				break;
			}
			case SYMBOL: {
				if(String{token} == String{"//"}){
					parseComment();
				}
				break;
			}
			case NAME: {
				Node* next_node = nullptr;
				//give command, parse command.
				if(String{token} == String{"var"}){
					next_node = parseVar();
				} 
				else if(String{token} == String{"set"}){
					next_node = parseSet();
				} 
				else if(String{token} == String{"output"}){
					next_node = parseOutput();
				} 
				else if(String{token} == String{"text"}){
					next_node = parseText();
				} 
				else if(String{token} == String{"do"}){
					next_node = parseDo();
				} 
				else if(String{token} == String{"if"}){
					next_node = parseIf();
				} 
				else if(String{token} == String{"defun"}){
					next_node = parseDefun();
				} 
				else if(String{token} == String{"call"}){
					next_node = parseCall();
				} 
				else if(String{token} == String{"return"}){
					next_node = parseReturn();
				} 

				//add next_node to tree
				//special case for returns
				if(root == nullptr) {
					root = next_node;
					current = next_node;
				}
				else {
					current->setNextNode(next_node);
					current = next_node;
				}
				break;
			}
			default:{
				printf("Build Tree error. Unexpected token type. Token type = %i\n", tt);
				break;
			}
			case KEYWORD:
				break;
			case STRING:
				break;
			case INVALID:
				break;
			case END:
				break;
			}

		}

		f_pt.setRoot(root);

		((DefunNode*)function)->setFunction(&f_pt);
		return function;


	}
	Vector<String> parseParams(){
		const char* token = peek_next_token();
		TokenType tt = next_token_type;
		read_next_token();
		
		if(String{token} != String{"params"}) {
			printf("did not find token \"params\"\n");
		}

		Vector<String> result;

		while(true) {
			token = peek_next_token();

			if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
			}

			if(String{token} == String{"smarap"}) {
				read_next_token();
				break;
			}

			result.push_back(String{token});
			read_next_token();
		}

		return result;

	}

	Node* parseCall(){
		CallNode* call = new CallNode{};

		const char* token = peek_next_token();
		TokenType tt = next_token_type;
		read_next_token();

		if(VERBOSE){
			printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
		}


		Node* func_name = new Node{0, String{token}};

		call->setFunctionNameNode(func_name);

		Vector<Node*> args = parseArgs();

		call->setArgumentList(args);

		return call;

	}
	Vector<Node*> parseArgs(){
		const char* token = peek_next_token();
		TokenType tt = next_token_type;
		read_next_token();
		
		if(String{token} != String{"args"}) {
			printf("did not find token \"args\"\n");
		}

		Vector<Node*> result;

		while(true) {
			token = peek_next_token();

			if(VERBOSE){
				printf("Type = %i [%s]\n", tt, (String{token} == String{"\n"}) ? ("\\n") :(token) );
			}

			if(String{token} == String{"sgra"}) {
				read_next_token();
				break;
			}

			Node* expr = parseExpr();
			result.push_back(expr);
			//read_next_token();
		}

		return result;
	}

	Node* parseReturn(){
		ReturnNode*  ret= new ReturnNode{};
		ret->setFunctionRootNode( nullptr);
		Node* expr = parseExpr();
		ret->setReturnExpression(expr);

		return ret;
	}



	void peekTest(){
		const char* token = peek_next_token();
		//read_next_token();
		TokenType tt = next_token_type;

		while(true){
			printf("%s\n", token);

			if(tt == END){
				break;
			}

			token = peek_next_token();


		}
	}

}

#endif