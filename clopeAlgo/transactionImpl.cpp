#include "stdafx.h"

CTransaction::CTransaction(int* i_startPtr, int i_size)
{
	m_objects = new int[i_size];
}

///////////////////////////////////////////////////////////////////////////////////////////
CTransaction::~CTransaction()
{
	delete[] m_objects;
}