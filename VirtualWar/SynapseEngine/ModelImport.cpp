#include "ModelImport.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Material.h"
#include "VString.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "WorldActor.h"
#include <map>
#include "Helper.h"
NodeEntity* cur = NULL;

std::vector<Mesh3D*> meshes;
std::vector<Material*> mats;
const char* mpath = "";

const C_STRUCT aiScene* scene = NULL;

inline glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4* from)
{
	glm::mat4 to;


	to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
	to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
	to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
	to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;

	return to;
}

NodeEntity* importNode(const C_STRUCT aiScene* sc, const C_STRUCT aiNode* nd)
{

	//printf("Importing Node: Meshes:%d\n", nd->mNumMeshes);

	C_STRUCT aiMatrix4x4 m = nd->mTransformation;
	
	glm::mat4 vm = aiMatrix4x4ToGlm(&m);
	glm::vec4 pos = vm[3];

	vm[3] = glm::vec4(0, 0, 0, 1);


	//vm[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	NodeEntity* vent = new NodeEntity;

	//vent->SetRotation(vm);
	//vent->SetPosition(Vect3(pos.x, pos.y, pos.z));

	VString nn = VString(nd->mName.C_Str());
	vent->SetName(nn.GetConst());



	for (int i = 0; i < nd->mNumMeshes; i++) {

		Mesh3D* vmesh = meshes[nd->mMeshes[i]];
		//printf("Importing Mesh: Verts:%d Tris:%d\n", mesh->mNumVertices, mesh->mNumFaces);
		vent->AddMesh(vmesh);


	}

	/*
	for (; n < nd->mNumMeshes; ++n) {
		const C_STRUCT aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		*/
	//printf("Importing Children. Count:%d\n", nd->mNumChildren);
	for (int i = 0; i < nd->mNumChildren; i++) {
		
		auto nent = importNode(sc, nd->mChildren[i]);
		vent->Add(nent);

	}
	return vent;

}

