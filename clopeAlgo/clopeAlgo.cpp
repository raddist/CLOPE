#include "stdafx.h"
#include <memory>

int main(int* argc, char* argv[])
{
	CLOPEEngine* engine = new CLOPEEngine();

	engine->Initialize(argv[1]);

    return 0;
}
