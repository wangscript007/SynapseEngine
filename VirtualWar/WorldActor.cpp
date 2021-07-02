#include "WorldActor.h"
#include "WorldEffects.h"
#include "ModelImport.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


#include "Material.h"
#include "VString.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "WorldActor.h"
#include <map>
#include "Helper.h"
#include "ActorSkeleton.h"
//#include "ActorBone.h"

WorldActor::WorldActor() {

	Meshes.resize(0);
	BaseMesh.resize(0);// = NULL;
	scale = glm::vec3(1, 1, 1);
	position = glm::vec3(0, 0, 0);
	rotation = glm::mat4(1.0);
	m_BoneCounter = 0;

}

// Private functions to convert from Assimp data types to glm
static glm::mat4x4 aiToGlm(const aiMatrix4x4& v)
{
	glm::mat4x4 out;
	assert(sizeof(out) == sizeof(v));
	memcpy(&out, &v, sizeof(v));
	return glm::transpose(out);
}





static glm::vec3 aiToGlm(const aiVector3D& v)
{
	glm::vec3 out;
	assert(sizeof(out) == sizeof(v));
	memcpy(&out, &v, sizeof(v));
	return out;
}





static glm::quat aiToGlm(const aiQuaternion& v)
{
	return glm::quat(v.w, v.x, v.y, v.z);
}





void actorThread(WorldActor* a)
{
	
}
const char* mpath2 = "";

