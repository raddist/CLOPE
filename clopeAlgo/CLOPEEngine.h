#pragma once

#include <vector>

class CCluster;
class IDataReader;

class CLOPEEngine
{
public:
	CLOPEEngine() {};

	~CLOPEEngine() {};

	bool Initialize(const char* i_fileName);

	void StartClusterization();

	void Finalize();

private:
	/// @return true if algorithm has finished work
	bool iterateAllTransactions(bool i_isFirstIteration);

private:
	std::vector<CCluster> m_clusters;

	IDataReader* m_transactionReader;

	FILE* m_inputStream;
};