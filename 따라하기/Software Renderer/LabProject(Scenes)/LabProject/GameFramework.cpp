//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"

CGameFramework::CGameFramework()
{
	_tcscpy_s(m_pszFrameRate, _T("LabProject ("));
}

CGameFramework::~CGameFramework()
{
}

bool CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
    ::srand(timeGetTime());

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	BuildFrameBuffer(); 

	BuildObjects(); 

	return(true);
}

void CGameFramework::BuildFrameBuffer()
{
    HDC hDC = ::GetDC(m_hWnd);

	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);

    m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, (rcClient.right - rcClient.left) + 1, (rcClient.bottom - rcClient.top) + 1);
    ::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
    ::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
    HBRUSH hBrush = ::CreateSolidBrush(dwColor);
    HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	::Rectangle(m_hDCFrameBuffer, m_pPlayer->m_pCamera->m_Viewport.m_xStart, m_pPlayer->m_pCamera->m_Viewport.m_yStart, m_pPlayer->m_pCamera->m_Viewport.m_nWidth, m_pPlayer->m_pCamera->m_Viewport.m_nHeight);
    ::SelectObject(m_hDCFrameBuffer, hOldBrush);
    ::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{    
    HDC hDC = ::GetDC(m_hWnd);
    ::BitBlt(hDC, m_pPlayer->m_pCamera->m_Viewport.m_xStart, m_pPlayer->m_pCamera->m_Viewport.m_yStart, m_pPlayer->m_pCamera->m_Viewport.m_nWidth, m_pPlayer->m_pCamera->m_Viewport.m_nHeight, m_hDCFrameBuffer, m_pPlayer->m_pCamera->m_Viewport.m_xStart, m_pPlayer->m_pCamera->m_Viewport.m_yStart, SRCCOPY);
    ::ReleaseDC(m_hWnd, hDC);
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			::SetCapture(hWnd);
			::GetCursorPos(&m_ptOldCursorPos);
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
			::ReleaseCapture();
			break;
		case WM_MOUSEMOVE:
			break;
		default:
			break;
	}
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					::PostQuitMessage(0);
					break;
				case 'S':
				{
					if (m_pScene)
					{
						m_pScene->ReleaseObjects();
						delete m_pScene;
					}
					m_nScene = (m_nScene + 1) % m_nScenes;
					switch (m_nScene)
					{
						case 0: 
							m_pScene = new CPlayerScene(); 
							break;
						case 1: 
							m_pScene = new CCollisionScene(); 
							break;
						case 2: 
							m_pScene = new CExplosionScene(); 
							break;
						case 3: 
							m_pScene = new CRunAwayScene(); 	
							break;
					}

					if (m_pPlayer) delete m_pPlayer;
					if (m_nScene == 3)
					{
						CCubeMesh *pCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
						m_pPlayer = new CTerrainPlayer();
						m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
						m_pPlayer->SetMesh(pCubeMesh);
						m_pPlayer->SetColor(RGB(255, 0, 0));
						m_pPlayer->SetMesh(pCubeMesh);
						m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 50.0f, -35.0f));
					}
					else
					{
						CAirplaneMesh *pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);
						m_pPlayer = new CAirplanePlayer();
						m_pPlayer->SetPosition(0.0f, 0.0f, -30.0f);
						m_pPlayer->SetMesh(pAirplaneMesh);
						m_pPlayer->SetColor(RGB(0, 0, 255));
						m_pPlayer->SetMesh(pAirplaneMesh);
						m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));
					}

					m_pScene->m_pPlayer = m_pPlayer;

					m_pScene->BuildObjects();
					break;
				}
				default:
					m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
					break;
			}
			break;
		default:
			break;
	}
}

LRESULT CALLBACK CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_INACTIVE)
				m_GameTimer.Stop();
			else
				m_GameTimer.Start();
			break;
		}
		case WM_SIZE:
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:
			OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
			OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
			break;
		}
		return(0);
}

void CGameFramework::BuildObjects()
{
	CAirplaneMesh *pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);
	m_pPlayer = new CAirplanePlayer();
	m_pPlayer->SetPosition(0.0f, 0.0f, -30.0f);
	m_pPlayer->SetMesh(pAirplaneMesh);
	m_pPlayer->SetColor(RGB(0, 0, 255));
	m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));

	m_nScenes = 4;

	m_nScene = 0;
	m_pScene = new CPlayerScene();
	m_pScene->BuildObjects();

	m_pScene->m_pPlayer = m_pPlayer;
}

void CGameFramework::ReleaseObjects()
{
	if (m_pScene)
	{
		m_pScene->ReleaseObjects();
		delete m_pScene;
	}

	if (m_pPlayer) delete m_pPlayer;
}

void CGameFramework::OnDestroy()
{
	ReleaseObjects();

	if (m_hBitmapFrameBuffer) ::DeleteObject(m_hBitmapFrameBuffer);
    if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);

    if (m_hWnd) DestroyWindow(m_hWnd);
}

void CGameFramework::ProcessInput()
{
	static UCHAR pKeyBuffer[256];
	DWORD dwDirection = 0;
	if (GetKeyboardState(pKeyBuffer))
	{
		if (pKeyBuffer[VK_UP] & 0xF0) dwDirection |= DIR_FORWARD;
		if (pKeyBuffer[VK_DOWN] & 0xF0) dwDirection |= DIR_BACKWARD;
		if (pKeyBuffer[VK_LEFT] & 0xF0) dwDirection |= DIR_LEFT;
		if (pKeyBuffer[VK_RIGHT] & 0xF0) dwDirection |= DIR_RIGHT;
		if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
		if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;
	}
	float cxDelta = 0.0f, cyDelta = 0.0f;
	POINT ptCursorPos;
	if (GetCapture() == m_hWnd)
	{
		SetCursor(NULL);
		GetCursorPos(&ptCursorPos);
		cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
	}
	if ((dwDirection != 0) || (cxDelta != 0.0f) || (cyDelta != 0.0f))
	{
		if (cxDelta || cyDelta)
		{
			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
				m_pPlayer->Rotate(cyDelta, 0.0f, -cxDelta);
			else
				m_pPlayer->Rotate(cyDelta, cxDelta, 0.0f);
		}
		if (dwDirection) m_pPlayer->Move(dwDirection, 0.15f);
	}
	m_pPlayer->Update(m_GameTimer.GetTimeElapsed());
}

void CGameFramework::FrameAdvance()
{    
    if (!m_bActive) return;

	m_GameTimer.Tick(0.0f);

	ProcessInput();

	m_pScene->Animate(m_GameTimer.GetTimeElapsed());

	ClearFrameBuffer(RGB(255, 255, 255));

	m_pScene->Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);
	m_pPlayer->Render(m_hDCFrameBuffer, m_pPlayer->m_pCamera);

	PresentFrameBuffer();

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37);
	::SetWindowText(m_hWnd, m_pszFrameRate);
}


