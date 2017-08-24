#pragma once

class IODataStreamer
{
public:
	virtual void OpenStream() = 0;

	virtual void CloseStream() = 0;

	virtual bool ReadTransaction(CTransaction& i_transaction, bool i_isCINneeded) = 0;

	virtual void AppendCINToTransaction(int i_CIN) = 0;

	virtual void RemoveCINFromFile() = 0;

	virtual int ReplyAmountOfDifferentArgs() = 0;
};