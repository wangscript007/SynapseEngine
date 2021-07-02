#pragma once
#include "DataTypes.h"
#include <map>
#include <string>

#include "Mesh3D.h"
#include "NodeCam.h"
#include <vector>

#include "glm/glm.hpp"
#include "glm/common.hpp"
#include "glm/ext.hpp"
#include "glm/exponential.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_common.hpp"
#include "AssimpConverter.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "SkeletalModel.h"
#include "ActorSkeleton.h"
#include "ActorNode.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h> 
class WorldActor
{
public:
	//std::map<std::string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter;

	WorldActor(const char* path);


	std::vector<Mesh3D*> BaseMesh;

	std::vector<Mesh3D*> Meshes;
	unsigned int ProcessNode(aiNode* node);


	void AddMesh(Mesh3D* mesh) {
		Meshes.push_back(mesh);
	}

	glm::vec3* TransformStream(glm::vec3* str, int count, glm::mat4 mat);
	void UpdateAnim(float d);
	void SetScale(glm::vec3 scale);
	void SetPosition(glm::vec3 pos);

	float ff = 0;
	void Rotate(glm::vec3 rot);
	void Render(NodeCam* cam);
	void RenderDepth(NodeCam* cam);
	void RenderExtra(NodeCam* cam);
	void RenderPosition(NodeCam* cam);
	void RenderNormals(NodeCam* cam);
	void RenderMeshes();
	void RenderMeshesNoMaterial();
	void GenerateBounds();
	glm::vec3 GetBoundsMin();
	glm::vec3 GetBoundsMax();
	void AnimateNode(float time, ActorBone* b, glm::mat4 parentTransform);

	void PlayAnim(int id) {
		
		anim = skeleton->Animations[id];

	}

	void Transform();

	glm::vec3 Bounds;
	bool boundsGenerated = false;
	bool Visible = false;
	WorldActor();
	SA::SkeletalModel model;
	glm::vec3 scale;
	glm::vec3 position;
	glm::mat4 rotation;
	int rn = 1;
	std::thread actorThr;
	bool animate = false;
	bool animateDone = false;
	float animateF = 0.0;
	float animF = 0.0;
	ActorSkeleton* skeleton;
	ActorNode* RootNode;
	ActorAnimation* anim;
	double animTime = 0.0;
	int smesh = -1;
};

