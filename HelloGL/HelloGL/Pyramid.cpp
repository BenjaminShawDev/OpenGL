#include "Pyramid.h"

//Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
//{
//	_position.x = x;
//	_position.y = y;
//	_position.z = z;
//}
//
//Pyramid::~Pyramid()
//{
//
//}
//
//void Pyramid::Draw()
//{
//	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr)
//	{
//		glEnableClientState(GL_VERTEX_ARRAY);
//		glEnableClientState(GL_COLOR_ARRAY);
//		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
//		glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
//
//		glPushMatrix();
//		glTranslatef(_position.x, _position.y, _position.z);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
//		glPopMatrix();
//
//		glDisableClientState(GL_COLOR_ARRAY);
//		glDisableClientState(GL_VERTEX_ARRAY);
//	}
//}
//
//void Pyramid::Update()
//{
//
//}