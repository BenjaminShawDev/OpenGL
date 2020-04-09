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

class PowerUpBeam : public SceneObject
{
private:
	Vector3 _position;
public:
	PowerUpBeam(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~PowerUpBeam();

	void Draw();
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();
};

