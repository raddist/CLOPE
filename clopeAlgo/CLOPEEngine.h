#pragma once

#include <vector>

class CCluster;
class IODataStreamer;

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

	double findMaxDelta(CTransaction i_transaction, int o_bestCluster);

	void removeEmptyClusters();

private:
	std::vector<CCluster> m_clusters;
	double m_profit = 0;

	IODataStreamer* m_transactionStreamer;

	double m_R;
};