#include "pch.h"
#include "IDraw.h"
#include "Texture2D.h"
#include "FXImageDraw.h"


IDraw::IDraw(int w,int h) {

	Draws.resize(0);
	drawZ = 0.01f;
	dw = w;
	dh = h;
	fx = new FXImageDraw(w,h);
	va = 0;
	vb = 0;

}

void IDraw::SingleDrawTex(int x, int y, int w, int h, Texture2D* tex, float r, float g, float b, float a) {

	glClear(GL_DEPTH_BUFFER_BIT);
	Begin();
	DrawTex(x, y, w, h, tex, r, g, b, a);
	End();

}

void IDraw::Begin() {

	for (int i = 0; i < Draws.size(); i++) {

		auto dd = Draws[i];

		for (int d = 0; d < dd->Draws.size(); d++) {

			auto d2 = dd->Draws[d];

			delete d2;

		}

		delete dd;

	}
	Draws.resize(0);
	drawZ = 0.001f;

}

void IDraw::End(kEffect* fx, bool alpha, bool soft) {

	if (vdat == NULL) {
		vdat = (float*)malloc(4 * 1024 * 250);
	}
	if (idat == NULL) {
		idat = (int*)malloc(4 * 1024 * 100);
	}
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	if (!soft) {
		if (alpha) {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else {
			glBlendFunc(GL_ONE, GL_ONE);
		};
	}
	else {
		glBlendFunc(GL_ONE, GL_ONE);
	}
	//glViewport(0, 0, Application::RenW, Application::RenH);

	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	fx->bind();

	if (madeGL == false) {
		madeGL = true;
		glGenVertexArrays(1, &va);


		glGenBuffers(1, &vb);
	}
	for (int i = 0; i < Draws.size(); i++) {

		//GLuint va;

		//		}
		DrawList* list = Draws[i];

		int draw_c = list->Draws.size() * 4;
		int draw_i = 0;
		int vc = 0;
		int ic = 0;


		//uint32_t ind_data[draw_c)];



		//float* vert_data = (float*)malloc((size_t) draw_c * 9 * 4);
		//uint32_t* ind_data = (uint32_t*)malloc((size_t)draw_c * 4);


		int vert_i = 0;
		int int_i = 0;

		list->Tex->Bind(0);
		if (list->Norm != NULL) {
			list->Norm->Bind(1);
		}
		for (int k = 0; k < list->Draws.size(); k++) {
			for (int l = 0; l < 4; l++) {

				//ind_data.push_back((GLuint)int_i);
				idat[ic++] = int_i;
				int_i++;


			}

			DrawInfo* info = list->Draws[k];

			vdat[vc++] = info->x[0];
			vdat[vc++] = info->y[0];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;


			vdat[vc++] = info->x[1];
			vdat[vc++] = info->y[1];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[2];
			vdat[vc++] = info->y[2];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[3];
			vdat[vc++] = info->y[3];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vert_i += 36;

		};


		glBindVertexArray(va);

		glBindBuffer(GL_ARRAY_BUFFER, vb);



		GLsizeiptr siz = ((GLsizeiptr)(vert_i) * 4);

		glBufferData(GL_ARRAY_BUFFER, siz, (const void*)vdat, GL_DYNAMIC_DRAW);



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * 4, 0);





		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 9 * 4, (void*)(3 * 4));



		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 9 * 4, (void*)(5 * 4));



		glDrawElements(GL_QUADS, draw_c, GL_UNSIGNED_INT, idat);



		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	//	glDeleteBuffers(1, &vb);
	//	glDeleteVertexArrays(1, &va);



		list->Tex->Release(0);
		if (list->Norm != NULL) {
			list->Norm->Release(1);
		};
	}


	fx->unbind();

}

