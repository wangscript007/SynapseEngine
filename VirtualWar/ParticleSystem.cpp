#include "ParticleSystem.h"
#include "WorldEffects.h"
#include "ParticleQuad.h"
ParticleSystem::ParticleSystem() {

	minPos = randV3(glm::vec3(-2, -2, -2), glm::vec3(0, 0, 0));
	maxPos = randV3(glm::vec3(0, 0, 0), glm::vec3(2, 2, 2));
	minInertia = randV3(glm::vec3(-5, -5, -5),glm::vec3(0,0,0));
	maxInertia = randV3(glm::vec3(0, 0, 0),glm::vec3(5, 5, 5));
	alphaMin = 0.8f;
	alphaMax = 1.0f;
	lifeMin = randF(0.1f, 0.2f);
	lifeMax = randF(0.3f, 1.0f);
	minScale = randV3(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.3f,0.3f,0.3f));
	maxScale = randV3(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(1, 1, 1));
	minSize = randF(0.2, 10);
	maxSize = randF(10, 20);


}

void ParticleSystem::addBase(ParticleBase* p) {

	base.push_back(p);

}

void ParticleSystem::spawn(int num) {

	for (int i = 0; i < num; i++) {

		for (int j = 0; j < base.size(); j++) {

			auto p = base[j]->clone();

//			glm::vec3

			p->alphaMod = randF(0.97f, 0.999f);
			p->alpha = randF(alphaMin, alphaMax);
			p->life = randF(lifeMin, lifeMax);
			p->size = randF(minSize, maxSize);
			p->pos = randV3(glm::vec3(-120, -120, -120), glm::vec3(120, 120, 120));
			p->sizeMod = randF(0.01f, 0.03f);
			p->inertia = randV3(minInertia, maxInertia);
			p->color = glm::vec3(1, 1, 1);
			spawned.push_back(p);







		}

	}

}

void ParticleSystem::Update(NodeCam* cam) {

	for (int i = 0; i < spawned.size(); i++) {



		auto pt = spawned[i];

		pt->alpha = pt->alpha * pt->alphaMod;

		if (pt->alpha < 0.01f)
		{
			spawned[i] = spawned[spawned.size() - 1];
			spawned.pop_back();
		}

		glm::vec3 pos = pt->GetPos();

		pos = pos + pt->inertia;

		//pt->pos = pos;

		float size = pt->size;

		size = size + pt->sizeMod;
		pt->size = size;

		float xd, yd, zd, dis;

		xd = cam->GetPosition().X - pos.x;
		yd = cam->GetPosition().Y - pos.y;
		zd = cam->GetPosition().Z - pos.z;

		dis = sqrt(xd * xd + yd * yd + zd * zd);

		pt->cameradistance = dis;
		
	


	}


		bool sorted = true;
		for (int i = 0; i < spawned.size(); i++) {

			//bool sorted = true;

			sorted = true;
			for (int j = 0; j < spawned.size(); j++) {

				if (j == i) continue;
				if (spawned[i]->cameradistance < spawned[j]->cameradistance)
				{
					auto tmp = spawned[i];
					spawned[i] = spawned[j];
					spawned[j] = tmp;
					sorted = false;
				}

			}
			if (sorted) break;

		}
	
	//	std::sort(&spawned[0], &spawned[MaxParticles]);

}

void ParticleSystem::Render(NodeCam* cam) {

	
	std::vector<glm::vec3> vs;
	std::vector<unsigned int> is;

	unsigned int vn = 0;
	for (int i = 0; i < spawned.size(); i++) {

		auto pt = spawned[i];

		glm::vec3 pos = pt->GetPos();

		float size = pt->size;

		glm::vec3 v1(pos.x-size, pos.y-size, pos.z);
		glm::vec3 v2(pos.x + size, pos.y - size, pos.z);
		glm::vec3 v3(pos.x + size, pos.y + size, pos.z);
		glm::vec3 v4(pos.x - size, pos.y + size, pos.z);

		vs.push_back(v1);
		vs.push_back(glm::vec3(0, 1, 0));
		vs.push_back(pt->color);
		vs.push_back(glm::vec3(pt->alpha, 0, 0));
		vs.push_back(v2);
		vs.push_back(glm::vec3(1, 1, 0));
		vs.push_back(pt->color);
		vs.push_back(glm::vec3(pt->alpha, 0, 0));
		vs.push_back(v3);
		vs.push_back(glm::vec3(1, 0, 0));
		vs.push_back(pt->color);
		vs.push_back(glm::vec3(pt->alpha, 0, 0));
		vs.push_back(v4);
		vs.push_back(glm::vec3(0, 0, 0));
		vs.push_back(pt->color);
		vs.push_back(glm::vec3(pt->alpha, 0, 0));
		is.push_back(vn+0);
		is.push_back(vn+1);
		is.push_back(vn+2);
		is.push_back(vn+2);
		is.push_back(vn+3);
		is.push_back(vn+0);
		vn += 4;
	}

	if (VertexArray == -1) {
		glGenVertexArrays(1, &VertexArray);
		glGenBuffers(1, &VertexBuffer);
	}

	int maxSize = spawned.size();

	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);


	int vecs = 16;
	int vecSize = 3 * 4;
	int fSize = vecs * vecSize;

	GLsizeiptr size = (GLsizeiptr)spawned.size() * fSize;

	glBufferData(GL_ARRAY_BUFFER, size, (const void*)vs.data(), GL_DYNAMIC_DRAW);


	// Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, (GLsizei)(4*3*4), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, (GLsizei)(4*3*4), (void*)(3 * 4));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, (GLsizei)(4*3*4), (void*)(6 * 4));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, (GLsizei)(4 * 3 * 4), (void*)(9 * 4));


	/*
	//UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(7 * 4));

	//Norm
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(10 * 4));

	//Binorm
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(13 * 4));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(16 * 4));
	*/



	//glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(3);
	//glDisableVertexAttribArray(4);
	//	glDisableVertexAttribArray(5);





	if (IndexBuffer == -1) {
		glGenBuffers(1, &IndexBuffer);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * is.size(), is.data(),GL_DYNAMIC_DRAW);

	auto mfx = WorldEffects::XParticleSoft;

	//mfx->bind();
	mfx->mProj = cam->GetProj();
	mfx->mModel = glm::mat4(1.0f);
	mfx->mView = cam->GetWorld();
	mfx->Cam = cam;
	//mfx->bind();

	
	NodeBase* n = new NodeBase;
	n->SetPosition(Vect3(0, 0, 0));

	n->LookAt(cam->GetPosition());

	mfx->mModel = n->GetRotation();

	auto p1 = spawned[0];

	ParticleQuad* q1 = (ParticleQuad*)p1;

	q1->tex->Bind(0);

	//spawned[0]
	mfx->bind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDrawElements(GL_TRIANGLES, is.size(), GL_UNSIGNED_INT, (void*)(0));
	//return;
	mfx->unbind();

	q1->tex->Release(0);

	//mfx->unbind();

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);


}