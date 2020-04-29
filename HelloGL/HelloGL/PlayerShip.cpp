#include "PlayerShip.h"

PlayerShip::PlayerShip(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 7.5f;
	_xRotation = 0.0f;
	_zRotation = 0.0f;
}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::Draw()
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
		glRotatef(_rotation, 0.0f, 0.0f, _zRotation);
		glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

//Ship movement
void PlayerShip::moveUp()
{
	if (_position.y < 3.7f)
	{
		_position.y += 0.1f;
		_xRotation = 1.0f;
	}
	_zRotation = 0.0f;
}

void PlayerShip::moveLeft()
{
	if (_position.x > -3.4f)
	{
		_position.x -= 0.1f;
		_zRotation = 1.0f;
	}
	else
	{
		_zRotation = 0.0f;
	}
	_xRotation = 0.0f;
}

void PlayerShip::moveRight()
{
	if (_position.x < 3.4f)
	{
		_position.x += 0.1f;
		_zRotation = -1.0f;
	}
	else
	{
		_zRotation = 0.0f;
	}
	_xRotation = 0.0f;
}

void PlayerShip::moveDown()
{
	if (_position.y > -3.7f)
		_position.y -= 0.1f;
	_zRotation = 0.0f;
	_xRotation = -1.0f;
}

float PlayerShip::getXPosition()
{
	return _position.x;
}

float PlayerShip::getYPosition()
{
	return _position.y;
}

float PlayerShip::getZPosition()
{
	return _position.z;
}