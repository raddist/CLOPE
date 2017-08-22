#pragma once

class CTransaction;

class CCluster
{
public:
	CCluster() {};

	~CCluster() {};

	void AddTransaction(CTransaction i_transactionToAdd);

	void RemoveTransaction(CTransaction i_transactionToRemove);

	int* Occ;

	int m_width;

	int m_s;

	int m_h;

	int m_transactionCounter;
};
