#include "stdafx.h"

CTransaction::CTransaction(int* i_startPtr, int i_size)
{
	m_objects = new int[i_size];
	for (int i = 0; i < i_size; ++i)
	{
		m_objects[i] = i_startPtr[i];
	}
	m_len = i_size;
	std::cout << "new" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////
CTransaction::~CTransaction()
{
	delete[] m_objects;
	std::cout << "release" << std::endl;
}

//////////////////////////////////////////////////////////////////////////
void CTransaction::FillTransaction(int* i_startPtr, int i_size)
{
	delete[] m_objects;
	std::cout << "release" << std::endl;

	m_objects = new int[i_size];
	for (int i = 0; i < i_size; ++i)
	{
		m_objects[i] = i_startPtr[i];
	}
	m_len = i_size;
	std::cout << "new" << std::endl;
}