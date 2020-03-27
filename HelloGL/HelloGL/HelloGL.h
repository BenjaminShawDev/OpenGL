#pragma once
#define REFRESHRATE 16
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "MeshLoader.h"
#include "Pyramid.h"

class Cube;

class HelloGL
{
public:
	//Constructor definition
	HelloGL(int argc, char*argv[]);
	//Destructor
	~HelloGL(void);
	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();
	void LightingMaterial();
	void DrawString(const char* text, Vector3* position, Color* color);

	bool _move;

private:
	Camera* camera;
	//Cube* cube[200];
	SceneObject* objects[1000];
	Vector4* _lightPosition;
	Lighting* _lightData;
	Material* _material;
	Cube* cube;
};
