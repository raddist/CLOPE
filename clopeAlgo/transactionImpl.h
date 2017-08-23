#pragma once

class CTransaction
{
public:
	CTransaction () 
	: m_clusterOwner(-1)
	{};

	CTransaction(int* i_startPtr, int i_size);

	~CTransaction();

	int* m_objects;

	int m_len;

	int m_sq;

	int m_clusterOwner;
};