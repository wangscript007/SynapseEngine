#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "DataTypes.h"
#include "VString.h"
#include <vector>
#pragma once
#define PY_SSIZE_T_CLEAN
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif



#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif


enum NodeType {
	
	TypeLight,TypeNode,TypeEntity,TypeCam

};

class NodeBase
{
public:

	NodeBase();
	Vect3 GetPosition();
	Vect3 GetScale();
	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();

	glm::vec3 GetPositionGL() {

		return LocalPos;

	}

	glm::vec3 GetScaleGL() {

		return LocalScale;

	}

	glm::mat4 GetTurnGL() {

		return LocalTurn;

	}

	void SetRotation(glm::mat4 m);
	virtual void SetPosition(Vect3 pos);
	virtual void SetPosition(float x, float y, float z);

	void LookAt(Vect3 p);
	void LookAt(float x, float y, float z);
	void SetScale(Vect3 scale);
	void Rotate(float p, float y, float r);
	void Turn(float p, float y, float r);
	void Move(float x, float y, float z);
	glm::mat4 GetRotation() {
		return LocalTurn;
	}
	glm::mat4 GetWorldRotation() {

		glm::mat4 t = glm::mat4(1.0f);

		if (Root != NULL) {
			t = Root->GetWorldRotation();
		}

		return LocalTurn * t;

	}
	virtual glm::mat4 GetWorld();
	void Add(NodeBase* node);
	NodeBase* GetSub(int id);
	int NumSub();
	std::vector<NodeBase*> GetSub();
	void SetRoot(NodeBase* node);
	NodeBase* GetRoot();
	const char* GetName() {
		return Name;
	}
	void SetName(const char* name) {
		Name = name;
	}

	NodeBase* FindNode(const char* name) {

		if (VString(name).IsSame(VString(Name)))
		{

			return this;

		}

		for (int i = 0; i < Sub.size(); i++) {

			auto nb = Sub[i];

			NodeBase* r = nb->FindNode(name);
			if (r != NULL) {
				return r;
			}

		}

		return NULL;

	}

	void Test() {

		printf("Node turned!\n");

	}

	Vect3 GetFlatCol() {
		return FlatCol;
	}

	void SetFlatCol(Vect3 c) {

		FlatCol = c;

	}
	NodeType GetType() {
		return Type;
	}

	glm::mat4 GetWorldTurn() {

		glm::mat4 r = glm::mat4(1.0f);
		if (Root != NULL) {
			r = Root->GetWorldTurn();
		}
		return r * LocalTurn;

	}

	void BeginRun() {

		

		for (int i = 0; i < Sub.size(); i++) {

			Sub[i]->BeginRun();

		}

	}

	void EndRun() {

	

	}

	void UpdateNode() {




		for (int i = 0; i < Sub.size(); i++) {

			Sub[i]->UpdateNode();

		}


	}

	void SetScript(const char* s) {

		
	//	test1 = sm->GetFunc("createNode");
		//test1->Call();
		//test1->BeginPars(2);
		//test1->AddInt(25);
		//test1->AddString("Antony Wells");
		//test1->AddPtr((void*)this);
		//test1->CallPars();

	//	auto obj = test1->ReturnObj();

	//	auto t2 = sm->GetFunc("testNode");
	//	t2->BeginPars(1);
//		t2->AddString("Hey now!");
	//	t2->AddObj(obj);

	//	t2->CallPars();

	
	
		
		//printf("Ret:%d\n", test1->ReturnInt());

	}

	void AddRotate(float x, float y, float z);

protected:
	glm::mat4 LocalTurn;
	glm::vec3 LocalScale;
	glm::vec3 LocalPos;

	Vect3 FlatCol;

	std::vector<NodeBase*> Sub;

	NodeBase* Root = NULL;
	const char* Name = "";
	NodeType Type;



};

