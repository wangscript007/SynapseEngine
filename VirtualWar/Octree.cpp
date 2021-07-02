#include "Octree.h"
#include "GameWorld.h"
#include "WorldEffects.h"
#include "WorldChunk.h"
Octree::Octree(GameWorld* w) {

	world = w;
	ProcessWorld();

}

Octree::Octree(const char* path) {

	FILE* fin = fopen(path, "rb");

	worldChunk = new WorldChunk;

	worldChunk->Read(fin);


	//file.flush();
	fclose(fin);

	//file->Close();


}

void Octree::ProcessWorld() {

	auto b = world->GetBounds();

	worldChunk = new WorldChunk;

	WorldChunk::AllLinks.resize(0);

	worldChunk->Assume(world, b,TriLimit);
	

	



	//worldChunk->SetBounds();



}

void Octree::RenderShadows() {


}

void Octree::RenderWorld() {

	



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);


	bool first = true;

	WorldChunk::rlist.resize(0);

	worldChunk->GetRenderList(world->GetCam(),false);


	//glDepthMask(GL_TRUE);

	WorldChunk::renderCount = 0;
	for (int i = 0; i < world->NumLights(); i++) {
		 
		auto lt = world->GetLight(i);

		WorldEffects::XMesh->Light = lt;// world->GetLight(i);

		//WorldEffects::XMesh->bind();
		auto sb =lt->GetSB();
		sb->GetCube()->Bind(2);



		//worldChunk->Render(world->GetCam(),true);

		//worldChunk->Render(world->GetCam());
		for (int i = 0; i < WorldChunk::rlist.size(); i++) {

			WorldChunk::rlist[i]->Render(world->GetCam(),false);

		}

	
		//	printf("Visible Actors:%d\n", vis_actors.size());

			//	glClear(GL_DEPTH_BUFFER_BIT);
		sb->GetCube()->Release(2);

		if (first) {
			glBlendFunc(GL_ONE, GL_ONE);
		}
		//WorldEffects::XMesh->unbind();


	}

	//printf("Chunks Rendered:%d\n", WorldChunk::rlist.size());

}

void Octree::Save(const char* path) {

	
	FILE* fout = fopen(path, "wb");

	worldChunk->Write(fout);
	fflush(fout);
	fclose(fout);


	//file->Close();


}