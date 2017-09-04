#include "stdafx.h"

CTransaction::CTransaction(int* i_startPtr, int i_size)
{
	m_objects = new int[i_size];
	for (int i = 0; i < i_size; ++i)
	{
		m_objects[i] = i_startPtr[i];
	}
	m_len = i_size;
}

///////////////////////////////////////////////////////////////////////////////////////////
CTransaction::~CTransaction()
{
	delete[] m_objects;
}

//////////////////////////////////////////////////////////////////////////
void CTransaction::FillTransaction(int* i_startPtr, int i_size, int i_class)
{
	if (i_size != m_len)
	{
		delete[] m_objects;
		m_objects = new int[i_size];
		m_len = i_size;
	}

	for (int i = 0; i < i_size; ++i)
	{
		m_objects[i] = i_startPtr[i];
	}

	m_class = i_class;
}