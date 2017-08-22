#pragma once

class CTransaction
{
public:
	CTransaction() {};

	CTransaction(int* i_startPtr, int i_size);

	~CTransaction();

	int* m_objects;

	int m_len;

	int m_sq;

	int m_clusterOwner;
};