


#include "String.h"
#include "Node.h"
#include "Map.h"
#include "ParseTree.h"
#include "Util.h"


int main (){
	using namespace EE312Project10;

	//setinput("blah.blip");
	ParseTree& pt = buildParseTree();
	//printf("Done Building Tree\nExecuting...\n\n");
	pt.execute();
	delete &pt;


}

