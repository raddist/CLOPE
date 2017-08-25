#pragma once

class CTransaction
{
public:
	CTransaction () 
	: m_clusterOwner(-1)
	{};

	CTransaction(int* i_startPtr, int i_size);

	~CTransaction();

	void FillTransaction(int* i_startPtr, int i_size);

	int* m_objects;

	int m_len;

	int m_clusterOwner;
};