WorldActor::WorldActor(const char* path) {

	scale = glm::vec3(1, 1, 1);
	position = glm::vec3(0, 0, 0);
	rotation = glm::mat4(1.0);


	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace);
	
	std::vector<Mesh3D*> meshes;
	printf("Importing scene.\n");

	printf("Importing meshes. Number:%d\n", scene->mNumMeshes);

	skeleton = new ActorSkeleton;

	skeleton->GlobalInverseTransform = glm::inverse(aiToGlm(scene->mRootNode->mTransformation));

	printf("Importing Nodes.\n");
	ProcessNode(scene->mRootNode);
	printf("Imported.\n");

	for (int i = 0; i < scene->mNumMeshes; i++) {
		
		auto aim = scene->mMeshes[i];

		printf("Importing mesh:%d\n", i);
		
		Mesh3D* mesh = new Mesh3D;

		Meshes.push_back(mesh);

		printf("Mesh Verts:%d Tris:%d\n", aim->mNumVertices, aim->mNumFaces);

		for (int v = 0; v < aim->mNumVertices; v++) {

			aiVector3D pos, norm, bi, tan, uv;

			pos = aim->mVertices[v];
			norm = aim->mNormals[v];
			bi = aim->mBitangents[v];
			tan = aim->mTangents[v];
			uv = aim->mTextureCoords[0][v];

			Vertex v1;

			v1.Pos = Vect3(pos.x,pos.y,pos.z);
			v1.Norm = Vect3(norm.x, norm.y, norm.z);
			v1.BiNorm = Vect3(bi.x, bi.y, bi.z);
			v1.Tan = Vect3(tan.x, tan.y, tan.z);
			v1.UV = Vect3(uv.x, uv.y, 0.0f);

			mesh->AddVertex(v1);

		}

		for (int f = 0; f < aim->mNumFaces; f++) {

			auto face = aim->mFaces[f];

			Tri t;

			t.V0 = face.mIndices[0];
			t.V1 = face.mIndices[1];
			t.V2 = face.mIndices[2];

			mesh->AddTri(t);

		}

		printf("Mesh Bones:%d\n", aim->mNumBones);
	
		auto mc = mesh->Clone();

		//Meshes.push_back(mesh);
		BaseMesh.push_back(mc);

		mesh->CreateVBO();
		mc->CreateVBO();

	
		//aim->mNumBones;

		printf("Importing bones. Count:%d\n", aim->mNumBones);

		if (aim->mNumBones > 0) {

			smesh = i;

		}

		for (int b = 0; b < aim->mNumBones; b++) {

			auto bone = aim->mBones[b];

			ActorBone* cb = skeleton->findBone(std::string(bone->mName.C_Str()));

			if (cb != NULL) {
				printf("Found bone.\n");
			}
			else {
				printf("Bone not found.\n");
			}

			//ActorBone* ab = new ActorBone(bone->mName.C_Str());


			printf("Imported bone:%d ", b);
			printf("Name:");
			printf(bone->mName.C_Str());
			printf("\n");
			
			cb->SetOffsetMatrix(aiToGlm(bone->mOffsetMatrix));
			int vc = mesh->NumVertices();
			mesh->AddBone(cb);
			

			printf("Weights:%d\n", bone->mNumWeights);
			cb->numWeights = bone->mNumWeights;
			for (int w = 0; w < bone->mNumWeights; w++) {

				auto aw = bone->mWeights[w];
				
				BoneWeight* bw = new BoneWeight;
				bw->Weight = aw.mWeight;
				bw->Vertex = aw.mVertexId;
				cb->weights.push_back(bw);
				if (bw->Vertex >= vc) {
					printf("Vertex exceeds limit.\n");
					while (true) {};
				}
				
			}

		//bone->


		}

		printf("Created mesh:%d\n", i);

		

	}


	printf("Importing animations. Count:%d\n", scene->mNumAnimations);

	for (int a = 0; a < scene->mNumAnimations; a++) {

		ActorAnimation* aa = new ActorAnimation;
		
		skeleton->Animations.push_back(aa);

		auto anim = scene->mAnimations[a];
		printf("Anim:%d", a);
		printf(" Channels:%d", anim->mNumChannels);
		printf(" Mesh Channels:%d", anim->mNumMeshChannels);
		printf(" Morph Channels:%d\n", anim->mNumMorphMeshChannels);
		aa->duration = anim->mDuration;
		aa->ticksPerSecond = anim->mTicksPerSecond;
		aa->name = std::string(anim->mName.C_Str());

		printf("Importing Animation channels: count:%d\n", anim->mNumChannels);

		for (int c = 0; c < anim->mNumChannels; c++) {

			auto chan = anim->mChannels[c];

			AnimationChannel* ac = new AnimationChannel;

			aa->channels.push_back(ac);

			printf("Importing channel:%d ", c);
			printf("Name:");
			printf(chan->mNodeName.C_Str());
			printf("\n");
			ac->name = std::string(chan->mNodeName.C_Str());
			
			printf("Importing keys. Pos:%d Rot:%d Scale:%d\n", chan->mNumPositionKeys, chan->mNumRotationKeys, chan->mNumScalingKeys);

			for(int p=0;p<chan->mNumPositionKeys;p++)
			{
				VecKey vk;
				vk.key = aiToGlm(chan->mPositionKeys[p].mValue);
				vk.time = chan->mPositionKeys[p].mTime;
				ac->PosKeys.push_back(vk);
				//	ac->PosKeys.push_back(aiToGlm(chan->mPositionKeys[p].mValue));
			}

			for (int r = 0; r < chan->mNumRotationKeys; r++) {

				RotKey rk;
				rk.key = aiToGlm(chan->mRotationKeys[r].mValue);
				rk.time = chan->mRotationKeys[r].mTime;
				ac->RotKeys.push_back(rk);
			}

			for (int s = 0; s < chan->mNumScalingKeys; s++) {

				VecKey vk;
				vk.key = aiToGlm(chan->mScalingKeys[s].mValue);
				vk.time = chan->mScalingKeys[s].mTime;
				ac->ScaleKeys.push_back(vk);

			}



		
					

		}


	
	}


	for (int b = 0; b < skeleton->bones.size(); b++) {

		auto bone = skeleton->bones[b];

		printf("Bone:%d Name:",b);
		printf(bone->name.c_str());
		printf("\n");

	}

	int bb = 5;

	//while (true) {}
	// 
	//while(true){}
	//const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);


	/*
	int dc = mat->GetTextureCount(aiTextureType_DIFFUSE);
	int nc = mat->GetTextureCount(aiTextureType_NORMALS);

	aiString dp;


	VString p1(path);

	//printf("P:");
	//printf(path);
	//printf("|\n");
	int lc = -1;
	while (true) {

		int pc = p1.Find("\\", lc + 1);
		if (pc == -1) {
			break;
		}
		lc = pc;

	}

	if (lc != -1) {
		VString bp(path);
		p1 = bp.SubString(0, lc);
		p1.Add(VString("\\"));
	}

	//printf("P2:");
	//printf(p1.GetConst());
	//printf("|\n");

	mpath2 = p1.GetConst();

	Material* nm = new Material;

	if (nc > 0)
	{

		mat->GetTexture(aiTextureType_NORMALS, 0, &dp);

	}

	if (dc > 0) {
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &dp);

		VString np3(dp.C_Str());

		np3.Replace("/"[0], "\\"[0]);

		dp = aiString(std::string(np3.GetConst()));

		//printf("Diff:");
		//printf(dp.C_Str());
		//printf("\n");
		VString np2 = VString(mpath2);

		np2.Add(VString(dp.C_Str()));


		if (false) //VFile::Exists(np2.GetConst())) {
		{
			Texture2D* ntex = new Texture2D(np2.GetConst(), false);
			//vmat->SetColorTex(ntex);

		}
		else {


			VString mp(mpath2);
			mp.Add(dp.C_Str());
			p1 = VString(dp.C_Str());

			int lc = -1;
			while (true) {

				int pc = p1.Find("\\", lc + 1);
				if (pc == -1) {
					break;
				}
				lc = pc;

			}

			if (lc != -1) {
				VString bp(dp.C_Str());
				p1 = bp.SubString(lc + 1, bp.Len() - lc - 1);
				//p1.Add(VString("\\"));

			}

			VString np = p1;

			np.Add(VString("norm_"));

			VString np3 = VString(mpath2);

			np3.Add(VString(p1));

			np = VString(mpath2);

			auto sp = VString(mpath2);


			np.Add("norm_");
			np.Add(VString(p1));

			sp.Add("spec_");
			sp.Add(VString(p1));

			//mp = VString(p1);

			mp = np3;

			if (VFile::Exists(sp.GetConst())) {

				Texture2D* spectex = new Texture2D(sp.GetConst(), false);
				nm->SetSpecularTex(spectex);

			}

			if (VFile::Exists(np.GetConst())) {

				Texture2D* normtex = new Texture2D(np.GetConst(), false);
				nm->SetNormalTex(normtex);

			}

			if (VFile::Exists(mp.GetConst())) {

				Texture2D* ntex = new Texture2D(mp.GetConst(), false);
				nm->SetColorTex(ntex);

			}
			else {



				VString p1(dp.C_Str());
				p1.Replace("/"[0], "\\"[0]);

				int lc = -1;
				while (true) {

					int pc = p1.Find("\\", lc + 1);
					if (pc == -1) {
						break;
					}
					lc = pc;

				}

				VString jf = p1.SubString(lc + 1, p1.Len() - lc - 1);
				//VString p1(mpath);
				//VString p2(filep);
				VString mp(mpath2);

				mp.Add(jf);

				//printf("TP:");
				//printf(mp.GetConst());
				//printf("|\n");
				//while(true){}

				if (VFile::Exists(mp.GetConst()))
				{

					Texture2D* ntex = new Texture2D(mp.GetConst(), false, true);
					nm->SetColorTex(ntex);

				}



			}
		}

	}


	for (int i = 0; i < model.GetNumMeshes(); i++) {

		auto Mesh = new Mesh3D();
		BaseMesh.push_back(Mesh);

		auto am = model.GetMesh(i);

		Mesh->SetMaterial(nm);

		std::vector<Vertex> verts;

		for (int i = 0; i < am.NumVertices; i++) {

			Vertex nv;

			nv.Pos = am.pVertices[i];
			nv.Norm = am.pNormals[i];
			nv.BiNorm = am.pBiNormals[i];
			nv.Tan = am.pTangents[i];
			nv.UV = Vect3(am.pUV[i].x, am.pUV[i].y, 0);

			verts.push_back(nv);

		}

		std::vector<Tri> tris;

		for (int i = 0; i < am.NumIndices; i += 3) {

			Tri t;
			t.V0 = am.pIndices[i];
			t.V1 = am.pIndices[i + 1];
			t.V2 = am.pIndices[i + 2];
			tris.push_back(t);

		}

		Mesh->SetVertexData(verts);
		Mesh->SetTriData(tris);
		Mesh->CreateVBO();

		Meshes.push_back(Mesh->Clone());
		Meshes[i]->CreateVBO();
		Meshes[i]->SetMaterial(nm);

		//while (true) {}


	}
	*/
}

