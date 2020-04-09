#include "PowerUp.h"

PowerUp::PowerUp(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0;
	_objectAcceleration = 0.1f;
}

PowerUp::~PowerUp()
{

}

void PowerUp::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->TexCoords != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void PowerUp::Update()
{
	_rotation += 0.2f;
	_position.z += _objectAcceleration;
	_objectAcceleration += 0.0005f;

	if (_position.z > 150.0f)
	{
		_position.x = ((rand() % 80) / 10.0f) - 4.0f;
		_position.y = ((rand() % 70) / 10.0f) - 3.5f;
		_position.z = -750.0f;
	}
}

void PowerUp::PowerUpEffect()
{
	_position.z += 15.0f;
}

float PowerUp::getXPosition()
{
	return _position.x;
}

float PowerUp::getYPosition()
{
	return _position.y;
}

float PowerUp::getZPosition()
{
	return _position.z;
}

