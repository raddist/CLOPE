#pragma once

#include "IODataStreamer.h"
#include "transactionImpl.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////////////////
class TxtStreamer : public IODataStreamer
{
public:
	TxtStreamer(char* i_fileName, char* i_ruleName);

	~TxtStreamer();

	virtual bool OpenStream();

	virtual bool CloseStream();

	virtual bool ReadTransaction(CTransaction& o_transaction);

	virtual void AppendCINToTransaction(int i_CIN);

	virtual void goToTheStreamStart();

	virtual void RemoveCINFromFile();

	virtual int ReplyAmountOfDifferentArgs();

	virtual std::map<char, int> ReplyParamInformation(int i_param);

	void makeCinFileNames(std::string i_baseName);

private:
	bool readRule(std::string);

	std::string convertTransactionString(std::string i_string);

private:

	bool m_readCIN = false;
	bool doSwitchOutToCIN2 = true;

	std::string m_inFileName = "";
	std::string m_cinFileName1 = "";
	std::string m_cinFileName2 = "";
	std::string m_ruleName;

	std::ifstream m_in_cin;
	std::ofstream m_out_cin;
	std::fstream m_in;

	char m_delimiter;
	char m_unknown;

	std::vector<std::map<char, int>> m_map;
	int m_difObj;
};
