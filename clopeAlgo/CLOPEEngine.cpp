#include "stdafx.h"

bool CLOPEEngine::Initialize(const char* i_fileName)
{
	//fopen_s(&m_inputStream, i_fileName, "r");

	//return m_inputStream ? true : false;
}

void CLOPEEngine::StartClusterization()
{
	bool firstIteration = true;
	while (true)
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
   CTransaction* curTransaction;
   while (m_transactionStreamer->ReadTransaction(curTransaction))
   {

   }

	return false;
}

void CLOPEEngine::Finalize()
{
   /*if (m_inputStream)
   {
   fclose(m_inputStream);
   }*/
}