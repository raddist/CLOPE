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
   TxtStreamer(char* i_fileName, char* i_ruleName)
      : m_inFileName(i_fileName)
	   , m_ruleName(i_ruleName)
   {
      makeCinFileNames(i_fileName);
   };

   ~TxtStreamer() {};

   virtual bool OpenStream()
   {
      m_in.open(m_inFileName, std::ios::in | std::ios::out);
      m_out_cin.open(m_cinFileName1, std::ios::out);
	  readRule(m_ruleName);

      if (!m_in)
      {
         std::cout << "Can't open input file";
         return false;
      }

      return true;
   };

   ///////////////////////////////////////////////////////////////////////////////////////////
   virtual bool CloseStream()
   {
      m_in.close();
      m_in_cin.close();
      m_out_cin.close();

      return true;
   };

   ///////////////////////////////////////////////////////////////////////////////////////////
   virtual bool ReadTransaction(CTransaction& o_transaction)
   {
      std::string strTransaction;
      if (std::getline(m_in, strTransaction))
      {
		  std::string convertedStr = convertTransactionString(strTransaction);
		  std::stringstream inputStream(convertedStr);

         int* temp = new int[(convertedStr.size() + 1) / 2.0];
         const char* t = " ";
         int ind = 0;
		 int trClass = -1;
		 int tempInteger = -1;

		 inputStream >> trClass;
		 while (inputStream >> tempInteger)
		 {
			 temp[ind++] = tempInteger;
		 }

         o_transaction.FillTransaction(temp, ind, trClass);

         if (m_readCIN)
         {
            if (std::getline(m_in_cin, convertedStr))
            {
               o_transaction.m_clusterOwner = convertedStr[0] - '0';
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

		 delete[] temp;
         return true;
      }

      return false;
   }

   ///////////////////////////////////////////////////////////////////////////////////////////
   virtual void AppendCINToTransaction(int i_CIN)
   {
      m_out_cin << i_CIN << "\n";
   }

   ///////////////////////////////////////////////////////////////////////////////////////////
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

   ///////////////////////////////////////////////////////////////////////////////////////////
   virtual void RemoveCINFromFile()
   {
      std::remove(m_cinFileName1.c_str());
      std::remove(m_cinFileName2.c_str());
   }

   ///////////////////////////////////////////////////////////////////////////////////////////
   virtual int ReplyAmountOfDifferentArgs()
   {
	   return m_difObj;
   }

   ///////////////////////////////////////////////////////////////////////////////////////////
   virtual std::map<char, int> ReplyParamInformation(int i_param)
   {
	   return m_map[i_param - 1];
   }

   ///////////////////////////////////////////////////////////////////////////////////////////
   void makeCinFileNames(std::string i_baseName)
   {
      m_cinFileName1 = i_baseName + "CIN1.txt";
      m_cinFileName2 = i_baseName + "CIN2.txt";

      m_cinFileName1.erase(m_inFileName.size() - 4, 4);
      m_cinFileName2.erase(m_inFileName.size() - 4, 4);
   }

   private:
   bool readRule(std::string)
   {
	   std::ifstream in(m_ruleName);
	   std::string line;
	   int paramsNumber = 0;

	   // read delimiter symbol
	   if (!std::getline(in, line))
	   {
		   in.close();
		   return false;
	   }

	   int found = line.find("delimiter");
	   if (found != std::string::npos)
	   {
		   found = line.find('"');
		   m_delimiter = line[found + 1];
	   }

	   // read 'unknown' symbol
	   std::getline(in, line);

	   found = line.find("unknown");
	   if (found != std::string::npos)
	   {
		   found = line.find('"');
		   m_unknown = line[found + 1];
	   }

	   // read param information
	   std::getline(in, line);

	   found = line.find("nparams");
	   if (found != std::string::npos)
	   {
		   found = line.find('"');
		   size_t foundEnd = line.find('"', found + 1);

		   paramsNumber = std::stoi(line.substr(found + 1, foundEnd - found - 1));
	   }

	   int ind = 0;
	   int tempInt = 0;
	   std::map<char, int> tempMap;

	   for (int i = 0; i < paramsNumber; ++i)
	   {
		   std::getline(in, line);

		   for (int j = 0; j < line.size(); ++j)
		   {
			   if (line[j] != ' ')
			   {
				   tempMap.insert(std::make_pair(line[j], ind++));
			   }
		   }

		   m_map.push_back(tempMap);
		   tempMap.clear();
	   }
	   
	   m_difObj = ind;

	   in.close();
	   return true;
   }

   std::string convertTransactionString(std::string i_string)
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
