#include "stdafx.h"
#include <memory>

int main(int* argc, char* argv[])
{
	CLOPEEngine* engine = new CLOPEEngine(argv[1], atof(argv[2]));

	engine->Initialize();

	engine->StartClusterization();

	engine->Finalize();

	int* etemp = NULL;
	engine->ShowDistributionByParam(1, etemp);

	delete engine;

    return 0;
}