NodeEntity* ModelImport::ImportAI(const char* path,bool optimize) {

	NodeEntity* root = new NodeEntity;

	VString p1(path);

	//printf("P:");
	//printf(path);
	//printf("|\n");
	int lc = -1;
	while (true) {

		int pc = p1.Find("\\",lc+1);
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
	
	mpath = p1.GetConst();

	//p1.Find("\\")





	if (optimize) {
		scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);
	}
	else {
		exit(0);
		scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	}
	cur = root;
	meshes.resize(0);
	mats.resize(0);


	for (int i = 0; i < scene->mNumMaterials; i++) {

		Material* vmat = new Material;

		auto mat = scene->mMaterials[i];
		int dc = mat->GetTextureCount(aiTextureType_DIFFUSE);
		int nc = mat->GetTextureCount(aiTextureType_NORMALS);

		mats.push_back(vmat);

		aiString dp;

		if (nc > 0)
		{

			mat->GetTexture(aiTextureType_NORMALS, 0, &dp);
		//	printf("Norm:");
		//	printf(dp.C_Str());
		//	printf("\n");

			if (VFile::Exists(dp.C_Str())) {

				Texture2D* ntex = new Texture2D(dp.C_Str(), false, true);
				vmat->SetNormalTex(ntex);

			}
			else {


				VString mp(mpath);
				mp.Add(dp.C_Str());

				if (VFile::Exists(mp.GetConst())) {

					Texture2D* ntex = new Texture2D(mp.GetConst(), false, true);
					vmat->SetNormalTex(ntex);

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
					VString mp(mpath);

					mp.Add(jf);

					//printf("TP:");
					//printf(mp.GetConst());
				//	printf("|\n");
					//while(true){}

					if (VFile::Exists(mp.GetConst()))
					{

						Texture2D* ntex = new Texture2D(mp.GetConst(), false, true);
						vmat->SetNormalTex(ntex);

					}



				}
			}
		}

		if (dc > 0) {
			mat->GetTexture(aiTextureType_DIFFUSE, 0, &dp);
			//printf("Diff:");
			//printf(dp.C_Str());
			//printf("\n");
			VString np2 = VString(mpath);

			np2.Add(VString(dp.C_Str()));


			if (false) //VFile::Exists(np2.GetConst())) {
			{
				Texture2D* ntex = new Texture2D(np2.GetConst(), false);
				vmat->SetColorTex(ntex);

			}
			else {


				VString mp(mpath);
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
					p1 = bp.SubString(lc+1,bp.Len()-lc-1);
					//p1.Add(VString("\\"));

				}

				VString np = p1;

				np.Add(VString("norm_"));

				VString np3 = VString(mpath);

				np3.Add(VString(p1));

				np = VString(mpath);

				auto sp = VString(mpath);


				np.Add("norm_");
				np.Add(VString(p1));

				sp.Add("spec_");
				sp.Add(VString(p1));

				//mp = VString(p1);

				mp = np3;

				if (VFile::Exists(sp.GetConst())) {

					Texture2D* spectex = new Texture2D(sp.GetConst(), false);
					vmat->SetSpecularTex(spectex);

				}

				if (VFile::Exists(np.GetConst())) {

					Texture2D* normtex = new Texture2D(np.GetConst(), false);
					vmat->SetNormalTex(normtex);

				}

				if (VFile::Exists(mp.GetConst())) {

					Texture2D* ntex = new Texture2D(mp.GetConst(), false);
					vmat->SetColorTex(ntex);

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
					VString mp(mpath);

					mp.Add(jf);

					//printf("TP:");
					//printf(mp.GetConst());
					//printf("|\n");
					//while(true){}

					if (VFile::Exists(mp.GetConst()))
					{

						Texture2D* ntex = new Texture2D(mp.GetConst(), false, true);
						vmat->SetColorTex(ntex);

					}



				}
			}

		}
//		printf("Mat: DC:%d NC:%d\n", dc, nc);


	}

	for (int m = 0; m < scene->mNumMeshes; m++) {

		const C_STRUCT aiMesh* mesh = scene->mMeshes[m];


		auto vmat = mats[mesh->mMaterialIndex];

	

		Mesh3D* vmesh = new Mesh3D(mesh->mNumVertices, mesh->mNumFaces);

		vmesh->SetMaterial(vmat);

		meshes.push_back(vmesh);

		for (int v = 0; v < mesh->mNumVertices; v++) {

			auto vert = mesh->mVertices[v];
			auto norm = mesh->mNormals[v];
			aiVector3D binorm;
			
			if (mesh->mBitangents != NULL) {
				binorm = mesh->mBitangents[v];
			}

			aiVector3D tan;
				
			if (mesh->mTangents != NULL) {
				tan = mesh->mTangents[v];
			}



			auto uv = mesh->mTextureCoords[0][v];
			aiColor4D col;
			col.r = 1;
			col.g = 1;
			col.b = 1;
			col.a = 1;
			if (mesh->HasVertexColors(0)) {
				col = mesh->mColors[0][v];
			}

			Vertex nvert;
			nvert.Pos = Vect3(vert.x, vert.z, vert.y);
			nvert.Norm = Vect3(norm.x, norm.z, norm.y);
			nvert.BiNorm = Vect3(binorm.x, binorm.z, binorm.y);
			nvert.Tan = Vect3(tan.x, tan.z, tan.y);
			nvert.UV = Vect3(uv.x, uv.y, uv.z);
			nvert.Col = Vect4(col.r, col.g, col.b, col.a);

			vmesh->SetVertex(v, nvert);
			//printf("X:%f Y:%f Z:%f \n", vert.x, vert.y, vert.z);
		}


		for (int t = 0; t < mesh->mNumFaces; t++) {

			auto face = mesh->mFaces[t];

			if (face.mNumIndices == 3) {

				Tri vtri;
				vtri.V0 = face.mIndices[0];
				vtri.V1 = face.mIndices[1];
				vtri.V2 = face.mIndices[2];

				vmesh->SetTri(t, vtri);
			}
		}

		vmesh->CreateVBO();

	}

	//printf("Importing scene.\n");
	root = importNode(scene, scene->mRootNode);

	//printf("Import complete.\n");

	aiReleaseImport(scene);
	

	return root;

}

