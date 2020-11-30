#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Hero.h"
#include "Map.h"

#include "AreaOnMap.h"



class CPlayScene : public CScene
{
protected:
	CHero *player;					
	Map *map;

	unordered_map<int, CAreaOnMap*> listAreaOnMap;
	int indexAreaOnMap = 1;


	vector<LPGAMEOBJECT> *objects= new vector<LPGAMEOBJECT>();
	vector<LPGAMEOBJECT> *curObjects=new vector<LPGAMEOBJECT>();

	float cx = 0, cy = 0;
	float last_cx = 0, last_cy = 0;


	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSeciton_MAP(string line);
	void _ParseSeciton_AreaOnMap(string line);
	

public:
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CHero * GetPlayer() { return player; }
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};