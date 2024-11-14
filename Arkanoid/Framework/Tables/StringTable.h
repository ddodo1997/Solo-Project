#pragma once

class StringTable : public DataTable
{
public:
	static std::string Undefined;

protected:
	// <T1, T2>
	//	T1: 스트링 아이디
	//	T2: 언어별 스트링 ([0] 한국어 [1] 영어 ...)
	std::unordered_map<std::string, std::string> table;
	std::string filePath = "tables/main_string.json";
public:
	StringTable() : DataTable(DataTable::Types::String) { };
	~StringTable() = default;

	bool Load() override;
	void Release() override;
	void SetPath();

	const std::string& Get(const std::string& id);
};