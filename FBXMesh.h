#pragma once


#define SUCCESS(param) if(param == NULL or param == false or param < 0) abort()


class ModelUtility
{
public:
	static glm::vec2 ToVector2(const FbxVector2& vec)
	{
		return glm::vec2((float)vec.mData[0], (float)vec.mData[1]);
	}

	static glm::vec3 ToVector3(const FbxVector4& vec)
	{
		return glm::vec3((float)vec.mData[0], (float)vec.mData[1], (float)vec.mData[2]);
	}

	static glm::vec4 ToColor(const FbxVector4& vec)
	{
		return glm::vec4((float)vec.mData[0], (float)vec.mData[1], (float)vec.mData[2], 1);
	}

	static glm::vec2 ToUv(const FbxVector2& vec)
	{
		glm::vec2 temp = ToVector2(vec);

		return glm::vec2(temp.x, 1.0f - temp.y);
	}

	static glm::mat4 ToMatrix(const FbxAMatrix& matrix)
	{
		FbxVector4 r1 = matrix.GetRow(0);
		FbxVector4 r2 = matrix.GetRow(1);
		FbxVector4 r3 = matrix.GetRow(2);
		FbxVector4 r4 = matrix.GetRow(3);

		return glm::mat4
		(
			(float)r1.mData[0], (float)r1.mData[1], (float)r1.mData[2], (float)r1.mData[3],
			(float)r2.mData[0], (float)r2.mData[1], (float)r2.mData[2], (float)r2.mData[3],
			(float)r3.mData[0], (float)r3.mData[1], (float)r3.mData[2], (float)r3.mData[3],
			(float)r4.mData[0], (float)r4.mData[1], (float)r4.mData[2], (float)r4.mData[3]
		);
	}
};




namespace FBX {
	
	enum class AnimationMode
	{
		Play = 0, Pause, Stop,
	};

	class Model;
	class ModelAnimationController;
	class ModelBuffer;

	class ModelAnimation
	{
	public:
		ModelAnimation(std::wstring name, int keyFrame, float defaultFrameRate);
		~ModelAnimation();

		std::wstring GetName() { return name; }
		int GetKeyFrames() { return keyFrame; }

		float GetFrameRate() { return frameRate; }
		void SetFrameRate(float frameRate) { frameRate = frameRate; }

		float GetDefaultFrameRate() { return defaultFrameRate; }

		void ResetFrameRate() { frameRate = defaultFrameRate; }

	private:
		std::wstring name;

		int keyFrame;
		float frameRate;
		float defaultFrameRate;
	};


	class ModelAnimationController
	{
	public:
		ModelAnimationController();
		~ModelAnimationController();

		void AddAnimation(ModelAnimation* animation);

		ModelAnimation* GetCurrentAnimation();
		void SetCurrentAnimation(std::wstring animationName);
		void SetCurrentAnimation(int index);

		UINT GetAnimationCount();
		ModelAnimation* GetAnimation(int index);

		void Play();
		void Pause();
		void Stop();

		int GetCurrentKeyFrame() { return currentKeyFrame; }
		void SetCurrentKeyFrame(int keyFrame);

		int GetNextKeyFrame() { return nextKeyFrame; }
		float GetKeyFrameFactor() { return keyFrameFactor; }

		AnimationMode GetAnimationMode() { return animationMode; }

		void UseQuaternionKeyFrames(bool use) { useQuaternionKeyFrames = use; }
		bool UseQuaternionKeyFrames() { return useQuaternionKeyFrames; }

		void Update();

	private:
		AnimationMode animationMode;
		ModelAnimation* currentAnimation;

		typedef std::pair<std::wstring, ModelAnimation*> Pair;
		std::vector<Pair> animations;

		float frameTimer;

		int currentKeyFrame;
		int nextKeyFrame;
		float keyFrameFactor;
		bool useQuaternionKeyFrames;
	};




	class ModelAnimationQuaternionKeyFrame
	{
	public:
		ModelAnimationQuaternionKeyFrame(const glm::mat4& transform)
		{

			q = glm::quat_cast(transform);
			translation = glm::vec3{ transform[4][1],transform[4][2],transform[4][3] };
		}

