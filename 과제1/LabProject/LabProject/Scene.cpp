#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'Z':	// 오브젝트 전체 폭발
		{
			for (int i = 0; i < m_nObjects; i++)
			{
				CExplosiveObject *pExplosiveObject = (CExplosiveObject *)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
			}
			break;
		}
		case '1':	// 오브젝트 추가
		{
			CCubeMesh * pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
			pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

			m_nObjects += 1;

			m_ppObjects[m_nObjects - 1] = new CExplosiveObject();
			m_ppObjects[m_nObjects - 1]->SetMesh(pObjectCubeMesh);
			m_ppObjects[m_nObjects - 1]->SetColor(RGB(255, 0, 0));
			m_ppObjects[m_nObjects - 1]->SetPosition(-13.5f, 0.0f, -14.0f);
			m_ppObjects[m_nObjects - 1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
			m_ppObjects[m_nObjects - 1]->SetRotationSpeed(90.0f);
			m_ppObjects[m_nObjects - 1]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
			m_ppObjects[m_nObjects - 1]->SetMovingSpeed(10.5f);
			break;
		}
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	// 벽 생성
	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 100.0f;
	int iSubRects = 15;
	CWallMesh *pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, iSubRects);
	pWallCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pWallsObject = new CWallsObject*[5];
	
	for (int i = 0; i < 5; ++i) {
		m_pWallsObject[i] = new CWallsObject();
		m_pWallsObject[i]->SetPosition(0.0f, 0.0f, 200.0f * i + 80);
		m_pWallsObject[i]->SetMesh(pWallCubeMesh);
		m_pWallsObject[i]->SetColor(RGB(127.5, 0, 127.5));
		m_pWallsObject[i]->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
		m_pWallsObject[i]->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
		m_pWallsObject[i]->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
		m_pWallsObject[i]->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
		m_pWallsObject[i]->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
		m_pWallsObject[i]->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);
	}

	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 10;
	m_ppObjects = new CGameObject*[m_nObjects];

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pObjectCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 0.0f, -14.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[0]->SetRotationSpeed(90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pObjectCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, 0.0f, -14.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(180.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);

	m_ppObjects[2] = new CExplosiveObject();
	m_ppObjects[2]->SetMesh(pObjectCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, +5.0f, 20.0f);
	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[2]->SetRotationSpeed(30.15f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);

	m_ppObjects[3] = new CExplosiveObject();
	m_ppObjects[3]->SetMesh(pObjectCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[3]->SetRotationSpeed(40.6f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);

	m_ppObjects[4] = new CExplosiveObject();
	m_ppObjects[4]->SetMesh(pObjectCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 0.0f, 0.0f);
	m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[4]->SetRotationSpeed(50.06f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);

	m_ppObjects[5] = new CExplosiveObject();
	m_ppObjects[5]->SetMesh(pObjectCubeMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[5]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[5]->SetRotationSpeed(60.06f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);

	m_ppObjects[6] = new CExplosiveObject();
	m_ppObjects[6]->SetMesh(pObjectCubeMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, 10.0f, -10.0f);
	m_ppObjects[6]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[6]->SetRotationSpeed(60.06f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 1.0f));
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = new CExplosiveObject();
	m_ppObjects[7]->SetMesh(pObjectCubeMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, 10.0f, -20.0f);
	m_ppObjects[7]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[7]->SetRotationSpeed(70.06f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 1.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);

	m_ppObjects[8] = new CExplosiveObject();
	m_ppObjects[8]->SetMesh(pObjectCubeMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, 10.0f, -30.0f);
	m_ppObjects[8]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[8]->SetRotationSpeed(90.06f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);

	m_ppObjects[9] = new CExplosiveObject();
	m_ppObjects[9]->SetMesh(pObjectCubeMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, 10.0f, 0.0f);
	m_ppObjects[9]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[9]->SetRotationSpeed(90.06f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
	m_ppObjects[9]->SetMovingSpeed(15.0f);
}

void CScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++)
		if (m_ppObjects[i]) delete m_ppObjects[i];

	if (m_ppObjects) delete[] m_ppObjects;

	if (m_pWallsObject) delete m_pWallsObject;
}

void CScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

