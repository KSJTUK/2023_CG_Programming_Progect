#include "pch.h"
#include "AnimationCounter.h"

void AnimationCounter::Update(float DeltaTime){



	// if t is more than 1
	if (m_interpolationParameter > 1.0) {
		

		// if animation direction is forward
		if (m_animationdir == 1) {

			if (m_frame == m_keyframes.size() - 2) {
				m_animationdir = -1;
				m_frame += 1;
			}
			else {
				m_frame += m_animationdir;
			}
			

		}
		// if animation direction is reversial
		else if (m_animationdir == -1) {

			if (m_frame == 1) {
				m_animationdir = 1;
				m_frame -= 1;
			}
			else {
				m_frame += m_animationdir;
			}


		}
		else {
			std::cerr << "Animation Counter : Animation Direction should be 1 or -1" << std::endl;
			exit(EXIT_FAILURE);
		}



		m_interpolationParameter = 0.f;

	}

	
	// 기본적인 사원수 애니매이팅은 이 두 줄의 코드로 진행됨
	// 1. 먼저 현재 키프레임과, 다음 키프레임의 쿼터니언을 가져와, 두 쿼터니언을 t 기준으로 선형 보간한다 
	// 2. 그 결과로 나온 쿼터니언을 회전행렬로 변환하여 렌더링 파트로 전달한다. ( 통상 업데이트 이후, 렌더링이 진행되므로, 바로 이 값을 사용할 것이다 ) 
	glm::vec3 InterpolatedPoint{glm::lerp(m_keyframes[m_frame].movement,m_keyframes[m_frame + m_animationdir].movement,m_interpolationParameter)};
	glm::quat InterpolatedQuaternion{glm::slerp(m_keyframes[m_frame].rotation,m_keyframes[m_frame + m_animationdir].rotation,m_interpolationParameter)};


	m_rotateAnimationBuffer = glm::mat4_cast(InterpolatedQuaternion);
	m_translateAnimationBuffer = glm::translate(InterpolatedPoint);

	m_interpolationParameter += m_keyframes[m_frame].angle_unit;
}


/*

0->1 
1->2
2->1
1->0
0->1



*/