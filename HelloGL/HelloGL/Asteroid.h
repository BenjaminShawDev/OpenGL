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

class Asteroid : public SceneObject
{
private:
	//static int numVertices, numColors, numIndices;
	GLfloat _rotation;
	Vector3 _position;
	GLfloat _objectAcceleration;
	float powerUpTimer;
	bool slowPowerUpActive;

public:
	//static bool Load(char* path);

	Asteroid(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Asteroid();

	void Draw();
	void Update();
	void SpeedPowerUpAsteroid();
	void SlowPowerUpAsteroid();
	void BeamPowerUpAsteroid();

	float getXPosition();
	float getYPosition();
	float getZPosition();
};