unsigned int  WorldActor::ProcessNode(aiNode* node) {

	ActorNode* an = new ActorNode;
	an->name = std::string(node->mName.C_Str());
	an->Transform = aiToGlm(node->mTransformation);
	unsigned int boneID = skeleton->bones.size();
	ActorBone* bone = new ActorBone;
	bone->name = node->mName.C_Str();
	bone->NodeTransform = aiToGlm(node->mTransformation);
	bone->numChildren = node->mNumChildren;
	bone->children = new unsigned int[bone->numChildren];
	bone->numWeights = 0;
	for (unsigned int i = 0; i < bone->numChildren; i++) {
		bone->children[i] = -1;
	}
	skeleton->bones.push_back(bone);
	/*
	printf("Adding Meshes. Count:%d\n", node->mNumMeshes);
	for (int m = 0; m < node->mNumMeshes; m++) {
		an->meshes.push_back(Meshes[node->mMeshes[m]]);
	}
	*/
	

	for (int c = 0; c < node->mNumChildren; c++) {

		unsigned int childID = ProcessNode(node->mChildren[c]);
		skeleton->bones[boneID]->children[c] = childID;
		//an->child.push_back(ProcessNode(node->mChildren[c]));
		//an->child[an->child.size() - 1]->parent = an;

	}



	return boneID;

}

