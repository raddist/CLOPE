#include "stdafx.h"
#include <fstream>
#include <string>

namespace
{
   bool ShowResults(char* i_resFileName, int* res, int rows, int cols)
   {
      std::ofstream out(i_resFileName, std::ios::out | std::ios::trunc);

      int ind = 1;

      std::string strRow("Cluster\t");
      for (int i = 0; i < cols - 1; ++i)
      {
         strRow = strRow + std::to_string(res[i]) + "\t";
      }
      strRow += "W/o param\n";

      out << strRow;
      strRow.clear();

      for (int i = 1; i < rows; ++i)
      {
         strRow = std::to_string(i) + "\t";

         for (int j = 0; j < cols; ++j)
         {
            strRow = strRow + std::to_string(res[i * cols + j]) + "\t";
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

	engine->Finalize();

	int* etemp = NULL;
   int rows = 0;
   int cols = 0;
	etemp = engine->ShowDistributionByParam(1, rows, cols);

   ShowResults("D:\\res.txt", etemp, rows, cols);

	delete engine;

    return 0;
}

