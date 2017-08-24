#include "stdafx.h"

CTransaction::CTransaction(int* i_startPtr, int i_size)
{
	m_objects = new int[i_size];
	for (int i = 0; i < i_size; ++i)
	{
		m_objects[i] = i_startPtr[i];
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
CTransaction::~CTransaction()
{
	delete[] m_objects;
}

//////////////////////////////////////////////////////////////////////////
void CTransaction::FillTransaction(int* i_startPtr, int i_size)
{
	delete[] m_objects;

	m_objects = new int[i_size];
	for (int i = 0; i < i_size; ++i)
	{
		m_objects[i] = i_startPtr[i];
	}
}