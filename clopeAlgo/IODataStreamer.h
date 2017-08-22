#pragma once

class IDataStream
{
   virtual void OpenStream();

   virtual void CloseStream();

   virtual bool ReadTransaction(CTransaction& i_transaction);

   virtual void ReadTransactionWithCIN();

   virtual void AppendCINToTransaction(int i_CIN);
}