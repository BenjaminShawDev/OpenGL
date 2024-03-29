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

class Cube : public SceneObject
{
private:
	//static int numVertices, numColors, numIndices;
	GLfloat _rotation;
	Vector3 _position;
	GLfloat _objectAcceleration;

	float powerUpTimer;
public:
	//static bool Load(char* path);

	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void PowerUpAsteroid();

	float getXPosition();
	float getYPosition();
	float getZPosition();
};

