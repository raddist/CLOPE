#include "stdafx.h"
#include <math.h>

CCluster::CCluster(int objAmount)
: m_width( 0 )
, m_s( 0 )
, m_transactionCounter( 0 )
, m_occMaxSize( objAmount )
{
	Occ = new int[objAmount];
	for (int i = 0; i < m_occMaxSize; ++i)
	{
		Occ[i] = 0;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////
void CCluster::operator=(const CCluster& i_other)
{
	m_occMaxSize = i_other.m_occMaxSize;

	Occ = new int[m_occMaxSize];
	for (int i = 0; i < m_occMaxSize; ++i)
	{
		Occ[i] = i_other.Occ[i];
	}

	m_width = i_other.m_width;

	m_s = i_other.m_s;

	m_transactionCounter = i_other.m_transactionCounter;

	m_occMaxSize = i_other.m_occMaxSize;
}

///////////////////////////////////////////////////////////////////////////////////////////
CCluster::CCluster(const CCluster& i_other)
{
	m_occMaxSize = i_other.m_occMaxSize;

	Occ = new int[m_occMaxSize];
	for (int i = 0; i < m_occMaxSize; ++i)
	{
		Occ[i] = i_other.Occ[i];
	}

	m_width = i_other.m_width;

	m_s = i_other.m_s;

	m_transactionCounter = i_other.m_transactionCounter;
}

///////////////////////////////////////////////////////////////////////////////////////////
CCluster::~CCluster()
{
	delete[] Occ;
};

///////////////////////////////////////////////////////////////////////////////////////////
double CCluster::DeltaAdd(const CTransaction& i_transaction, double i_rep)
{
	int newSq = m_s + i_transaction.m_len;
	int newWidth = m_width;
	for (int i = 0; i < i_transaction.m_len; ++i)
	{
		int t1 = i_transaction.m_objects[i];
		int t = Occ[i_transaction.m_objects[i]];
		if (Occ[i_transaction.m_objects[i]] == 0)
		{
			newWidth += 1;
		}
	}

	return newSq * (m_transactionCounter + 1) / pow(newWidth, i_rep)
		- m_s * m_transactionCounter / pow(m_width, i_rep);
}

///////////////////////////////////////////////////////////////////////////////////////////
double CCluster::DeltaRemove(const CTransaction& i_transaction, double i_rep)
{
	int newSq = m_s - i_transaction.m_len;
	int newWidth = m_width;
	for (int i = 0; i < i_transaction.m_len; ++i)
	{
		if (Occ[i_transaction.m_objects[i]] - 1 == 0)
		{
			newWidth -= 1;
		}
	}

	if (newWidth == 0)
	{
		return m_s * m_transactionCounter / pow(m_width, i_rep);
	}

	return m_s * m_transactionCounter / pow(m_width, i_rep)
		- newSq * (m_transactionCounter - 1) / pow(newWidth, i_rep);
}

///////////////////////////////////////////////////////////////////////////////////////////
void CCluster::AddTransaction(const CTransaction& i_transactionToAdd)
{
	int deltaWidth = 0;

	// add new objecs
	for (int i = 0; i < i_transactionToAdd.m_len; ++i)
	{
		int tt = i_transactionToAdd.m_objects[i];
		if (Occ[i_transactionToAdd.m_objects[i]] == 0)
		{
			deltaWidth += 1;
		}
		Occ[i_transactionToAdd.m_objects[i]] += 1;
	}

	// change width
	m_width += deltaWidth;

	// change sq
	m_s += i_transactionToAdd.m_len;

	// change number of containing transactions
	m_transactionCounter++;
};

///////////////////////////////////////////////////////////////////////////////////////////
void CCluster::RemoveTransaction(const CTransaction& i_transactionToRemove)
{
	int deltaWidth = 0;
	// remove objects
	for (int i = 0; i < i_transactionToRemove.m_len; ++i)
	{
		Occ[i_transactionToRemove.m_objects[i]] -= 1;
		if (Occ[i_transactionToRemove.m_objects[i]] == 0)
		{
			deltaWidth -= 1;
		}
	}

	// change width
	m_width += deltaWidth;

	// change sq
	m_s -= i_transactionToRemove.m_len;

	// change numver of containing transactions
	m_transactionCounter--;
};
