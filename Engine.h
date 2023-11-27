#pragma once
#include "Renderer.h"
#include "Timer.h"


class Engine {
public:
	Engine();
	~Engine();

private:
	// 윈도우 정보를 담을 구조체
	WINDOWINFORMATION	m_windowInfo{ };

	// 스왑버퍼의 스왑 간격을 조정할 변수 기본은 0 느리게 하려면 큰값을 주면 됨
	int32		m_swapInterver{ };


	/// <summary>
	/// This is Engine's UNIQUE property 
	/// </summary>
	std::unique_ptr<Renderer> m_renderer{ nullptr };

	/// <summary>
	/// This is Engine's UNIQUE property 
	/// </summary>
	std::unique_ptr<Timer> m_timer{ nullptr };



	/// <summary>
	/// This express Engine's Initialize is ready
	/// </summary>
	bool m_ready = false;
public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void Loop();
};


