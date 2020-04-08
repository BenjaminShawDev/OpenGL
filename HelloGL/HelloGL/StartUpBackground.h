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

class StartUpBackground : public SceneObject
{
private:
	Vector3 _position;
public:
	StartUpBackground(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~StartUpBackground();

	void Draw();
};

