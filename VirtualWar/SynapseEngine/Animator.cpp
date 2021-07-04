#include "Animator.h"
#include "Helper.h"
Animator::Animator() {

	_skeleton = NULL;

	CurrentAnimationIndex = -1;
	_bonesByName.clear();
	_bonesByIndex.clear();
	_animationNameToId.clear();
	_bones.resize(0);
	Animations.resize(0);

}

int Animator::GetBoneIndex(std::string name) {

	//if(_bonesByIndex)
	if (_bonesByIndex.contains(name)) {
		return _bonesByIndex[name];
	}
	return -1;
}

void Animator::SetAnimationIndex(int index) {
	CurrentAnimationIndex = index;
}


void Animator::CalculateBoneToWorldTransform(Bone* child) {

	child->GlobalTransform = child->LocalTransform;

	Bone* parent = child->Parent;
	while (parent != nullptr) {

		//Check!
		//child->GlobalTransform = parent->LocalTransform * child->GlobalTransform;

		child->GlobalTransform = child->GlobalTransform * parent->LocalTransform;
		parent = parent->Parent;

	}


}

Bone* Animator::CreateBoneTree(aiNode* node, Bone* parent) {

	Bone* internalNode = new Bone;
	internalNode->Name = std::string(node->mName.C_Str());
	internalNode->Parent = parent;

	if (internalNode->Name == "") {

		internalNode->Name = "foo" + std::to_string(_i++);

	}

	_bonesByName[internalNode->Name] = internalNode;
	aiMatrix4x4 trans = node->mTransformation;
	

	internalNode->LocalTransform = AssimpGLMHelpers::ConvertMatrixToGLMFormat(trans);
	internalNode->OriginalLocalTransform = internalNode->LocalTransform;
	CalculateBoneToWorldTransform(internalNode);

	for (int i = 0; i < node->mNumChildren; i++) {

		Bone* child = CreateBoneTree(node->mChildren[i], internalNode);
		if (child != nullptr)
		{
			internalNode->Children.push_back(child);

		}
	}
	return internalNode;


}

void DebugBones(Bone* bone) {

	printf("Name:");
	printf(bone->Name.c_str());
	printf(" Bone:%d\n", bone->Children.size());
	for (int i = 0; i < bone->Children.size(); i++) {
		DebugBones(bone->Children[i]);
	}

}

void Animator::InitAssImp(const aiScene* aiRoot, WorldActor* root)
{

	if (aiRoot->HasAnimations() == false) {
		return;
	}

	_skeleton = CreateBoneTree(aiRoot->mRootNode, nullptr);

	DebugBones(_skeleton);

	for (int i = 0; i < aiRoot->mNumMeshes; i++) {

		aiMesh* mesh = aiRoot->mMeshes[i];
		for (int j = 0; j < mesh->mNumBones; j++) {

			aiBone* bone = mesh->mBones[j];
			if (!_bonesByName.contains(bone->mName.C_Str()))
			{
				printf("Did not find bone.\n");
				continue;
			}
			Bone * found = _bonesByName[bone->mName.C_Str()];
			printf("Found bone.\n");
				
			bool skip = false;
			for (int c = 0; c < _bones.size(); c++) {

				if (_bones[c]->Name == bone->mName.C_Str()) {

					printf("Bone already found.\n");
					skip = true;
					break;
				}

			}

			if (skip)
			{
				continue;
			}
			found->Offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(bone->mOffsetMatrix);
			_bones.push_back(found);
			int ff = _bones.size() - 1;
			_bonesByIndex[found->Name] = ff;


		}
		ExtractAnimations(aiRoot);

		const float timestep = 1.0f / 30.0f;

		for (int k = 0; k < Animations.size(); k++) {

			SetAnimationIndex(k);
			float dt = 0.0;
			for (float ticks = 0.0f; ticks < Animations[k]->Duration; ticks += Animations[k]->TicksPerSecond / 30.0f)
			{
				dt += timestep;
				Calculate(dt);
				std::vector<glm::mat4>  trans;
				int bs = _bones.size();
				for (int a = 0; a < _bones.size(); a++) {

					glm::mat4 rotMat = _bones[a]->Offset * _bones[a]->GlobalTransform;
					trans.push_back(rotMat);

				}
				Animations[k]->Transforms.push_back(trans);

			}

		}

		
		/*
		* 
		for (auto it = _bonesByName.begin(); it != _bonesByName.end(); ++it)
		{
			auto bone_name = it->first;
			auto Bone = it->second;

			printf("Bone:");
			printf(bone_name.c_str());
			printf("\n");

		}
		*/
		printf("Check complete.\n");

		//for (int i = 0; i < _bonesByName.size(); i++) {

		//	auto key = _bonesByName.at


		//}



		printf("Searching for duplicates.\n");
		for (int i = 0; i < _bones.size(); i++) {

			Bone* b1 = _bones[i];

			for (int k = 0; k < _bones.size(); k++) {

				Bone* b2 = _bones[k];
				
				if (k != i) {
					if (b1 == b2) {
						printf("Duplicate bone.\n");
					}
				}

			}

		}
		printf("search complete.\n");



	}

	//printf("Bones:%d\n", _skeleton->Children.size());

	//while (true) {};


}

void Animator::Calculate(float dt) {

	if ((CurrentAnimationIndex < 0) | (CurrentAnimationIndex >= Animations.size()))
	{
		return;
	}
	Animations[CurrentAnimationIndex]->Evaluate(dt, _bonesByName);
	UpdateTransforms(_skeleton);
}

void Animator::UpdateTransforms(Bone* node) {

	CalculateBoneToWorldTransform(node);
	for (int i = 0; i < node->Children.size(); i++) {
		UpdateTransforms(node->Children[i]);
	}

}

void Animator::ExtractAnimations(const aiScene* root) {

	for (int i = 0; i < root->mNumAnimations; i++) {
		auto anim = root->mAnimations[i];

		Animations.push_back(new AnimEvaluator(anim));
		printf("Animation:");
		printf(Animations[i]->Name.c_str());
		printf(" Len:%f", Animations[i]->Duration);
		printf(" Channels:%d", Animations[i]->Channels.size());
		printf("\n");

	}
	for (int i = 0; i < Animations.size(); i++) {

		_animationNameToId[Animations[i]->Name] = i;

	}
	CurrentAnimationIndex = 0;
}