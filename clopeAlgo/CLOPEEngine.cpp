#include "stdafx.h"
#include <math.h>

bool CLOPEEngine::Initialize(const char* i_fileName)
{
	//fopen_s(&m_inputStream, i_fileName, "r");

	//return m_inputStream ? true : false;
	return true;
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
	CTransaction* curTransaction = new CTransaction();;
   while (m_transactionStreamer->ReadTransaction(*curTransaction, !i_isFirstIteration))
   {
	   double deltaNew = curTransaction->m_sq / pow(curTransaction->m_len, m_R);

	   int bestFoundCluster = -1;
	   double foundDelta = findMaxDelta(bestFoundCluster,
										i_isFirstIteration ? -1 : curTransaction->m_clusterOwner);


	   if (deltaNew > foundDelta)
	   {
		   m_clusters.emplace_back();
		   m_profit += deltaNew;
		   m_transactionStreamer->AppendCINToTransaction(static_cast<int>(m_clusters.size()) - 1);
	   }
	   else
	   {
		   m_clusters[bestFoundCluster].AddTransaction(*curTransaction);
		   m_profit += foundDelta;
		   m_transactionStreamer->AppendCINToTransaction(bestFoundCluster);
	   }
   }

   removeEmptyClusters();
	return false;
}

double CLOPEEngine::findMaxDelta(int o_bestCluster, int i_exceptCluster)
{
	o_bestCluster = 0;
	return 0.0;
}

void CLOPEEngine::removeEmptyClusters() {};

void CLOPEEngine::Finalize()
{
   /*if (m_inputStream)
   {
   fclose(m_inputStream);
   }*/
}