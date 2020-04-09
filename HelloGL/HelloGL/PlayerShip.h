#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include <fstream>
#include <iostream>
#include "SceneObject.h"
#include "HelloGL.h"

class HelloGL;

class PlayerShip : public SceneObject
{
private:
	GLfloat _rotation;
	GLfloat _zRotation;
	GLfloat _xRotation;
	Vector3 _position;
public:
	PlayerShip(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~PlayerShip();

	void Draw();
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();

	float getXPosition();
	float getYPosition();
	float getZPosition();
};

