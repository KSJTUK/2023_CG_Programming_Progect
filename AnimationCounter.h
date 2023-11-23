#pragma once
class AnimationCounter {
public:
	AnimationCounter() = default;


private:


	std::vector<KeyFrame> m_keyframes{};


	glm::mat4 m_rotateAnimationBuffer{};
	glm::mat4 m_translateAnimationBuffer{};

	float m_interpolationParameter{};
	int m_frame{};
	int m_animationdir = 1;

public:
	void RegisterMyFrame(const KeyFrame& newframe) { m_keyframes.push_back(newframe); };

	void Update(float DeltaTime);
	glm::mat4 GetRotateAnimation() { return m_rotateAnimationBuffer; };
	glm::mat4 GetTranslateAnimation() { return m_translateAnimationBuffer; };
	

};

