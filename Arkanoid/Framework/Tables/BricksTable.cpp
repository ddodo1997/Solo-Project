#include "stdafx.h"
#include "BricksTable.h"

std::unordered_map<std::string, std::vector<int>> BricksTable::Undefined;

bool BricksTable::Load()
{
	Release();
	std::ifstream fStream(filePath);

	if (!fStream.is_open())
	{
		std::cerr << "String Table File Open Error!!" << std::endl;
	}
	json data = json::parse(fStream);

	for (const auto& map : data.items())
	{
		table.insert({ map.key(), map.value() });
	}

	fStream.close();
	return true;
}

void BricksTable::Release()
{
}

const std::unordered_map<std::string, std::vector<int>>& BricksTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	return find->second;
}