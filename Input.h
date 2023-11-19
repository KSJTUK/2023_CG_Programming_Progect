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
	PRESSED,


	/// <summary>
	///  released on time  
	/// </summary>
	RELEASED


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
	float2 m_delteMouse{};

	static Input* InputInstance;


public:


	static Input* GetInstance(GLFWwindow* window);
	static Input* GetInstance();



	void Update();


	const KEY_STATE Getkey(int key);



};