void WorldActor::Render(NodeCam* cam) {

	auto mfx = WorldEffects::XMesh;

	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;

	mfx->mProj = cam->GetProj();
	//mfx->mModel = glm::mat4(1.0f) * sm;

	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

	//mfx->mProj = cam->GetProj();
	//mfx->mModel = rotation;;
	//mfx->mView = cam->GetWorld();
	//mfx->fCol = Vect3(1, 1, 1);


	//glDisable(GL_BLEND);
	mfx->bind();

	RenderMeshes();


	mfx->unbind();

}

void WorldActor::Rotate(glm::vec3 rot) {

	glm::mat4 xmat = glm::rotate(glm::mat4(1.0f), glm::radians(rot.x), glm::vec3(1, 0, 0));
	glm::mat4 ymat = glm::rotate(glm::mat4(1.0f), glm::radians(rot.y), glm::vec3(0, 1, 0));
	glm::mat4 zmat = glm::rotate(glm::mat4(1.0f), glm::radians(rot.z), glm::vec3(0, 0, 1));

	rotation = ymat * xmat * zmat;


}

void WorldActor::RenderDepth(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshDepth;

	mfx->mProj = cam->GetProj();


	mfx->mView = cam->GetWorld();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->Cam = cam;
	bool first = true;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshesNoMaterial();

	mfx->unbind();

}

void WorldActor::RenderExtra(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshPosMap;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshes();

	mfx->unbind();



}

void WorldActor::RenderPosition(NodeCam* cam) {

	auto mfx = WorldEffects::XMeshPosMap;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshesNoMaterial();

	mfx->unbind();



}

void WorldActor::RenderNormals(NodeCam* cam) {


	auto mfx = WorldEffects::XMeshNormMap;

	mfx->mProj = cam->GetProj();
	glm::mat4 sm = glm::scale(scale);


	glm::vec3 np(position.x, position.y, position.z);

	glm::mat4 fm = glm::translate(np);
	//glm::mat4 sm = glm::scale(scale);

	fm = fm * rotation * sm;

	mfx->mModel = fm;
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;

	mfx->bind();

	//node->RenderNoMaterial();

	RenderMeshesNoMaterial();

	mfx->unbind();


}

void WorldActor::RenderMeshesNoMaterial() {

	for (int i = 0; i < Meshes.size(); i++) {

		
		//Meshes[i]->BindMaterial();
		BaseMesh[i]->BindVBO();
		BaseMesh[i]->DrawVBO();
		BaseMesh[i]->ReleaseVBO();
		//Meshes[i]->ReleaseMaterial();

	}

}

void WorldActor::RenderMeshes() {

	for (int i = 0; i < BaseMesh.size(); i++) {
		
	
		BaseMesh[i]->BindMaterial();
		BaseMesh[i]->BindVBO();
		BaseMesh[i]->DrawVBO();
		BaseMesh[i]->ReleaseVBO();
		BaseMesh[i]->ReleaseMaterial();

	}

}

