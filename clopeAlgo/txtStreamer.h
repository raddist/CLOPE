#pragma once

#include "IODataStreamer.h"
#include "transactionImpl.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>


class TxtStreamer : public IODataStreamer
{
public:
	TxtStreamer(char* i_fileName)
		: m_inFileName(i_fileName)
	{
		makeCinFileNames(i_fileName);
	};

	~TxtStreamer() {};

	virtual bool OpenStream()
	{
		m_in.open(m_inFileName, std::ios::in | std::ios::out);
		m_out_cin.open(m_cinFileName1, std::ios::out);

		if (!m_in)
		{
			std::cout << "Can't open input file";
			return false;
		}

		return true;
	};

	virtual bool CloseStream()
	{
		m_in.close();
		m_in_cin.close();
		m_out_cin.close();

		return true;
	};

	virtual bool ReadTransaction(CTransaction& o_transaction)
	{
		std::string strTransaction;
		if (std::getline(m_in, strTransaction))
		{
			int* temp = new int[(strTransaction.size() + 1) / 2.0];
			const char* t = " ";
			int ind = 0;

			for (auto it = strTransaction.begin(); it < strTransaction.end(); ++it)
			{
				if (*it != *t)
				{
					temp[ind++] = *it - '0';
				}
			}

			o_transaction.FillTransaction(temp, ind);

			if (m_readCIN)
			{
				if (std::getline(m_in_cin, strTransaction))
				{
					o_transaction.m_clusterOwner = strTransaction[0] - '0';
				}
				else
				{
					// error
				}
			}
			else
			{
				o_transaction.m_clusterOwner = -1;
			}

			return true;
		}

		return false;
	}

	virtual void AppendCINToTransaction(int i_CIN)
	{
		m_out_cin << i_CIN << "\n";
	}

	virtual void goToTheStreamStart()
	{
		m_in.clear();
		m_in.seekg(0);

		// close temp files
		m_in_cin.close();
		m_out_cin.close();

		if (doSwitchOutToCIN2)
		{
			m_in_cin.open(m_cinFileName1);
			m_out_cin.open(m_cinFileName2, std::ios::trunc | std::ios::out);
		}
		else
		{
			m_in_cin.open(m_cinFileName2);
			m_out_cin.open(m_cinFileName1, std::ios::trunc | std::ios::out);
		}

		m_readCIN = true;
	}

	virtual void RemoveCINFromFile()
	{
		transactionClusters.clear();
	}

	virtual int ReplyAmountOfDifferentArgs()
	{
		return 6;
	}

	virtual int* ReplyParamInformation(int i_param, int& o_size)
	{
		if (i_param == 1)
		{
			o_size = 2;

			int* o_obj = new int[o_size];
			o_obj[0] = 0;
			o_obj[1] = 4;

			return o_obj;
		}
	}

	void makeCinFileNames(std::string i_baseName)
	{
		m_cinFileName1 = i_baseName + "CIN1.txt";
		m_cinFileName2 = i_baseName + "CIN2.txt";

		m_cinFileName1.erase(m_inFileName.size() - 4, 4);
		m_cinFileName2.erase(m_inFileName.size() - 4, 4);
	}

	bool m_readCIN = false;
	bool doSwitchOutToCIN2 = true;

	std::string m_inFileName = "";
	std::string m_cinFileName1 = "";
	std::string m_cinFileName2 = "";

	std::ifstream m_in_cin;
	std::ofstream m_out_cin;
	std::fstream m_in;
};
