#include "pch.h"
#include "FBXMesh.h"
#include "String.h"


FBX::ModelScene::ModelScene(std::string path){



	m_manager = fbxsdk::FbxManager::Create();
	if (m_manager == NULL) {
		abort();
	}


	m_scene = fbxsdk::FbxScene::Create(m_manager,"");


	// m_modelbuffer = new ModelBuffer();


	m_converter = new fbxsdk::FbxGeometryConverter(m_manager);
	{

		LoadScene(path);

	}

	FBX_SAFE_DELETE(m_converter);

}

FBX::ModelScene::~ModelScene()
{
}

void FBX::ModelScene::Update()
{
}

void FBX::ModelScene::Render()
{
}

void FBX::ModelScene::LoadScene(std::string path)
{
	m_importer = fbxsdk::FbxImporter::Create(m_manager, "");

	bool status = m_importer->Initialize(path.c_str(), -1, m_manager->GetIOSettings());

	if (!status) {
		abort();
	}

	status = m_importer->Import(m_scene);
	if (!status) {
		abort();
	}


	ProcessScene();


	m_importer->Destroy();



}

void FBX::ModelScene::ProcessScene()
{




}

void FBX::ModelScene::ProcessNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNodeAttribute::EType attrib){

	fbxsdk::FbxNodeAttribute* nodeattrib = Node->GetNodeAttribute();

	if (nodeattrib != NULL) {
		if (nodeattrib->GetAttributeType() == attrib) {
			switch (nodeattrib->GetAttributeType()){

			case fbxsdk::FbxNodeAttribute::eSkeleton:
				ProcessSkeleton(Node);
				break;
			case fbxsdk::FbxNodeAttribute::eMesh:

				ProcessMesh(Node);
				break;
			case fbxsdk::FbxNodeAttribute::eMarker:
				break;
			case fbxsdk::FbxNodeAttribute::eNull:
				break;
			case fbxsdk::FbxNodeAttribute::eNurbs:
				break;
			case fbxsdk::FbxNodeAttribute::ePatch:
				break;
			case fbxsdk::FbxNodeAttribute::eLight:
				break;
			case fbxsdk::FbxNodeAttribute::eCamera:
				break;
			default:
				break;
			}
		}
	}
	
	for (auto i = 0; i < Node->GetChildCount(); ++i) {
		ProcessNode(Node->GetChild(i), attrib);
	}




}

void FBX::ModelScene::ProcessMesh(fbxsdk::FbxNode* Node){
	fbxsdk::FbxNodeAttribute* attrib = Node->GetNodeAttribute();


	m_converter->Triangulate(attrib, true, true);


	fbxsdk::FbxMesh* mesh = Node->GetMesh();

	SUCCESS(mesh);

	int vertexcount = mesh->GetControlPointsCount();

	
	SUCCESS(vertexcount);


	std::vector<ModelBoneWeights> boneWeights(vertexcount, ModelBoneWeights());
	ProcessBoneWeights(mesh, boneWeights);


	Model* model = new Model(String::StringToWString(Node->GetName()), m_modelbuffer);

	fbxsdk::FbxVector4* controlPoints = mesh->GetControlPoints();


	for (auto i = 0; i < mesh->GetPolygonCount(); ++i) {
		
	}


}

void FBX::ModelScene::ProcessBoneWeights(fbxsdk::FbxMesh* Mesh, std::vector<ModelBoneWeights>& Weights)
{

	// static mesh 일 경우 return 
	if (m_skeleton == NULL) {
		return;
	}


	for (auto i = 0; i < Mesh->GetDeformerCount(); ++i) {
		fbxsdk::FbxDeformer* deformer = Mesh->GetDeformer(i);
		
		if (deformer == NULL) {
			continue;
		}
	

		if (deformer->GetDeformerType() == fbxsdk::FbxDeformer::eSkin) {
			fbxsdk::FbxSkin* skin = (fbxsdk::FbxSkin*)deformer;

			if (skin == NULL) {
				continue;
			}

			ProcessBoneWeights(skin, Weights);

		}

	}


}

void FBX::ModelScene::ProcessBoneWeights(fbxsdk::FbxSkin* Skin, std::vector<ModelBoneWeights>& Weights){



	// cluster 는 mesh 의 부분집합 
	fbxsdk::FbxCluster::ELinkMode linkMode = fbxsdk::FbxCluster::eNormalize;


	int clusterCount = Skin->GetClusterCount();

	std::vector<ModelBoneWeights> skinBoneWeights(Weights.size(), ModelBoneWeights());



	for (auto i = 0; i < clusterCount; ++i) {
		fbxsdk::FbxCluster* cluster = Skin->GetCluster(i);

		if (cluster == NULL) {
			continue;
		}

		linkMode = cluster->GetLinkMode();
		fbxsdk::FbxNode* LinkNode = cluster->GetLink();

		if (LinkNode == NULL) {
			continue;
		}

		std::wstring LineNodeName = String::StringToWString(LinkNode->GetName());


		int nBoneIndex = m_skeleton->FindBoneIndex(LineNodeName);
		if (nBoneIndex > 0) continue;


		ModelSkeletonBone* skeletonBone = m_skeleton->GetSkeletonBone(nBoneIndex);


		fbxsdk::FbxAMatrix matClusterTransformMatrix{};
		fbxsdk::FbxAMatrix matClusterLinkTransformMatrix{};


		// 메쉬의 transform 
		cluster->GetTransformMatrix(matClusterTransformMatrix);
		
		// 뼈대의 transform 
		cluster->GetTransformLinkMatrix(matClusterLinkTransformMatrix);



		skeletonBone->SetBindPoseTransform(ModelUtility::ToMatrix(matClusterTransformMatrix));
		skeletonBone->SetBoneReferenceTransform(ModelUtility::ToMatrix(matClusterLinkTransformMatrix));




		int* indices = cluster->GetControlPointIndices();
		double* weights = cluster->GetControlPointWeights();


		for (auto j = 0; j < cluster->GetControlPointIndicesCount(); ++j) {
			skinBoneWeights[indices[j]].AddBoneWeight(nBoneIndex, (float)weights[j]);
		}


	}



	switch (linkMode)
	{
	case fbxsdk::FbxCluster::eNormalize: // 모든 정점의 합이 1로 정규화 
		for (auto i = 0; i < (int)skinBoneWeights.size(); ++i) {
			skinBoneWeights[i].Normalize();
		}
		break;
	case fbxsdk::FbxCluster::eAdditive: // 모든 가중치를 모두 합함 
		break;
	case fbxsdk::FbxCluster::eTotalOne: // 정규화 하지 않고 모두의 합이 1이됨 
		break;
	default:
		break;
	}


	for (size_t i = 0; i < Weights.size(); ++i) {
		Weights[i].AddBoneWeights(skinBoneWeights[i]);
	}


}

void FBX::ModelScene::ProcessSkeleton(fbxsdk::FbxNode* Node)
{
}


