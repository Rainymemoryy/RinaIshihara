#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"

#include "Portal.h"
#include "GameObject.h"


#include "Brick.h"
#include "Brick1.h"
#include "Brick2.h"
#include "Stair.h"

#include "Enemy1.h"
#include "Enemy2.h"



#include "Item.h"
#include "ItemHp.h"


#define AreaOnMap_UnKnown	0
#define AreaOnMap_LoadInfo	1
#define AreaOnMap_LoadObj	2


#define AreaOnMap_Type_BrickDf	0
#define AreaOnMap_Type_Brick1	1
#define AreaOnMap_Type_Brick2	2
#define AreaOnMap_Type_Stair	3

#define AreaOnMap_Type_Portal	20

#define AreaOnMap_Type_Enemy1	101
#define AreaOnMap_Type_Enemy2	102
#define AreaOnMap_Type_Enemy3	103
#define AreaOnMap_Type_Enemy4	104
#define AreaOnMap_Type_Enemy5	105
#define AreaOnMap_Type_Enemy6	106

#define AreaOnMap_Type_ItemHP	201



//typedef CAreaOnMap * LPAreaOnMap;

class CAreaOnMap
{
protected:
	int id;
	float map_t, map_l, map_r, map_b;
	bool isReload = false;
	LPCWSTR sceneFilePath;

	vector<LPGAMEOBJECT> *listObj;

public:
	CAreaOnMap(int id,LPCWSTR sceneFilePath)
	{
		this->id = id;
		this->sceneFilePath = sceneFilePath;
	}

	void GetAreaOnMap_Load() {
		listObj = new vector<LPGAMEOBJECT>();
		ifstream f;
		f.open(sceneFilePath);
		int section = AreaOnMap_UnKnown;
		char str[1024];

		while (f.getline(str, 1024))
		{
			string line(str);

			if (line[0] == '#') continue;
			if (line == "[INFO]") { section = AreaOnMap_LoadInfo; continue; }
			if (line == "[OBJECTS]") { section = AreaOnMap_LoadObj; continue; }
			if (line[0] == '[') { section = AreaOnMap_UnKnown; continue; }

			switch (section)
			{
			case AreaOnMap_LoadInfo: _ParseSection_Info(line); break;
			case AreaOnMap_LoadObj: _ParseSection_Objects(line); break;
			}
		}

		f.close();

		DebugOut(L"id: %d\t\tfile: %s\t\t\size :%d\n",id ,sceneFilePath, listObj->size());
	}

	void _ParseSection_Info(string line) {
		vector<string> tokens = split(line);
		map_l = atof(tokens[0].c_str());
		map_t = atof(tokens[1].c_str());
		map_r = atof(tokens[2].c_str());
		map_b = atof(tokens[3].c_str());
	}
	void _ParseSection_Objects(string line) {

		vector<string> tokens = split(line);
		if (tokens.size() < 3) return;

		int object_type = atoi(tokens[0].c_str());

		CGameObject *obj = NULL;
		switch (object_type)
		{
		case AreaOnMap_Type_BrickDf:
			obj = new CBrick(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			break;
		case AreaOnMap_Type_Brick1:
			obj = new CBrick1(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			break;
		case AreaOnMap_Type_Brick2:
			obj = new CBrick2(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			break;
		case AreaOnMap_Type_Stair:
			obj = new CStair(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16);
			break;


		case AreaOnMap_Type_ItemHP:
			obj = new CItemHp(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			break;



		case AreaOnMap_Type_Enemy1:
			obj = new CEnemy1(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			break;
		case AreaOnMap_Type_Enemy2:
			obj = new CEnemy2(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16);
			break;



		case AreaOnMap_Type_Portal:
			obj = new CPortal(atof(tokens[1].c_str()) * 16, atof(tokens[2].c_str()) * 16, atof(tokens[3].c_str()) * 16, atof(tokens[4].c_str()) * 16, atoi(tokens[5].c_str()), atof(tokens[6].c_str()) * 16, atof(tokens[7].c_str()) * 16);
			break;
		}
		listObj->push_back(obj);
	}

	float GetAreaOnMap_Right() { return map_r*16; }
	float GetAreaOnMap_Bottom() { return map_b*16; }
	float GetAreaOnMap_X() { return map_l*16; }
	float GetAreaOnMap_Y() { return map_t*16; }


	vector<LPGAMEOBJECT> * GetAreaOnMap_ListObj() {
		return listObj;
	}


	~CAreaOnMap() {
		for (int i = 0; i < listObj->size(); i++)
			delete listObj->at(i);
		listObj->clear();
	};


};

