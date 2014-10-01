#include "BOSystem.h"
#define DEBUG

int main(int argc, char* args[])
{
	BOSystem system;
	if (system.Initialize())
	{
		while (system.Run());
	}
	system.Shutdown();
	return 0;
}