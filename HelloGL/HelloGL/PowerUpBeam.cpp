#include "PowerUpBeam.h"

PowerUpBeam::PowerUpBeam(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject (mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

PowerUpBeam::~PowerUpBeam()
{

}

void PowerUpBeam::Draw()
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
		glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void PowerUpBeam::moveUp()
{
	if (_position.y < 3.7f)
		_position.y += 0.1f;
}

void PowerUpBeam::moveLeft()
{
	if (_position.x > -3.4f)
		_position.x -= 0.1f;
}

void PowerUpBeam::moveRight()
{
	if (_position.x < 3.4f)
		_position.x += 0.1f;
}

void PowerUpBeam::moveDown()
{
	if (_position.y > -3.7f)
		_position.y -= 0.1f;
}