void IDraw::End(bool leaveShader) {

	if (vdat == NULL) {
		vdat = (float*)malloc(4 * 1024 * 250);
	}
	if (idat == NULL) {
		idat = (int*)malloc(4 * 1024 * 100);
	}
	
//	fx->bind();
	//return;
	if (madeGL == false) {
		glGenVertexArrays(1, &va);

		glGenBuffers(1, &vb);
		madeGL = true;
	}

	for (int i = 0; i < Draws.size(); i++) {


		//		}
		DrawList* list = Draws[i];

		int draw_c = list->Draws.size() * 4;
		int draw_i = 0;



		//std::vector<GLfloat> vert_data;
		int vc = 0;
		int ic = 0;

		//		vert_data.resize(0);

				//float vert_data[draw_c];

				//uint32_t ind_data[draw_c)];



				//float* vert_data = (float*)malloc((size_t) draw_c * 9 * 4);
				//uint32_t* ind_data = (uint32_t*)malloc((size_t)draw_c * 4);


		int vert_i = 0;
		int int_i = 0;

		list->Tex->Bind(0);

		for (int k = 0; k < list->Draws.size(); k++) {

			for (int l = 0; l < 4; l++) {

				//ind_data.push_back((GLuint)int_i);
				idat[ic++] = int_i;
				int_i++;


			}

			DrawInfo* info = list->Draws[k];

			vdat[vc++] = info->x[0];
			vdat[vc++] = info->y[0];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;


			vdat[vc++] = info->x[1];
			vdat[vc++] = info->y[1];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[2];
			vdat[vc++] = info->y[2];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[3];
			vdat[vc++] = info->y[3];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			/*



			// - V2

				vert_data.push_back((GLfloat)info->x[1]);
				vert_data.push_back((GLfloat)info->y[1]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)1);
				vert_data.push_back((GLfloat)0);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);

			// - V3

				vert_data.push_back((GLfloat)info->x[2]);
				vert_data.push_back((GLfloat)info->y[2]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)1);
				vert_data.push_back((GLfloat)1);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);

			// - v4

				vert_data.push_back((GLfloat)info->x[3]);
				vert_data.push_back((GLfloat)info->y[3]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)0);
				vert_data.push_back((GLfloat)1);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);
				*/

			vert_i += 36;

		};


		glBindVertexArray(va);

		glBindBuffer(GL_ARRAY_BUFFER, vb);



		GLsizeiptr siz = ((GLsizeiptr)(vert_i) * 4);

		glBufferData(GL_ARRAY_BUFFER, siz, (const void*)vdat, GL_DYNAMIC_DRAW);



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * 4, 0);





		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 9 * 4, (void*)(3 * 4));



		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 9 * 4, (void*)(5 * 4));



		glDrawElements(GL_QUADS, draw_c, GL_UNSIGNED_INT, idat);



		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glDeleteBuffers(1,&vb);
		//glDeleteVertexArrays(1, &va);



		list->Tex->Release(0);

	};


//	fx->unbind();

}

