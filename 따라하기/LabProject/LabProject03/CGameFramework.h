#pragma once
#include "Timer.h"

class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

private:
	int m_nWndClientWidth;
	int m_nWndClientHeight;

private:
	IDXGIFactory4 *m_pdxgiFactory;	// DXGI ���丮 �������̽��� ���� ������.
	IDXGISwapChain3 *m_pdxgiSwapChain;	// ���� ü�� �������̽��� ���� ������. �ַ� ���÷��̸� �����ϱ� ���Ͽ� �ʿ�
	ID3D12Device *m_pd3dDevice;	// Direct3D ����̽� �������̽��� ���� ������. �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ�

private:
	// MSAA ���� ���ø��� Ȱ��ȭ�ϰ� ���� ���ø� ������ �����Ѵ�.
	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;

private:
	static const UINT m_nSwapChainBuffers = 2;	// ���� ü���� �ĸ� ������ ����
	UINT m_nSwapChainBufferIndex;	//���� ����ü���� �ĸ���� �ε���

private:
	ID3D12Resource * m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers]; // ���� Ÿ�� ����
	ID3D12DescriptorHeap *m_pd3dRtvDescriptorHeap;	// ������ �� �������̽� ������
	UINT m_nRtvDescriptorIncrementSize;	// ���� Ÿ�� ������ ������ ũ��

private:
	ID3D12Resource * m_pd3dDepthStencilBuffer;// ����-���ٽ� ����
	ID3D12DescriptorHeap *m_pd3dDsvDescriptorHeap;// ������ �� �������̽� ������
	UINT m_nDsvDescriptorIncrementSize;// ����-���Ľ� ������ ������ ũ��

private:
	ID3D12CommandQueue *m_pd3dCommandQueue;	// ��� ť
	ID3D12CommandAllocator *m_pd3dCommandAllocator;	// ��� �Ҵ���
	ID3D12GraphicsCommandList *m_pd3dCommandList;	// ��� ����Ʈ �������̽� ������

private:
	ID3D12PipelineState *m_pd3dPipelineState;	// �׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� ������

private:
	ID3D12Fence *m_pd3dFence;	// �潺 �������̽� ������
	UINT64 m_nFenceValue;	// �潺�� ��
	HANDLE m_hFenceEvent;	// �̺�Ʈ �ڵ�

private:
#ifdef _DEBUG
	ID3D12Debug *m_pd3dDebugController;

#endif
	D3D12_VIEWPORT m_d3dViewport;	// �� ��Ʈ
	D3D12_RECT m_d3dScissorRect;	// ���� �簢��

private:
	CGameTimer m_GameTimer;	// �����ӿ�ũ���� ����� Ÿ�̸��̴�.
	_TCHAR m_pszFrameRate[50];	// //������ ������ ����Ʈ�� �� �������� ĸ�ǿ� ����ϱ� ���� ���ڿ��̴�.

public:
	CGameFramework();
	~CGameFramework();

public:
	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);	// �����ӿ�ũ�� �ʱ�ȭ�ϴ� �Լ��̴�(�� �����찡 �����Ǹ� ȣ��ȴ�.)
	void OnDestroy();

public:
	void CreateSwapChain();	// ����ü���� �����ϴ� �Լ�
	void CreateDirect3DDevice();	// ����̽��� �����ϴ� �Լ�
	void CreateRtvAndDsvDescriptorHeaps();	// ���������� �����ϴ� �Լ�
	void CreateCommandQueueAndList();	// ��� ť, �Ҵ���, ����Ʈ�� �����ϴ� �Լ�
	void CreateRenderTargetView();
	void CreateDepthStencilView();

public:
	void BuildObjects();	// �������� �޽��� ���� ��ü�� �����ϴ� �Լ�
	void ReleaseObjects();	// �������� �޽��� ���� ��ü�� �Ҹ��ϴ� �Լ�

public:
	// �����ӿ�ũ�� �ٽ�
	void ProcessInput();	// ����� �Է��� �����ϴ� �Լ�
	void AnimateObjects();	// �ִϸ��̼��� �����ϴ� �Լ�
	void FrameAdvance();	// �������� �����ϴ� �Լ�

public:
	void WaitForGpuComplete();	// CPU�� GPU�� ����ȭ �ϴ� �Լ�

public:
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);	// ���콺 �Է� ó�� �Լ�
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);	// Ű���� �Է� ó���Լ�
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);	// �������� �޽��� ó�� �Լ�

};

