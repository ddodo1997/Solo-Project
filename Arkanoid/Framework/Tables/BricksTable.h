#pragma once
#include "DataTable.h"
class BricksTable :
    public DataTable
{
public:
	static std::unordered_map<std::string, std::vector<int>> Undefined;

protected:
	std::unordered_map<std::string, std::unordered_map<std::string,std::vector<int>>> table;
	std::string filePath = "tables/bricks.json";
public:
	BricksTable() : DataTable(DataTable::Types::Bricks) {};
	~BricksTable() = default;

	bool Load() override;
	void Release() override;

	const std::unordered_map<std::string, std::vector<int>>& Get(const std::string& id);
};
