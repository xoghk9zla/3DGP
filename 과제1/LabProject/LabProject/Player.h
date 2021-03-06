#pragma once

#include "GameObject.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

	XMFLOAT3					m_xmf3Position;
	XMFLOAT3					m_xmf3Right;	// 플레이어의 Right 벡터
	XMFLOAT3					m_xmf3Up;		// 플레이어의 UP 벡터
	XMFLOAT3					m_xmf3Look;		// 플레이어의 LOOK 벡터

	XMFLOAT3					m_xmf3CameraOffset;
	XMFLOAT3					m_xmf3Velocity;
	float						m_fFriction = 125.0f;

	float           			m_fPitch = 0.0f;
	float           			m_fYaw = 0.0f;
	float           			m_fRoll = 0.0f;

	CCamera						*m_pCamera = NULL;

	list<CGameObject*>		m_plistBullet;

	void SetPosition(float x, float y, float z);
	void Move(DWORD dwDirection, float fDistance);
	void Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity);
	void Move(float x, float y, float z);
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
	void SetCameraOffset(XMFLOAT3& xmf3CameraOffset);
	void Update(float fTimeElapsed=0.016f);

	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);
};

class CAirplanePlayer : public CPlayer
{
public:
	CAirplanePlayer();
	virtual ~CAirplanePlayer();
};

class CTerrainPlayer : public CPlayer
{
public:
	CTerrainPlayer();
	virtual ~CTerrainPlayer();
};
