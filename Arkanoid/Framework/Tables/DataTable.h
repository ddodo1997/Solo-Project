#pragma once
class DataTable
{
public:
	enum class Types
	{
		String,
		Vause,
		Item,
		Blocks,
	};
	static const int TotalType = 4;

protected:
	Types type;

public:

	DataTable(Types type) :type(type) {}
	~DataTable() = default;

	virtual bool Load() = 0;
	virtual void Release() = 0;
};