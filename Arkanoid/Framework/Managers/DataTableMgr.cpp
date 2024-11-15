#include "stdafx.h"
#include "DataTableMgr.h"
#include "BricksTable.h"
#include "StageTable.h"
DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();
	tables.insert({ DataTable::Types::String ,new StringTable() });
	tables.insert({ DataTable::Types::Bricks ,new BricksTable() });
	tables.insert({ DataTable::Types::Stages ,new StageTable() });
	for (auto t : tables)
	{
		t.second->Load();
	}
}

void DataTableMgr::Release()
{
	for (auto t : tables)
	{
		t.second->Release();
		delete t.second;
	}
	tables.clear();
}