void CScene::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		// 개체가 개체를 포함하고 있는지( DISJOINT = 0, INTERSECTS = 1, CONTAINS = 2)
		ContainmentType containType = m_pWallsObject[0]->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				// 객체가 평면과 교차하는지 여부( FRONT = 0, INTERSECTING = 1, BACK = 2)
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject[0]->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject[0]->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject[0]->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject[0]->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject[0]->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject[0]->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject[0]->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject[0]->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
}

void CScene::CheckBulletByObjectCollisions()
{

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;


	for (int i = 0; i < m_nObjects; i++)
	{
		auto iter_begin = m_pPlayer->m_plistBullet.begin();
		auto iter_end = m_pPlayer->m_plistBullet.end();

		for (; iter_begin != iter_end;)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects((*iter_begin)->m_xmOOBB) && dynamic_cast<CExplosiveObject*>(m_ppObjects[i])->m_bBlowingUp != true)
			{
				dynamic_cast<CExplosiveObject*>(m_ppObjects[i])->m_bBlowingUp = true;
				delete *iter_begin;
				iter_begin = m_pPlayer->m_plistBullet.erase(iter_begin);
			}
			else {
				++iter_begin;
			}
		}
	}
}

void CScene::CheckBulletByWallCollisions()
{
	auto iter_begin = m_pPlayer->m_plistBullet.begin();
	auto iter_end = m_pPlayer->m_plistBullet.end();

	for (int i = 0; i < 5; ++i) {
		for (; iter_begin != iter_end; )
		{
			// 개체가 개체를 포함하고 있는지( DISJOINT = 0, INTERSECTS = 1, CONTAINS = 2)
			if ((200.0f * i <= m_pPlayer->GetPosition().z + 100 && m_pPlayer->GetPosition().z + 100 <= 200.0f * (i + 1)) ||
				(200.0f * i <= m_pPlayer->GetPosition().z - 100 && m_pPlayer->GetPosition().z - 100 <= 200.0f * (i + 1))) {
				ContainmentType containType = m_pWallsObject[i]->m_xmOOBB.Contains((*iter_begin)->m_xmOOBB);
				switch (containType)
				{
				case DISJOINT:
				{
					int nPlaneIndex = -1;
					for (int j = 1; j < 5; j++)
					{
						// 객체가 평면과 교차하는지 여부( FRONT = 0, INTERSECTING = 1, BACK = 2)
						PlaneIntersectionType intersectType = (*iter_begin)->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject[i]->m_pxmf4WallPlanes[j]));
						if (intersectType == BACK)
						{
							nPlaneIndex = j;
							break;
						}
					}
					if (nPlaneIndex != -1)
					{
						delete *iter_begin;
						iter_begin = m_pPlayer->m_plistBullet.erase(iter_begin);
					}
					else {
						++iter_begin;
					}
					break;
				}
				case INTERSECTS:
				{
					int nPlaneIndex = -1;
					for (int j = 1; j < 5; j++)
					{
						PlaneIntersectionType intersectType = (*iter_begin)->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject[i]->m_pxmf4WallPlanes[j]));
						if (intersectType == INTERSECTING)
						{
							nPlaneIndex = j;
							break;
						}
					}
					if (nPlaneIndex != -1)
					{
						delete *iter_begin;
						iter_begin = m_pPlayer->m_plistBullet.erase(iter_begin);
					}
					else {
						++iter_begin;
					}
					break;
				}
				case CONTAINS:
					break;
				}
			}
		}
	}
}

void CScene::Animate(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime); 

	CheckObjectByWallCollisions();

	CheckObjectByObjectCollisions();

	CheckBulletByObjectCollisions();

	CheckBulletByWallCollisions();
}

void CScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	for (int i = 0; i < 5; ++i) {
		if((200.0f * i <= m_pPlayer->GetPosition().z + 100 && m_pPlayer->GetPosition().z + 100 <= 200.0f * (i + 1)) || 
			(200.0f * i <= m_pPlayer->GetPosition().z - 100 && m_pPlayer->GetPosition().z - 100 <= 200.0f * (i + 1)))
			m_pWallsObject[i]->Render(hDCFrameBuffer, pCamera);
	}
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

}
