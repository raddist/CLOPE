#pragma once
#include <map>
#include <string>

class IODataStreamer
{
public:
	virtual bool OpenStream() = 0;

	virtual bool CloseStream() = 0;

	virtual bool ReadTransaction(CTransaction& i_transaction) = 0;

	virtual void AppendCINToTransaction(int i_CIN) = 0;

	virtual void goToTheStreamStart() = 0;

	virtual void RemoveCINFromFile() = 0;

	virtual int ReplyAmountOfDifferentArgs() = 0;

	virtual std::map<char, int> ReplyParamInformation(int i_param) = 0;
};