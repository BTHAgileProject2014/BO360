#include "BOSystem.h"
#define DEBUG

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char* args[])
{
	BOSystem system;
	if (system.Initialize())
	{
		while (system.Run());
	}
	system.Shutdown();
	//_CrtDumpMemoryLeaks();
	return 0;
}