void IDraw::EndNoBlend() {

	if (vdat == NULL) {
		vdat = (float*)malloc(4 * 1024 * 250);
	}
	if (idat == NULL) {
		idat = (int*)malloc(4 * 1024 * 100);
	}
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

//	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glViewport(0, 0, Application::RenW, Application::RenH);
	glClearDepth(1.0f);

	glDepthFunc(GL_LESS);
	fx->bind();
	//return;
	if (madeGL == false) {
		glGenVertexArrays(1, &va);

		glGenBuffers(1, &vb);
		madeGL = true;
	}

	for (int i = 0; i < Draws.size(); i++) {


		//		}
		DrawList* list = Draws[i];

		int draw_c = list->Draws.size() * 4;
		int draw_i = 0;



		//std::vector<GLfloat> vert_data;
		int vc = 0;
		int ic = 0;

		//		vert_data.resize(0);

				//float vert_data[draw_c];

				//uint32_t ind_data[draw_c)];



				//float* vert_data = (float*)malloc((size_t) draw_c * 9 * 4);
				//uint32_t* ind_data = (uint32_t*)malloc((size_t)draw_c * 4);


		int vert_i = 0;
		int int_i = 0;

		list->Tex->Bind(0);

		for (int k = 0; k < list->Draws.size(); k++) {

			for (int l = 0; l < 4; l++) {

				//ind_data.push_back((GLuint)int_i);
				idat[ic++] = int_i;
				int_i++;


			}

			DrawInfo* info = list->Draws[k];

			vdat[vc++] = info->x[0];
			vdat[vc++] = info->y[0];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;


			vdat[vc++] = info->x[1];
			vdat[vc++] = info->y[1];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[2];
			vdat[vc++] = info->y[2];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[3];
			vdat[vc++] = info->y[3];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			/*



			// - V2

				vert_data.push_back((GLfloat)info->x[1]);
				vert_data.push_back((GLfloat)info->y[1]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)1);
				vert_data.push_back((GLfloat)0);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);

			// - V3

				vert_data.push_back((GLfloat)info->x[2]);
				vert_data.push_back((GLfloat)info->y[2]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)1);
				vert_data.push_back((GLfloat)1);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);

			// - v4

				vert_data.push_back((GLfloat)info->x[3]);
				vert_data.push_back((GLfloat)info->y[3]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)0);
				vert_data.push_back((GLfloat)1);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);
				*/

			vert_i += 36;

		};


		glBindVertexArray(va);

		glBindBuffer(GL_ARRAY_BUFFER, vb);



		GLsizeiptr siz = ((GLsizeiptr)(vert_i) * 4);

		glBufferData(GL_ARRAY_BUFFER, siz, (const void*)vdat, GL_DYNAMIC_DRAW);



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * 4, 0);





		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 9 * 4, (void*)(3 * 4));



		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 9 * 4, (void*)(5 * 4));



		glDrawElements(GL_QUADS, draw_c, GL_UNSIGNED_INT, idat);



		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glDeleteBuffers(1,&vb);
		//glDeleteVertexArrays(1, &va);



		list->Tex->Release(0);

	};


	fx->unbind();



}

void IDraw::End() {

	//printf("DrawLists:%d \n", Draws.size());

	if (vdat == NULL) {
		vdat = (float*)malloc(4 * 1024 * 250);
	}
	if (idat == NULL) {
		idat = (int*)malloc(4 * 1024 * 100);
	}
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glViewport(0, 0, Application::RenW, Application::RenH);
	glClearDepth(1.0f);

	glDepthFunc(GL_LESS);
	fx->bind();
	//return;
	if (madeGL == false) {
		glGenVertexArrays(1, &va);

		glGenBuffers(1, &vb);
		madeGL = true;
	}

	for (int i = 0; i < Draws.size(); i++) {

	
//		}
		DrawList* list = Draws[i];

		int draw_c = list->Draws.size() * 4;
		int draw_i = 0;



		//std::vector<GLfloat> vert_data;
		int vc = 0;
		int ic = 0;

//		vert_data.resize(0);

		//float vert_data[draw_c];
	
		//uint32_t ind_data[draw_c)];



		//float* vert_data = (float*)malloc((size_t) draw_c * 9 * 4);
		//uint32_t* ind_data = (uint32_t*)malloc((size_t)draw_c * 4);


		int vert_i = 0;
		int int_i = 0;

		list->Tex->Bind(0);

		for (int k = 0; k < list->Draws.size(); k++) {

			for (int l = 0; l < 4; l++) {

				//ind_data.push_back((GLuint)int_i);
				idat[ic++] = int_i;
				int_i++;


			}

			DrawInfo* info = list->Draws[k];

			vdat[vc++] = info->x[0];
			vdat[vc++] = info->y[0];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;


			vdat[vc++] = info->x[1];
			vdat[vc++] = info->y[1];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 0;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[2];
			vdat[vc++] = info->y[2];
			vdat[vc++] = info->z;

			vdat[vc++] = 1;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			vdat[vc++] = info->x[3];
			vdat[vc++] = info->y[3];
			vdat[vc++] = info->z;

			vdat[vc++] = 0;
			vdat[vc++] = 1;

			vdat[vc++] = info->r;
			vdat[vc++] = info->g;
			vdat[vc++] = info->b;
			vdat[vc++] = info->a;

			/*
			
		

			// - V2

				vert_data.push_back((GLfloat)info->x[1]);
				vert_data.push_back((GLfloat)info->y[1]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)1);
				vert_data.push_back((GLfloat)0);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);

			// - V3

				vert_data.push_back((GLfloat)info->x[2]);
				vert_data.push_back((GLfloat)info->y[2]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)1);
				vert_data.push_back((GLfloat)1);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);

			// - v4

				vert_data.push_back((GLfloat)info->x[3]);
				vert_data.push_back((GLfloat)info->y[3]);
				vert_data.push_back((GLfloat)info->z);

				vert_data.push_back((GLfloat)0);
				vert_data.push_back((GLfloat)1);

				vert_data.push_back((GLfloat)info->r);
				vert_data.push_back((GLfloat)info->g);
				vert_data.push_back((GLfloat)info->b);
				vert_data.push_back((GLfloat)info->a);
				*/

				vert_i += 36;

		};

		
		glBindVertexArray(va);

		glBindBuffer(GL_ARRAY_BUFFER,vb);

		

		GLsizeiptr siz = ((GLsizeiptr)(vert_i) * 4);

		glBufferData(GL_ARRAY_BUFFER, siz, (const void*)vdat,GL_DYNAMIC_DRAW);

		

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * 4, 0);
		




		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT,false, 9 * 4, (void *)(3 * 4));
		


		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 9 * 4, (void *)(5 * 4));

		
	
		glDrawElements(GL_QUADS, draw_c, GL_UNSIGNED_INT, idat);

		
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glDeleteBuffers(1,&vb);
		//glDeleteVertexArrays(1, &va);

		

		list->Tex->Release(0);

	};


	fx->unbind();


};

