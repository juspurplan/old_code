#include "String.h"
#include "Map.h"


int main(){
	using namespace EE312Project10;
	
	Map<String, int> m;


	printf("put(Hellow, 1)\n");
	printf("put(World, 2)\n");
	printf("(put(fun, 40))\n" );
	m.put(String{"Hellow"}, 1);
	m.put(String{"World"}, 2);
	m.put(String{"fun"}, 40); 

	printf("get(Hellow) = %i\n", m.get(String{"Hellow"}));
	printf("get(World) = %i\n", m.get(String{"World"}));
	printf("get(World) = %i\n", m.get(String{"fun"}));

	printf("put(fun, 10)\n");
	m.put(String{"fun"}, 10);

	printf("get(Hellow) = %i\n", m.get(String{"Hellow"}));
	printf("get(World) = %i\n", m.get(String{"World"}));
	printf("get(World) = %i\n", m.get(String{"fun"}));

	printf("Size = %i\n", m.size());

	printf("clear\n");
	m.clear();

	printf("Size = %i\n", m.size());

	printf("containsKey(Hellow) = %s", (m.containsKey(String{"Hellow"})) ? ("True\n") : ("False\n") );

}
