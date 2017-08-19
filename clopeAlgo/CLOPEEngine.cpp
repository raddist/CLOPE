#include "stdafx.h"
#include <iostream>

bool CLOPEEngine::Initialize(const char* i_fileName)
{
	fopen_s(&m_inputStream, i_fileName, "r");
}

void CLOPEEngine::StartClusterization()
{
	bool firstIteration = true;
	while (!m_inputStream)
	{
		if (iterateAllTransactions(firstIteration))
		{
			break;
		}
		firstIteration = false;
	}
}

bool CLOPEEngine::iterateAllTransactions(bool i_isFirstIteration)
{

}

void CLOPEEngine::Finalize()
{
	if (m_inputStream)
	{
		fclose(m_inputStream);
	}
}