#pragma once

#include "IODataStreamer.h"
#include "transactionImpl.h"
#include <vector>

namespace 
{
	int sc_transaction_1[2] = { 0, 1 };
	int sc_transaction_2[3] = { 0, 1, 2 };
	int sc_transaction_3[3] = { 0, 2, 3 };
	int sc_transaction_4[2] = { 3, 4 };
	int sc_transaction_5[3] = { 3, 4, 5 };

	std::vector<std::pair<int*, int>> transactions = {
		std::make_pair(sc_transaction_1, 2),
		std::make_pair(sc_transaction_2, 3),
		std::make_pair(sc_transaction_3, 3),
		std::make_pair(sc_transaction_4, 2),
		std::make_pair(sc_transaction_5, 3),
	};

	std::vector<int> transactionClusters;
}

class TestStreamer : public IODataStreamer
{
public:
	TestStreamer()
	: m_ptr( 0 )
	{
		transactionClusters.assign(transactions.size(), -1);
	};

	~TestStreamer() {};

	virtual bool OpenStream() { return true; };

	virtual bool CloseStream() { return true;  };

	virtual bool ReadTransaction(CTransaction& o_transaction)
	{
		if (m_ptr < static_cast<int>(transactions.size()))
		{
			o_transaction.FillTransaction(transactions[m_ptr].first, transactions[m_ptr].second);
			o_transaction.m_clusterOwner = transactionClusters[m_ptr];
			++m_ptr;
			return true;
		}

		return false;
	}

	virtual void AppendCINToTransaction(int i_CIN)
	{
		// we have already incremented m_ptr
		// so use previous one
		transactionClusters[m_ptr - 1] = i_CIN;
	}

	virtual void goToTheStreamStart()
	{
		m_ptr = 0;
	}

	virtual void RemoveCINFromFile()
	{
		transactionClusters.clear();
	}

	virtual int ReplyAmountOfDifferentArgs()
	{
		return 6;
	}

	virtual std::map<char, int> ReplyParamInformation(int i_param) 
	{  
		std::map<char, int> res;
		return res;
	};

	int m_ptr;
};