DrawList* IDraw::GetDrawList(Texture2D* tex) {

	for (int i = 0; i < Draws.size(); i++) {

		DrawList* l = Draws[i];
		if (l->Tex == tex) {

			return l;

		}

	};

	DrawList * l = new DrawList;
	l->Tex = tex;
	l->Norm = NULL;
	Draws.push_back(l);
	return l;

};

void IDraw::DrawTexCoords(float* tx, float* ty, Texture2D* tex, Texture2D* norm, float r, float g, float b, float a) {


	DrawList* list = GetDrawList(tex);

	DrawInfo* info = new DrawInfo();

	info->x[0] = tx[0];
	info->x[1] = tx[1];
	info->x[2] = tx[2];
	info->x[3] = tx[3];

	info->y[0] = ty[0];
	info->y[1] = ty[1];
	info->y[2] = ty[2];
	info->y[3] = ty[3];

	info->Tex = tex;
	info->Norm = norm;

	list->Norm = norm;

	info->z = drawZ;
	info->r = r;
	info->g = g;
	info->b = b;
	info->a = a;

	drawZ += 0.0001f;

	list->Draws.push_back(info);
}

void IDraw::DrawTexCoords(float* tx, float* ty, Texture2D* tex, float r, float g, float b, float a) {

	DrawList* list = GetDrawList(tex);

	DrawInfo* info = new DrawInfo();

	info->x[0] = tx[0];
	info->x[1] = tx[1];
	info->x[2] = tx[2];
	info->x[3] = tx[3];

	info->y[0] = ty[0];
	info->y[1] = ty[1];
	info->y[2] = ty[2];
	info->y[3] = ty[3];

	info->Tex = tex;
	info->Norm = NULL;

	info->z = drawZ;
	info->r = r;
	info->g = g;
	info->b = b;
	info->a = a;

	drawZ += 0.001f;

	list->Draws.push_back(info);

}

void IDraw::DrawTex(int x, int y, int w, int h, Texture2D* tex, float r, float g, float b, float a) {


	DrawList* list = GetDrawList(tex);

	DrawInfo* info = new DrawInfo();

	info->x[0] = x;
	info->x[1] = x + w;
	info->x[2] = x + w;
	info->x[3] = x;

	info->y[0] = y;
	info->y[1] = y;
	info->y[2] = y + h;
	info->y[3] = y + h;

	info->Tex = tex;

	info->z = drawZ;
	info->r = r;
	info->g = g;
	info->b = b;
	info->a = a;

	drawZ += 0.001f;

	list->Draws.push_back(info);

	//Draws.push_back(info);

};