


#include "String.h"
#include "Node.h"
#include "Map.h"
#include "ParseTree.h"
#include "Util.h"


int main (){
	using namespace EE312Project10;

	/*
	printf("Testing copying Nodes\n" );
	Node* n = new Node{};
	n->setNextNode(new TextNode{});
	((TextNode*)n->getNextNode())->setStringNode(new Node{0, String{"Weee"}});

	Node* n2 = n->clone();
	String result = ((TextNode*)n2->getNextNode())->getStringNode()->getString();
	printf("%s\n", result.c_str());
	*/

	//input: multiple peek test
	//conclusion: multiple peeking works and does not advance to next token.
	//peekTest();

	//setinput("blah.blip");
	ParseTree& pt = buildParseTree();
	pt.setGlobalsToLocals();
	//printf("Done Building Tree\nExecuting...\n\n");
	pt.execute();
	delete &pt;


}

