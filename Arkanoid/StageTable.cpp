#include "stdafx.h"
#include "StageTable.h"

std::vector<std::vector<int>> StageTable::Undefined;

bool StageTable::Load()
{
	Release();
	std::ifstream fStream(filePath);

	if (!fStream.is_open())
	{
		std::cerr << "Stage Table File Open Error!!" << std::endl;
	}
	json data = json::parse(fStream);

	for (const auto& map : data.items())
	{
		table.insert({ map.key(), map.value() });
	}

	fStream.close();
	return true;
}

void StageTable::Release()
{
}

void StageTable::SetPath()
{
}

const std::vector<std::vector<int>>& StageTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}
