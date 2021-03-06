#pragma once

class CTransaction;

class CCluster
{
public:
	// @brief default ctor
	CCluster(int objAmount);

	// @brief assignment ctor
	void CCluster::operator=(const CCluster& i_other);

	// copy and assignment prohibited
	CCluster(const CCluster&);

	// @brief default dtor
	~CCluster();

	// @brief Calculates relative profit in the case of
	//        adding the transaction to this cluster
	// @param i_transaction in, transaction - candidate to add
	// @param i_rep in, repulsion coefficient
	double DeltaAdd(const CTransaction& i_transaction, double i_rep);

	// @brief Calculates relative profit in the case of
	//        removing the transaction from this cluster
	// @param i_transaction in, transaction - candidate to remove
	// @param i_rep in, repulsion coefficient
	double DeltaRemove(const CTransaction& i_transaction, double i_rep);

	// @brief Adds transaction to cluster
	// @param i_transactionToAdd in, added transaction
	void AddTransaction(const CTransaction& i_transactionToAdd);

	// @brief Removes transaction from cluster
	// @param i_transactionToRemove in, removed transaction
	void RemoveTransaction(const CTransaction& i_transactionToRemove);

	int* Occ;	//< contains array of objects 

	int m_width;//< count number of different objects contained in cluster

	int m_s;	//< accumulated number of all objects

	int m_transactionCounter;	//< count number of transaction containing in this cluster

	int m_occMaxSize;	//< used for copy constructor
};