		const glm::quat& GetQuaternion() const { return q; }
		const glm::vec3& GetTranslation() const { return translation; }

	private:
		glm::quat q;
		glm::vec3 translation;
	};

	class ModelAnimationKeyFrames
	{
	public:
		ModelAnimationKeyFrames(std::wstring animationName);
		~ModelAnimationKeyFrames();

		void AddKeyFrame(const glm::mat4& transform);

		std::wstring GetAnimationName();
		const glm::mat4 &GetKeyFrameTransform(int keyFrame) const;
		const ModelAnimationQuaternionKeyFrame& GetQuaternionKeyFrame(int keyFrame) const;

	private:
		std::wstring animationName;

		typedef std::pair<glm::mat4, ModelAnimationQuaternionKeyFrame> Pair;
		std::vector<Pair> keyFrames;
	};


	class ModelSkeletonBone
	{
	public:
		ModelSkeletonBone(std::wstring name, int parentBoneIndex);
		~ModelSkeletonBone();

		void AddAnimationKeyFrames(ModelAnimationKeyFrames* keyFrames);

		void SetBindPoseTransform(const glm::mat4& matBindPoseTransform);
		void SetBoneReferenceTransform(const glm::mat4& matBoneReferenceTransform);

		ModelAnimationKeyFrames* GetAnimationKeyFrames(std::wstring animationName);

		const glm::mat4& GetBindPoseTransform()
		{
			return matBindPoseTransform;
		}

		const glm::mat4& GetInvBindPoseTransform()
		{
			return matInvBindPoseTransform;
		}

		const glm::mat4& GetBoneReferenceTransform()
		{
			return matBoneReferenceTransform;
		}

		const glm::mat4& GetInvBoneReferenceTransform()
		{
			return matInvBoneReferenceTransform;
		}

		std::wstring GetName() { return name; }
		int GetParentBoneIndex() { return parentBoneIndex; }

	private:
		typedef std::pair<std::wstring, ModelAnimationKeyFrames*> Pair;

		std::wstring name;

		glm::mat4 matBindPoseTransform;
		glm::mat4 matInvBindPoseTransform;
		glm::mat4 matBoneReferenceTransform;
		glm::mat4 matInvBoneReferenceTransform;

		int parentBoneIndex;

		std::vector<std::pair<std::wstring, ModelAnimationKeyFrames*>> animationKeyFrames;
	};


	class ModelSkeleton
	{
	public:
		ModelSkeleton();
		~ModelSkeleton();

		void AddSkeletonBone(ModelSkeletonBone* skeletonBone);
		ModelSkeletonBone* FindBone(std::wstring boneName);
		int FindBoneIndex(std::wstring boneName);

		ModelSkeletonBone* GetSkeletonBone(int index);
		const std::vector<std::pair<std::wstring, ModelSkeletonBone*>>& GetSkeletonBones()
		{
			return skeletonBones;
		}

		glm::mat4* GetSkinTransforms()
		{
			return skinTransforms;
		}

		int GetBoneCount() { return boneCount; }

		void UpdateAnimation(ModelAnimationController* animationController, bool isRootBoneLock);

	private:
		void BuildBoneTransforms(ModelAnimationController* animationController, std::wstring animationName, bool isRootBoneLock);

		typedef std::pair<std::wstring, ModelSkeletonBone*> Pair;
		std::vector<Pair> skeletonBones;



		glm::mat4* skinTransforms;
		glm::mat4* boneAnimationTransforms;

		int boneCount;

	public:
		glm::mat4 GetMatrixByBoneIndex(int index);
	};







	struct ModelBlendWeights
	{
		glm::vec4 BlendIndices;
		glm::vec4 BlendWeights;

		ModelBlendWeights()
		{
			BlendIndices = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			BlendWeights = glm::vec4 (0.0f, 0.0f, 0.0f, 0.0f);
		}

