#pragma once
enum class KEY_STATE{

	/// <summary>
	///  nothing state 
	/// </summary>
	NONE,

	/// <summary>
	///  pressed on time 
	/// </summary>
	DOWN,


	/// <summary>
	///  pressing during time 
	/// </summary>
	PRESS,


	/// <summary>
	///  released on time  
	/// </summary>
	RELEASE


};


class Input{
private:
	Input() = default;
	Input(const Input& other) = delete;
	~Input() = delete;
	Input& operator=(const Input& other) = delete;

private:

	GLFWwindow* m_window{ nullptr };

	KEY_STATE* m_keyboard_State{ nullptr };


	float2 m_prevMouse{};
	float2 m_deltaMouse{};

	static Input* InputInstance;


public:


	static Input* GetInstance();

	void Init(GLFWwindow* window);


	void Update();


	const KEY_STATE GetKey(int key);
	const float2 GetDeltaMouse() { return m_deltaMouse; };


};

