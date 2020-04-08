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
#include "PlayerShip.h"
#include "StarBackground.h"
#include "StartUpBackground.h"
#include "PowerUp.h"
#include <string>

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
	void CollisionDetection();
	void RestartGame();

	bool _move;

private:
	Camera* camera;
	//Cube* cube[200];
	SceneObject* asteroids[500];
	SceneObject* powerUps[3];
	SceneObject* ship;
	SceneObject* background;
	SceneObject* startUpBackground;
	Vector4* _lightPosition;
	Lighting* _lightData;
	Material* _material;
	Cube* cube;

	bool startGame;
	bool isPlayerDead;
	bool isPaused;
	bool doRestart;
	bool powerUpActive;
	int scoreTime;
	int score;
	int powerUpTimer;

	bool wKeyDown = false;
	bool aKeyDown = false;
	bool dKeyDown = false;
	bool sKeyDown = false;
};
