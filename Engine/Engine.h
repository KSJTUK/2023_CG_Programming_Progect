#ifndef _ENGINE_H
#define _ENGINE_H

class Engine {
public:
	Engine();
	~Engine();

private:
	WINDOWINFO m_windowInfo{ };

public:
	void Init();
	void Update();
	void Render();

	void Loop();
};

#endif