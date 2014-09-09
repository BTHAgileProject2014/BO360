#include "BOSystem.h"

int main(int argc, char* args[])
{
	BOSystem system;
	if (system.Initialize())
	{
		while (system.Run());
	}
	return 0;
}