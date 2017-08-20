#pragma once

class CTransaction
{
public:
	CTransaction() {};

	CTransaction(int* i_startPtr, int i_size);

	~CTransaction();

	int* m_objects;
};