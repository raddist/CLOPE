#pragma once

class IODataStreamer
{
public:
	virtual void OpenStream() {};

	virtual void CloseStream() {};

	virtual bool ReadTransaction(CTransaction& i_transaction, bool i_isCINneeded)
	{
		return true;
	}

	virtual void AppendCINToTransaction(int i_CIN) {};
};