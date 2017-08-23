#include "stdafx.h"
#include <math.h>

CCluster::CCluster() {};

CCluster::~CCluster() {};

///////////////////////////////////////////////////////////////////////////////////////////
double CCluster::DeltaAdd(CTransaction i_transaction, double i_rep)
{
	int newSq = m_s + i_transaction.m_sq;

	int newWidth = m_width;
	for (int i = 0; i < i_transaction.m_len; ++i)
	{
		if (Occ[i_transaction.m_objects[i]] == 0)
		{
			newWidth += 1;
		}
	}

	return newSq * (m_transactionCounter + 1) / pow(newWidth, i_rep)
		- m_s * m_transactionCounter / pow(m_width, i_rep);
}

///////////////////////////////////////////////////////////////////////////////////////////
double CCluster::DeltaRemove(CTransaction i_transaction, double i_rep)
{
	int newSq = m_s - i_transaction.m_sq;

	int newWidth = m_width;
	for (int i = 0; i < i_transaction.m_len; ++i)
	{
		if (Occ[i_transaction.m_objects[i]] - i_transaction.m_objects[i + i_transaction.m_len] == 0)
		{
			newWidth -= 1;
		}
	}

	return m_s * m_transactionCounter / pow(m_width, i_rep)
		- newSq * (m_transactionCounter + 1) / pow(newWidth, i_rep);
}

///////////////////////////////////////////////////////////////////////////////////////////
void CCluster::AddTransaction(CTransaction i_transactionToAdd)
{
	int deltaWidth = 0;

	// add new objecs
	for (int i = 0; i < i_transactionToAdd.m_len; ++i)
	{
		if (Occ[i_transactionToAdd.m_objects[i]] == 0)
		{
			deltaWidth += 1;
		}

		Occ[i_transactionToAdd.m_objects[i]] += i_transactionToAdd.m_objects[i + i_transactionToAdd.m_len];
	}

	// change width
	m_width += deltaWidth;

	// change sq
	m_s += i_transactionToAdd.m_sq;

	// change height
	m_h = m_s / m_width;

	// change numver of containing transactions
	m_transactionCounter++;
};

///////////////////////////////////////////////////////////////////////////////////////////
void CCluster::RemoveTransaction(CTransaction i_transactionToRemove)
{
	int deltaWidth = 0;
	// remove objects
	for (int i = 0; i < i_transactionToRemove.m_len; ++i)
	{
		Occ[i_transactionToRemove.m_objects[i]] -= i_transactionToRemove.m_objects[i + i_transactionToRemove.m_len];

		if (Occ[i_transactionToRemove.m_objects[i]] == 0)
		{
			deltaWidth -= 1;
		}
	}

	// change width
	m_width += deltaWidth;

	// change sq
	m_s -= i_transactionToRemove.m_sq;

	// change height
	m_h = m_s / m_width;

	// change numver of containing transactions
	m_transactionCounter--;
};