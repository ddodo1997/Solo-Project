#pragma once

class SaveData
{
public:
	int version = 0;
	virtual SaveData* VersionUp() = 0;
};

class SaveDataV1 : public SaveData
{
public:
	SaveDataV1() { version = 1; }

	int infinityHighScore = 0;
	int normalHighScore = 0;
	SaveData* VersionUp() override { return nullptr; }
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SaveDataV1, version, normalHighScore, infinityHighScore);
};


typedef SaveDataV1 SaveDataVC;