void WorldActor::SetScale(glm::vec3 s)
{

	scale = s;

}

void WorldActor::SetPosition(glm::vec3 p)
{

	position = p;

}

glm::vec3* WorldActor::TransformStream(glm::vec3* str, int count,glm::mat4 mat)
{

	//transformer->setMatrix(mat);



	return nullptr;

}

void WorldActor::AnimateNode(float time, ActorBone* bone, glm::mat4 parentTransform) {

	std::string NodeName(bone->name);
	glm::mat4x4 NodeTransformation(bone->NodeTransform);
	AnimationChannel* chan = anim->FindChannel(NodeName);

	if (chan != nullptr) {

		glm::vec3 trans = chan->GetPosition(time);
		glm::quat rot = chan->GetRotation(time);

		glm::mat4x4 rot2 = glm::toMat4(rot);
		glm::mat4x4 trans2 = glm::translate(trans);

		NodeTransformation = trans2 * rot2;

	}

	glm::mat4x4 GlobalTransform = parentTransform * NodeTransformation;

	unsigned int boneID = skeleton->findBoneIndex(NodeName);
	if (boneID != -1) {

		ActorBone* ab = skeleton->bones[boneID];
		ab->FinalTransform = skeleton->GlobalInverseTransform * GlobalTransform * ab->OffsetMatrix;

	}

	for (int i = 0; i < bone->numChildren; i++) {

		AnimateNode(time, skeleton->bones[bone->children[i]], GlobalTransform);

	}

	int vv = 5;

}

void WorldActor::Transform() {

	auto tm = BaseMesh[smesh];
	auto verts = BaseMesh[smesh]->GetVertexData();

	auto rm = Meshes[smesh];

	std::vector<glm::vec3> tpos;
	std::vector<glm::vec3> tnorm;
	std::vector<glm::vec3> tbi;
	std::vector<glm::vec3> ttan;
	for (int i = 0; i < verts.size(); i++) {

		tpos.push_back(glm::vec3(0, 0, 0));
		tnorm.push_back(glm::vec3(0, 0, 0));
		tbi.push_back(glm::vec3(0, 0, 0));
		ttan.push_back(glm::vec3(0, 0, 0));

	}




	int b = 0;

	for (int i = 0; i < skeleton->bones.size(); i++) {

		auto bone = skeleton->bones[i];

		glm::mat4x4 Transformation = bone->FinalTransform;
		glm::mat3x3 Rotation = glm::mat3x3(Transformation);

		for (int w = 0; w < bone->weights.size(); w++) {

			BoneWeight* bw = bone->weights[w];

			glm::vec3 inVertex = verts[bw->Vertex].Pos.GL();
			glm::vec3& outVertex = tpos[bw->Vertex];// AnimMesh.pTransformedVertices[Weight.VertexID];
			outVertex += glm::vec3((Transformation * glm::vec4(inVertex, 1)) *bw->Weight);
			tpos[bw->Vertex] = outVertex;
			//
								//norm
			glm::vec3 inNormal = verts[bw->Vertex].Norm.GL();
			glm::vec3& outNormal = tnorm[bw->Vertex];
			outNormal += (Rotation * inNormal) * bw->Weight;
			tnorm[bw->Vertex] = outNormal;
			//binorm
			glm::vec3 inBiNormal = verts[bw->Vertex].BiNorm.GL();
			glm::vec3& outBiNormal = tbi[bw->Vertex];
			outBiNormal += (Rotation * inBiNormal) * bw->Weight;
			tbi[bw->Vertex] = outBiNormal;
			//tan
			glm::vec3 inTan = verts[bw->Vertex].Tan.GL();
			glm::vec3& outTan = ttan[bw->Vertex];
			outTan += (Rotation * inTan) * bw->Weight;
			ttan[bw->Vertex] = outTan;


			int cc = 5;
		}

	}

	std::vector<Vertex> data;

	for (int i = 0; i < tpos.size(); i++) {

		Vertex v;
		v.Pos = tpos[i];
		v.Norm = tnorm[i];
		v.BiNorm = tbi[i];
		v.Tan = ttan[i];


		data.push_back(v);
	}

	rm->SetVertexData(data);
	rm->SetTriData(tm->GetTriData());
	rm->UpdateVBO();

	int bb = 0;

}

