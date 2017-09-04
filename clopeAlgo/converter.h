#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <map>

class CConverter
{
public:
	bool ReadRule(char* i_fileName)
	{
		m_delimiter = ',';
		m_unknown = '?';

		int ind = 0;

		std::map<std::string, int> tempMap;
		tempMap.insert(std::make_pair("1", ind++));
		tempMap.insert(std::make_pair("3", ind++));
		m_map.push_back(tempMap);
		tempMap.clear();

		tempMap.insert(std::make_pair("0", ind++));
		m_map.push_back(tempMap);
		tempMap.clear();

		tempMap.insert(std::make_pair("2", ind++));
		m_map.push_back(tempMap);
		tempMap.clear();

		tempMap.insert(std::make_pair("4", ind++));
		m_map.push_back(tempMap);
		tempMap.clear();

		tempMap.insert(std::make_pair("5", ind++));
		m_map.push_back(tempMap);
		tempMap.clear();

		m_difObj = ind;

		return true;
	}

	std::string ConvertTransactionString(std::string i_string)
	{
		int param = 0;
		int strLen = i_string.size();
		bool firstSym = true;

		std::string resStr = "";
		std::string spaceDelimiter = " ";

		for (int i = 0; i < strLen; ++i)
		{
			if (i_string[i] != m_delimiter)
			{
				if (i_string[i] != m_unknown)
				{
					resStr += firstSym
						? std::to_string(m_map[param].at(i_string[i]))
						: spaceDelimiter + std::to_string(m_map[param].at(i_string[i]));
					firstSym = false;
				}
				++param;
			}
		}

		return resStr;
	}

	int ReplyAmountOfObjects()
	{
		return m_difObj;
	}

	std::map<std::string, int> ReplyParamMap(int i_param)
	{
		return m_map[i_param - 1];
	}

private:
	char m_delimiter;
	char m_unknown;

	std::vector<std::map<std::string, int>> m_map;
	int m_difObj;
};

