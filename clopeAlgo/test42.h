#pragma once

#include "IODataStreamer.h"
#include "transactionImpl.h"
#include <vector>

namespace 
{
	int sc_transaction_1[2] = { 1, 2 };
	int sc_transaction_2[3] = { 1, 2, 3 };
	int sc_transaction_3[3] = { 1, 3, 4 };
	int sc_transaction_4[2] = { 4, 5 };
	int sc_transaction_5[3] = { 4, 5, 6 };

	std::vector<std::pair<int*, int>> transactions = {
		std::make_pair(sc_transaction_1, 2),
		std::make_pair(sc_transaction_2, 3),
		std::make_pair(sc_transaction_3, 3),
		std::make_pair(sc_transaction_4, 2),
		std::make_pair(sc_transaction_5, 3),
	};

	std::vector<int> transactionClusters;
}

class TestStreamer : IODataStreamer
{
	TestStreamer()
	: m_ptr( 0 )
	{
		transactionClusters.resize(transactions.size());
	};

	~TestStreamer() {};

	virtual void OpenStream() {};

	virtual void CloseStream() {};

	virtual bool ReadTransaction(CTransaction& i_transaction, bool i_isCINneeded)
	{
		if (m_ptr < transactions.size())
		{
			i_transaction.FillTransaction(transactions[m_ptr].first, transactions[m_ptr].second);
			return true;
		}
		return false;
	}

	virtual void AppendCINToTransaction(int i_CIN)
	{

	}

	virtual void RemoveCINFromFile() ;

	virtual int ReplyAmountOfDifferentArgs() ;

	int m_ptr;
};