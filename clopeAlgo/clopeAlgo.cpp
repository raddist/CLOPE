#include "stdafx.h"
#include <fstream>
#include <string>

namespace
{
   bool ShowResults(char* i_resFileName, EDistributionInfo info)
   {
      std::ofstream out(i_resFileName, std::ios::out | std::ios::trunc);

      std::string strRow("Cluster\t");
      for (int i = 0; i < info.cols - 1; ++i)
      {
         strRow = strRow + info.names[i] + "\t";
      }
      strRow += "W/o param\n";

      out << strRow;
      strRow.clear();

      for (int i = 0; i < info.rows; ++i)
      {
		  out << "\n";
         strRow = std::to_string(i + 1) + "\t";

         for (int j = 0; j < info.cols; ++j)
         {
            strRow = strRow + std::to_string(info.distribution[info.cols * i + j]) + "\t";
         }
         out << strRow <<"\n";
         strRow.clear();
      }

      out.close();

	  return true;
   }
}

int main(int* argc, char* argv[])
{
	CLOPEEngine* engine = new CLOPEEngine(argv[1], atof(argv[2]), argv[3]);

	engine->Initialize();

	engine->StartClusterization();

	EDistributionInfo info;
	info = engine->ShowDistributionByParam(1);

   ShowResults("D:\\res.txt", info);

   engine->Finalize();
	delete engine;

    return 0;
}

