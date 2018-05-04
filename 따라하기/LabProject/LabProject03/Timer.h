#pragma once

const ULONG MAX_SAMPLE_COUNT = 50; // 50ȸ�� ������ ó���ð��� �����Ͽ� ����Ѵ�.

class CGameTimer
{
public:
	CGameTimer();
	virtual ~CGameTimer();

public:
	void Tick(float);	// Ÿ�̸� �ð��� �����Ѵ�.
	unsigned long GetFrameRate(LPTSTR , int );	// �����ӷ���Ʈ�� ��ȯ�Ѵ�.
	float GetTimeElapsed();	// �������� ��� ��� �ð��� ��ȯ�Ѵ�.

private:
	bool m_bHardwareHasPerformanceCounter;	// ��ǻ�Ͱ� Performance Counter�� ������ �ִ� �� 
	float m_fTimeScale;	// Scale Counter�� �� 
	float m_fTimeElapsed;	// ������ ������ ���� ������ �ð�
	__int64 m_nCurrentTime;	// ������ �ð�
	__int64 m_nLastTime;	// ������ �������� �ð� 
	__int64 m_nPerformanceFrequency;	// ��ǻ���� Performance Frequency

private:
	float m_fFrameTime[MAX_SAMPLE_COUNT];	// ������ �ð��� �����ϱ� ���� �迭 
	ULONG m_nSampleCount;	// ������ ������ Ƚ�� 

private:
	unsigned long m_nCurrentFrameRate;	// ������ ������ ����Ʈ 
	unsigned long m_nFramesPerSecond;	// �ʴ� ������ �� 
	float m_fFPSTimeElapsed;	// ������ ����Ʈ ��� �ҿ� �ð�

};

