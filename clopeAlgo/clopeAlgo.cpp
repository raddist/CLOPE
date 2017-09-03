#include "stdafx.h"
#include <memory>

int main(int* argc, char* argv[])
{
	CLOPEEngine* engine = new CLOPEEngine(argv[1], atof(argv[2]));

	engine->Initialize();

	engine->StartClusterization();

	engine->Finalize();

	delete engine;

    return 0;
}

