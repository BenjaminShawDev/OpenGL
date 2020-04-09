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

class PowerUp : public SceneObject
{
private:
	GLfloat _rotation;
	Vector3 _position;
	GLfloat _objectAcceleration;
public:
	PowerUp(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~PowerUp();

	void Draw();
	void Update();
	void PowerUpEffect();

	float getXPosition();
	float getYPosition();
	float getZPosition();
};