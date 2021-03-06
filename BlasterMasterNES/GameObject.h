#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"

using namespace std;

#define ID_TEX_BBOX -100

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx = 0, ny = 0;

	float dx, dy;

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	float nx, ny;
	
	int state;

	DWORD dt;

	LPANIMATION_SET animation_set;

	bool isDelete = false;
	bool isTouthtable = true;


	vector<LPCOLLISIONEVENT> *coEvents=new vector<LPCOLLISIONEVENT>();
	

	int dropItem = -1;
	

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }
	void RenderBoundingBox();
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny,
		float &rdx,
		float &rdy);

	CGameObject();

	CGameObject(const CGameObject& other) {
		*this = other;
	};

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT> *listObj = NULL);
	virtual void Render() {};
	virtual void SetState(int state) { this->state = state; }
	virtual void LastUpdate() {};


	bool IsScopeWith(CGameObject *obj);
	void TinhTam(float &x, float &y);
	float TinhKhoangCach(CGameObject *obj);
	void SetDelete(bool a) { this->isDelete = a; }

	float GetWidth() { float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	return r - l;
	}

	~CGameObject();
};