void WorldActor::UpdateAnim(float f) {

	animTime = fmodf(animTime + f * anim->ticksPerSecond, anim->duration);

	AnimateNode(animTime, skeleton->bones[0], glm::mat4(1.0f));
	Transform();
	return;
	animateF = f;
	actorThread(this);
	return;

	if (!Visible) {
		animateDone = false;
		animate = false;
		animF += f;
		return;

	}
	else {

		f += animF;
		animF = 0.0;


	}

	/*
	if (transformer != NULL) {

		glm::mat4 cmat(1.0f);

		glm::vec3 *r = TransformStream(am.pVertices, am.NumVertices, cmat);
		for (int i = 0; i < 100; i++) {

			printf("V:%f\n", r[i].x);

		}

		while (true);
		return;

	}
	*/
		
	if (animate == false && animateDone == false) {
		animateF = f;
		animateDone = false;
		animate = true;
		return;
		//while (!animateDone) {
			//Sleep(1);
		//}
		//animateDone = false;
	
	}
	else {

		if (animateDone) {
			Meshes[0]->UpdateVBO();
			animate = false;
			animateDone = false;
			return;
		}
		else {
			return;
		}

	}
		

	//	auto am = model.GetMesh(0);

	


		/*
		std::vector<Tri> tris;

		for (int i = 0; i < am.NumIndices; i += 3) {

			Tri t;
			t.V0 = am.pIndices[i];
			t.V1 = am.pIndices[i + 1];
			t.V2 = am.pIndices[i + 2];
			tris.push_back(t);

		}
		*/
		//Meshes[0]->SetVertexData(verts);
		Meshes[0]->UpdateVBO();

		//Mesh->SetVertexData(verts);
		//Mesh->SetTriData(tris);
		//Mesh->CreateVBO();




}

void WorldActor::GenerateBounds() {

	if (boundsGenerated) return;
	boundsGenerated = true;

	bool first = true;

	float sx, sy, sz;
	float bx, by, bz;

	for (int m = 0; m < BaseMesh.size(); m++) {

		auto bm = BaseMesh[m];

		for (int i = 0; i < bm->NumVertices(); i++) {

			auto v = bm->GetVertex(i);

			auto vp = glm::vec3(v.Pos.X, v.Pos.Y, v.Pos.Z);

			glm::mat4 sm = glm::scale(scale);

			vp = sm * glm::vec4(vp, 1.0);

			if (first) {

				sx = vp.x;
				sy = vp.y;
				sz = vp.z;

				bx = vp.x;
				by = vp.y;
				bz = vp.z;

				first = false;

			}
			else {

				if (vp.x < sx) sx = vp.x;
				if (vp.y < sy) sy = vp.y;
				if (vp.z < sz) sz = vp.z;

				if (vp.x > bx) bx = vp.x;
				if (vp.y > by) by = vp.y;
				if (vp.z > bz) bz = vp.z;

			}

		}
	}
	Bounds.x = bx - sx;
	Bounds.y = by - sy;
	Bounds.z = bz - sz;

	printf("Bounds. X:%f Y:%f Z:%f\n", Bounds.x, Bounds.y, Bounds.z);
	

}

glm::vec3 WorldActor::GetBoundsMax() {

	float px, py, pz;

	px = position.x;
	py = position.y;
	pz = position.z;

	glm::vec3 p1;

	p1.x = px + Bounds.x;// / 2.0f;
	p1.y = py + Bounds.y;// / 2.0f;
	p1.z = pz + Bounds.z;// / 2.0f;

	return p1;

}

glm::vec3 WorldActor::GetBoundsMin() {

	float px, py, pz;

	px = position.x;
	py = position.y;
	pz = position.z;

	glm::vec3 p1;

	p1.x = px - Bounds.x;// / 2.0f;
	p1.y = py - Bounds.y;// / 2.0f;
	p1.z = pz - Bounds.z;// / 2.0f;

	return p1;
	//bb[0] = p1;


	//bb[0] = //glm::vec2(px - Bounds.x / 2, py - Bounds.y/2, pz - Bounds.z/2);
	//bb[1] =///glm::vec2(px + B
		//ounds.x / 2, py + Bounds.y / 2, pz + Bounds.z);


}