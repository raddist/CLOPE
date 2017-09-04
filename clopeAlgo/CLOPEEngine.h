#pragma once

#include <vector>

class CCluster;
class CTransaction;
class IODataStreamer;

typedef struct EDistributionInfo {
	std::vector<std::string> names;
	std::vector<int> distribution;
	int rows;
	int cols;
};

class CLOPEEngine
{
public:
	CLOPEEngine(char* i_fileName, double i_r, char* i_ruleName);

	~CLOPEEngine();

	bool Initialize();

	void StartClusterization();

   EDistributionInfo ShowDistributionByParam(int i_paramNumber);

	void Finalize();

private:

	void doFirstIteration();

	/// @return true if algorithm has finished work
	bool iterateAllTransactions();

	double findMaxDelta(const CTransaction& i_transaction, int& o_bestCluster, int exceptCluster = -1);

	void removeEmptyClusters();

private:
	std::vector<CCluster> m_clusters;

	double m_profit = 0;
	unsigned long m_transactionCounter = 0;

	IODataStreamer* m_transactionStreamer;

	double m_R;
};