		void SetBlendWeight(int nIndex, int nBoneIndex, float fWeight)
		{
			switch (nIndex)
			{
			case 0:
				BlendIndices.x = (float)nBoneIndex;
				BlendWeights.x = fWeight;
				break;
			case 1:
				BlendIndices.y = (float)nBoneIndex;
				BlendWeights.y = fWeight;
				break;
			case 2:
				BlendIndices.z = (float)nBoneIndex;
				BlendWeights.z = fWeight;
				break;
			case 3:
				BlendIndices.w = (float)nBoneIndex;
				BlendWeights.w = fWeight;
				break;
			}
		}
	};


	class ModelBoneWeights
	{
	public:
		ModelBoneWeights();
		~ModelBoneWeights();

		static const UINT MaxBonesPerVertex;
		static const UINT MaxBonesPerMax;

		void AddBoneWeight(int boneIndex, float boneWeight);
		void AddBoneWeight(std::pair<int, float> boneWeightPair);
		void AddBoneWeights(const ModelBoneWeights& boneWeights);

		void Validate();
		void Normalize();

		int GetBoneWeightCount() const { return boneWeights.size(); }
		std::pair<int, float> GetBoneWeight(int index) const { return boneWeights[index]; }
		ModelBlendWeights GetBlendWeights();

	private:
		float sumWeight;

		std::vector<std::pair<int, float>> boneWeights;
	};


	class ModelPart;

	class Model
	{
	public:
		Model(std::wstring name, ModelBuffer* modelBuffer);
		~Model();

		void Update(bool isAnimation);
		void UpdateAnimation(ModelAnimationController* animationController);
		void Render();

		std::wstring GetName() { return name; }

		void AddAnimationKeyFrames(ModelAnimationKeyFrames* animationKeyFrames);
		ModelAnimationKeyFrames* GetAnimationKeyFrames(std::wstring animationName);

		void SetGeometricOffset(const glm::mat4& matGeometricOffset)
		{
			this->matGeometricOffset = matGeometricOffset;
		}

		glm::mat4 GetGeometricOffset()
		{
			return matGeometricOffset;
		}

		glm::mat4 GetAnimationTransform()
		{
			return matAnimationTransform;
		}

		void SetAbsoluteTransform(const glm::mat4& matAbsoluteTransform)
		{
			this->matAnimationTransform = matAbsoluteTransform;
		}

		void AddVertex(glm::vec3 position, glm::vec3 normal, glm::vec3 uv, const ModelBoneWeights& boneWeights);
		void CreateBuffer();

		void SetWorldTransform(glm::mat4& world);

	private:
		std::wstring name;

		//D3DXMATRIX absoluteTransform;
		glm::mat4 matGeometricOffset;
		glm::mat4 matAnimationTransform;

		std::vector<ModelPart*> parts;

		ModelBuffer* modelBuffer;

		typedef std::pair<std::wstring, ModelAnimationKeyFrames*> Pair;
		std::vector<Pair> animationKeyFrames;
	};



	class ModelScene {
	public:

		ModelScene(std::string path);
		~ModelScene();




		void Update();
		void Render();


	private:

		void LoadScene(std::string path);
		void ProcessScene();
		void ProcessNode(fbxsdk::FbxNode* Node,fbxsdk::FbxNodeAttribute::EType attrib);
		void ProcessMesh(fbxsdk::FbxNode* Node);
		void ProcessBoneWeights(fbxsdk::FbxMesh* Mesh, std::vector<ModelBoneWeights>& Weights);
		void ProcessBoneWeights(fbxsdk::FbxSkin* Skin, std::vector<ModelBoneWeights>& Weights);
		void ProcessAnimations();
		void ProcessAnimation(fbxsdk::FbxNode* Node,std::string Name,float Framerate,float Start,float Stop);
		void ProcessSkeleton(fbxsdk::FbxNode* Node);




	private:


		fbxsdk::FbxManager* m_manager{ nullptr };
		fbxsdk::FbxScene* m_scene{ nullptr };

		fbxsdk::FbxGeometryConverter* m_converter{ nullptr };
		fbxsdk::FbxImporter* m_importer{ nullptr };



		ModelSkeleton* m_skeleton{ nullptr };

		std::vector<Model*> m_models{};
		


		ModelBuffer* m_modelbuffer{ nullptr };
		ModelAnimationController* m_animationController{nullptr};


		



	};




}