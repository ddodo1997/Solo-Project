#pragma once
#include "DataTable.h"
class StageTable :
    public DataTable
{
public:
	static  std::vector<std::vector<int>> Undefined;

protected:
	std::unordered_map<std::string, std::vector<std::vector<int>>> table;
	std::string filePath = "tables/stages.json";
public:
	StageTable() : DataTable(DataTable::Types::Stages) { };
	~StageTable() = default;

	bool Load() override;
	void Release() override;
	void SetPath();

	const  std::vector<std::vector<int>>& Get(const std::string& id);

};

