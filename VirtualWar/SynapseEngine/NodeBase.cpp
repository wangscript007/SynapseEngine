#include "NodeBase.h"
#include "TMaths.h"

NodeBase::NodeBase() {

	LocalTurn = glm::mat4(1.0f);
	LocalScale = glm::vec3(1, 1, 1);
	LocalPos = glm::vec3(0, 0, 0);
	Sub.resize(0);
	FlatCol = Vect3(1, 1, 1);
	Type = NodeType::TypeNode;


}

void NodeBase::Add(NodeBase* node) {

	Sub.push_back(node);
	node->SetRoot(this);

}

void NodeBase::SetRotation(glm::mat4 m) {

	LocalTurn = m;

}


NodeBase* NodeBase::GetSub(int id) {

	return Sub[id];

}

int NodeBase::NumSub() {

	return Sub.size();

}

std::vector<NodeBase*> NodeBase::GetSub() {

	return Sub;

}


Vect3 NodeBase::GetPosition() {

	return Vect3(LocalPos);

}

void NodeBase::SetPosition(Vect3 pos) {

	LocalPos = glm::vec3(pos.X, pos.Y, pos.Z);

}

Vect3 NodeBase::GetScale() {

	return Vect3(LocalScale);

}

void NodeBase::SetScale(Vect3 sc)
{

	LocalScale = glm::vec3(sc.X, sc.Y, sc.Z);

}

glm::mat4 NodeBase::GetWorld() {

	glm::mat4 prev = glm::mat4(1.0f);
	if (Root != NULL) {
		prev = Root->GetWorld();
	}

	//return glm::mat4(1.0f);
	glm::mat4 id = glm::mat4(1.0f);

	glm::mat4 tm = glm::translate<float>(id,LocalPos);
		
	glm::mat4 scal = glm::scale(id, LocalScale);



	//Scale, then rotate, then position, then apply previous world matrix.
	return prev*(tm*LocalTurn*scal);
	//return prev * tm * LocalTurn * scal;
	//return scal * LocalTurn * tm * prev;


}

void NodeBase::Move(float x, float y, float z) {

	glm::mat4 id = glm::mat4(1.0f);

	LocalPos = LocalPos + glm::vec3(GetWorldTurn() * glm::vec4(glm::vec3(x, y, z), 1.0));
	//printf("MX:%f MY:%f MZ:%f\n", x, y, z);

//	LocalPos += LocalTurn *= glm::vec3(x, y, z);//  LocalTurn;



}

void NodeBase::Rotate(float p, float y, float r) {

	p = TMaths::DegToRad(p);
	y = TMaths::DegToRad(y);
	r = TMaths::DegToRad(r);

	glm::mat4 id = glm::mat4(1.0f);

	glm::mat4 rot = glm::rotate(id,y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, p, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, r, glm::vec3(0, 0, 1));
	LocalTurn = rot;


}

void NodeBase::AddRotate(float p, float y, float r) {

	p = TMaths::DegToRad(p);
	y = TMaths::DegToRad(y);
	r = TMaths::DegToRad(r);

	glm::mat4 id = glm::mat4(1.0f);

	glm::mat4 rot = glm::rotate(id, y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, p, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, r, glm::vec3(0, 0, 1));
	LocalTurn = LocalTurn * rot;
}

void NodeBase::SetRoot(NodeBase* node) {

	Root = node;

}

NodeBase* NodeBase::GetRoot() {

	return Root;

}

void NodeBase::SetPosition(float x, float y, float z) {

	LocalPos = glm::vec3(x, y, z);

}

float NodeBase::GetPositionX() {

	return LocalPos.x;

}

float NodeBase::GetPositionY() {

	return LocalPos.y;

}

float NodeBase::GetPositionZ() {

	return LocalPos.z;

}

void NodeBase::LookAt(Vect3 p) {

	glm::vec3 np;
	np.x = p.X - LocalPos.x;
	np.y = p.Y - LocalPos.y;
	np.z = p.Z - LocalPos.z;

	LocalTurn = glm::lookAt(LocalPos, glm::vec3(p.X,p.Y,p.Z), glm::vec3(0, 1, 0));
//	LocalTurn = glm::inverse(LocalTurn);

	LocalTurn[3] = glm::vec4(0, 0, 0, 1);
	LocalTurn = glm::inverse(LocalTurn);

}

void NodeBase::LookAt(float x, float y, float z) {

	LookAt(Vect3(x, y, z));

}

void NodeBase::Turn(float p, float y, float r) {

	p = TMaths::DegToRad(p);
	y = TMaths::DegToRad(y);
	r = TMaths::DegToRad(r);

	glm::mat4 id = glm::mat4(1.0f);

	glm::mat4 rot = glm::rotate(id, y, glm::vec3(0, 0, 1));
	rot = glm::rotate(rot, p, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, r, glm::vec3(0, 1, 0));

	LocalTurn = rot * LocalTurn;

}