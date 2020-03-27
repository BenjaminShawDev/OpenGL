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
	//Vector3 _position;
	HelloGL* hellogl;
	float _translateX, _translateY;
public:
	//static bool Load(char* path);

	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void moveLeft();

	Vector3 _position;
};

