#pragma once
#include"preCompile.h"

//////////싱글톤 패턴으로 구현

class Time
{
private:
	LARGE_INTEGER m_CpuFreq;
	LARGE_INTEGER m_Cur;
	LARGE_INTEGER m_Prev;
	LARGE_INTEGER m_Start, m_Stop;

	float m_fElapsed;

public:
	const float& Update(){
		QueryPerformanceCounter(&m_Cur);
		m_fElapsed = float(m_Cur.QuadPart - m_Prev.QuadPart) / (float)m_CpuFreq.QuadPart; // Cpu클럭 비교로 시간 계산

		m_Prev = m_Cur;
		return m_fElapsed;
	}

private:
	unsigned int		m_FpsCnt;
	float				m_FpsTime;
	unsigned int		m_FPS;
	float				kk;

public:
	const unsigned int	checkFPS(){
		++m_FpsCnt;
		m_FpsTime += m_fElapsed;

		if (m_FpsTime >= 1.0f){
			m_FPS = m_FpsCnt;
			m_FpsTime = 0.f;
			m_FpsCnt = 0;
			return m_FPS;
		}

		return 0;
	}

	void Start(){
		QueryPerformanceCounter(&m_Start);
	}

	float Stop(){
		QueryPerformanceCounter(&m_Stop);
		return (float)(m_Stop.QuadPart - m_Start.QuadPart) / m_CpuFreq.QuadPart;
	}


	const bool spf(){
		kk += m_fElapsed;

		if (kk >= 0.1f){
			kk = 0.f;
			return TRUE;
		}

		return 0;
	}

private:
	static Time* myInstance;
	Time(){
		QueryPerformanceFrequency(&m_CpuFreq);
		QueryPerformanceCounter(&m_Prev);
		m_fElapsed = 0.f;
		m_FpsTime = 0.f;
		m_FpsCnt = 0.f;
		kk = 0.f;
	}
	~Time(){}


public:
	static Time* getInstance(){
		if (!myInstance)
			myInstance = new Time();

		return myInstance;
	}

	static void Release(){
		delete myInstance;
		myInstance = NULL;
	}
};

