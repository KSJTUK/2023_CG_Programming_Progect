#pragma once
#include "AssimpHeader.h"


#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))


constexpr UINT MAX_NUM_OF_BONES_PER_VERTEX = 4;

struct _tagVERTEXBONEDATA {
	UINT BoneIDs[MAX_NUM_OF_BONES_PER_VERTEX]{ 0, };
	float Weights[MAX_NUM_OF_BONES_PER_VERTEX]{ 0.f, };


	void AddBoneData(UINT BoneID, float Weight) {
		for(UINT i = 0; i < ARRAY_SIZE_IN_ELEMENTS(BoneIDs); ++i) {
			
			if (Weights[i] == 0.f) {
				BoneIDs[i] = BoneID;
				Weights[i] = Weight;

				return;
			}
		}
		printf("ERROR : There is no space to register new Bone \n");
	}

};

using VertexBoneData = _tagVERTEXBONEDATA;


std::vector<VertexBoneData> vertex_to_bones{};
std::vector<int> mesh_base_vertex{};
std::map<std::string, UINT> bone_name_to_index_map{};




class SkinedMesh
{




};

