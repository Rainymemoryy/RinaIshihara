#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"

class CScene
{
protected:
	CKeyEventHandler * key_handler;
	
	int typeScene = -1;
	int nextScene;
	LPCWSTR sceneFilePath;

public:
	CScene(int id, LPCWSTR filePath);
	int id;
	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	void SetTypeScene(int type) {
		typeScene = type;
	}
	int GetTypeScene( ) {
		return typeScene;
	}
	void SetNextScene(int nextScene) {
		this->nextScene = nextScene;
	}
	int GetNextScene() {
		return nextScene;
	}
};
typedef CScene * LPSCENE;

class CScenceKeyHandler : public CKeyEventHandler
{
protected:
	CScene * scence;

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene *s) :CKeyEventHandler() { scence = s; }
};