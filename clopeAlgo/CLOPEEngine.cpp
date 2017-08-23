#include "stdafx.h"
#include <math.h>
#include <algorithm>

bool CLOPEEngine::Initialize(const char* i_fileName)
{
	//fopen_s(&m_inputStream, i_fileName, "r");

	//return m_inputStream ? true : false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////
void CLOPEEngine::StartClusterization()
{
	doFirstIteration();

	while (true)
	{
		if ( !iterateAllTransactions() )
		{
			break;
		}
	}

	removeEmptyClusters();
	m_transactionStreamer->RemoveCINFromFile();
}

///////////////////////////////////////////////////////////////////////////////////////////
void CLOPEEngine::doFirstIteration()
{
	CTransaction* curTransaction = new CTransaction();;
	while (m_transactionStreamer->ReadTransaction(*curTransaction, false))
	{
		double deltaNew = curTransaction->m_sq / pow(curTransaction->m_len, m_R);

		int bestFoundCluster = -1;
		double foundDelta = findMaxDelta(*curTransaction, bestFoundCluster);


		if (deltaNew > foundDelta)
		{
			m_clusters.emplace_back();
			m_profit = (m_profit * m_transactionCounter + deltaNew)
				/ static_cast<double>(m_transactionCounter + 1);
			m_transactionStreamer->AppendCINToTransaction(static_cast<int>(m_clusters.size()) - 1);
		}
		else
		{
			m_clusters[bestFoundCluster].AddTransaction(*curTransaction);
			m_profit = (m_profit * m_transactionCounter + foundDelta)
				/ static_cast<double>(m_transactionCounter + 1);
			m_transactionStreamer->AppendCINToTransaction(bestFoundCluster);
		}

		m_transactionCounter++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
bool CLOPEEngine::iterateAllTransactions()
{
	bool isAnyTransactionMoved = false;

	CTransaction* curTransaction = new CTransaction();;
   while (m_transactionStreamer->ReadTransaction(*curTransaction, true))
   {
	   double deltaNew = curTransaction->m_sq / pow(curTransaction->m_len, m_R);
	   double deltaRemove = m_clusters[curTransaction->m_clusterOwner].DeltaRemove(*curTransaction, m_R);

	   int bestFoundCluster = -1;
	   double foundDelta = findMaxDelta(*curTransaction, bestFoundCluster);

	   if (deltaRemove > std::max(deltaNew, foundDelta))
	   {
		   continue;
	   }

	   isAnyTransactionMoved = true;
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

	return isAnyTransactionMoved;
}

///////////////////////////////////////////////////////////////////////////////////////////
double CLOPEEngine::findMaxDelta(CTransaction i_transaction, int  o_bestCluster)
{
	int index = 0;
	double bestDelta = 0.0;
	o_bestCluster = -1;

	for (CCluster cluster : m_clusters)
	{
		double delta = cluster.DeltaAdd(i_transaction, m_R);
		if (i_transaction.m_clusterOwner != index &&
			delta > bestDelta)
		{
			bestDelta = delta;
		}
	}

	return bestDelta;
}

///////////////////////////////////////////////////////////////////////////////////////////
void CLOPEEngine::removeEmptyClusters()
{
	for (auto it = m_clusters.begin(); it != m_clusters.end(); ++it)
	{
		if (it->m_transactionCounter == 0)
		{
			m_clusters.erase(it);
		}
	}
};

///////////////////////////////////////////////////////////////////////////////////////////
void CLOPEEngine::Finalize()
{
   /*if (m_inputStream)
   {
   fclose(m_inputStream);
   }*/
}