#include "Asteroid.h"

Asteroid::Asteroid(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_rotation = 0.0f;
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_objectAcceleration = 0.1f;
	powerUpTimer = 5000;
	slowPowerUpActive = false;
}

Asteroid::~Asteroid()
{

}

void Asteroid::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->TexCoords != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Asteroid::Update()
{
	//_rotation += 0.3f;
	_rotation += ((rand() % 150) / 100.0f) + 0.1f;
	_position.z += _objectAcceleration;
	_objectAcceleration += 0.0005f;

	if (_position.z > 150.f)
	{
		_position.x = ((rand() % 400) / 10.0f) - 20.0f;
		_position.y = ((rand() % 200) / 10.0f) - 10.0f;
		_position.z = -600.0f;
	}
}

void Asteroid::SpeedPowerUpAsteroid()
{
	_position.z += 5.0f;
}

void Asteroid::SlowPowerUpAsteroid()
{
	_position.z -= _objectAcceleration;
	_position.z += 0.1f;
}

void Asteroid::BeamPowerUpAsteroid()
{
	_position.z -= 300.0f;
}

float Asteroid::getXPosition()
{
	return _position.x;
}

float Asteroid::getYPosition()
{
	return _position.y;
}

float Asteroid::getZPosition()
{
	return _position.z;
}