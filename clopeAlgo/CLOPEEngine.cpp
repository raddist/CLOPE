#include "stdafx.h"

#include <math.h>
#include <algorithm>
#include <cstring>
#include "test42.h"
#include "txtStreamer.h"

CLOPEEngine::CLOPEEngine(char* i_fileName, double i_r)
{
	if (!strcmp(i_fileName, "42"))
	{
		m_transactionStreamer = new TestStreamer();
		m_R = 2.0;
	}

	m_transactionStreamer = new TxtStreamer(i_fileName);
	m_R = i_r;
}

///////////////////////////////////////////////////////////////////////////////////////////
bool CLOPEEngine::Initialize()
{
	return m_transactionStreamer->OpenStream();
}

///////////////////////////////////////////////////////////////////////////////////////////
void CLOPEEngine::StartClusterization()
{
	doFirstIteration();

	while (true)
	{
		m_transactionStreamer->goToTheStreamStart();
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
	while (m_transactionStreamer->ReadTransaction(*curTransaction))
	{
		double deltaNew = curTransaction->m_len / pow(curTransaction->m_len, m_R);

		int indexOfClusterToAddIn = -1;
		double foundDelta = findMaxDelta(*curTransaction, indexOfClusterToAddIn);


		if (deltaNew > foundDelta)
		{
			m_clusters.emplace_back( m_transactionStreamer->ReplyAmountOfDifferentArgs());
			indexOfClusterToAddIn = static_cast<int>(m_clusters.size() - 1);
		}

		m_clusters[indexOfClusterToAddIn].AddTransaction(*curTransaction);
		m_profit = (m_profit * m_transactionCounter + std::max(deltaNew, foundDelta))
			/ static_cast<double>(m_transactionCounter + 1);
		m_transactionStreamer->AppendCINToTransaction(indexOfClusterToAddIn);

		m_transactionCounter++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
bool CLOPEEngine::iterateAllTransactions()
{
	bool isAnyTransactionMoved = false;

	CTransaction* curTransaction = new CTransaction();;

   while (m_transactionStreamer->ReadTransaction(*curTransaction))
   {
	   double deltaNew = curTransaction->m_len / pow(curTransaction->m_len, m_R);
	   double deltaRemove = m_clusters[curTransaction->m_clusterOwner].DeltaRemove(*curTransaction, m_R);

	   int indexOfClusterToAddIn = -1;
	   double foundDelta = findMaxDelta(*curTransaction, indexOfClusterToAddIn, curTransaction->m_clusterOwner);

	   if (deltaRemove > std::max(deltaNew, foundDelta))
	   {
		   continue;
	   }

	   isAnyTransactionMoved = true;
	   m_clusters[curTransaction->m_clusterOwner].RemoveTransaction(*curTransaction);

	   if (deltaNew > foundDelta)
	   {
		   m_clusters.emplace_back( CCluster(m_transactionStreamer->ReplyAmountOfDifferentArgs()) );
		   indexOfClusterToAddIn = static_cast<int>(m_clusters.size() - 1);
	   }

	   m_clusters[indexOfClusterToAddIn].AddTransaction(*curTransaction);
	   m_profit = m_profit - (deltaRemove + std::max(deltaNew, foundDelta)) / static_cast<double>(m_transactionCounter);
	   m_transactionStreamer->AppendCINToTransaction(indexOfClusterToAddIn);
   }

	return isAnyTransactionMoved;
}

///////////////////////////////////////////////////////////////////////////////////////////
double CLOPEEngine::findMaxDelta(const CTransaction& i_transaction, int&  o_bestCluster, int exceptCluster)
{
	double bestDelta = 0.0;
	o_bestCluster = -1;

	for (int i = 0; i < m_clusters.size(); ++i)
	{
		double delta = m_clusters[i].DeltaAdd(i_transaction, m_R);
		if ( (exceptCluster < 0 ||
			  i_transaction.m_clusterOwner != exceptCluster) &&
			delta > bestDelta)
		{
			bestDelta = delta;
			o_bestCluster = i;
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
	m_transactionStreamer->CloseStream();
}