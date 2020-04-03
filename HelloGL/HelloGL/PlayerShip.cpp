#include "PlayerShip.h"

PlayerShip::PlayerShip(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
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
		//glRotatef(_rotation, 1.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void PlayerShip::Update()
{

}

void PlayerShip::moveUp()
{
	_position.y += MOVEMENT_SPEED;
}

void PlayerShip::moveLeft()
{
	_position.x -= MOVEMENT_SPEED;
}

void PlayerShip::moveRight()
{
	_position.x += MOVEMENT_SPEED;
}

void PlayerShip::moveDown()
{
	_position.y -= MOVEMENT_SPEED;
}