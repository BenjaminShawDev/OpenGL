#pragma once
#define REFRESHRATE 16
#include <Windows.h>
#include <stdlib.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h" //freeglut library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Asteroid.h"
#include "MeshLoader.h"
#include "PlayerShip.h"
#include "StarBackground.h"
#include "StartUpBackground.h"
#include "PowerUp.h"
#include "PowerUpBeam.h"
#include <string>
#include <fstream>

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

private:
	Camera* camera;
	//Cube* cube[200];
	SceneObject* asteroids[500];
	SceneObject* powerUps[3];
	SceneObject* ship;
	SceneObject* background;
	SceneObject* startUpBackground;
	SceneObject* powerUpBeam;
	Vector4* _lightPosition;
	Lighting* _lightData;
	Material* _material;
	fstream outStream;
	ofstream inStream;

	bool startGame;
	bool isPlayerDead;
	bool isPaused;
	bool doRestart;
	bool speedPowerUpActive;
	bool slowPowerUpActive;
	bool beamPowerUpActive;
	bool newHighScore;
	bool wKeyDown, aKeyDown, sKeyDown, dKeyDown;
	float powerUpTimer;
	int scoreTime;
	int score;
	int numOfSpeedPowerUps;
	int numOfSlowPowerUps;
	int numOfBeamPowerUps;
};
