#include "HelloGL.h"
#include <ctime>
//#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));
	InitGL(argc, argv);
	InitObjects();
	InitLighting();
	LightingMaterial();

	startGame = false;
	isPlayerDead = false;
	isPaused = false;
	doRestart = false;
	powerUpActive = false;
	score = 0;
	scoreTime = 0;
	powerUpTimer = 5000;

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::InitObjects()
{
	camera = new Camera();

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	Mesh* startUpBackgroundMesh = MeshLoader::Load((char*)"ObjectFiles/Menu.txt");
	Texture2D* startUpBackgroundTexture = new Texture2D();
	startUpBackgroundTexture->Load((char*)"Textures/Menu2.raw", 512, 512);
	startUpBackground = new StartUpBackground(startUpBackgroundMesh, startUpBackgroundTexture, 0, 0, -65);

	Mesh* backgroundMesh = MeshLoader::Load((char*)"ObjectFiles/Background.txt");
	Texture2D* backgroundTexture = new Texture2D();
	backgroundTexture->Load((char*)"Textures/Space.raw", 1024, 1024);
	background = new StarBackground(backgroundMesh, backgroundTexture, 0, 0, -240);

	Mesh* cubeMesh = MeshLoader::Load((char*)"ObjectFiles/Cube.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Textures/Asteroid.raw", 512, 512);
	for (int i = 0; i < 500; i++)
	{
		asteroids[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 10000) / 10.0f);
	}

	Mesh* powerUpMesh = MeshLoader::Load((char*)"ObjectFiles/PowerUp.txt");
	Texture2D* powerUpTexture = new Texture2D();
	powerUpTexture->Load((char*)"Textures/PowerUp.raw", 512, 512);
	for (int i = 0; i < 3; i++)
	{
		powerUps[i] = new PowerUp(powerUpMesh, powerUpTexture, ((rand() % 80) / 10.0f) - 4.0f, ((rand() % 70) / 10.0f) - 3.5f, -(rand() % 10000) / 10.0f);
	}

	Mesh* shipMesh = MeshLoader::Load((char*)"ObjectFiles/TestShape.txt");
	Texture2D* shipTexture = new Texture2D();
	shipTexture->Load((char*)"Textures/ShipTexture.raw", 512, 512);
	ship = new PlayerShip(shipMesh, shipTexture, 0, 0, -10);
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(500, 300);
	glutCreateWindow("Asteroid Avoider");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set the viewport to be the entire window
	glViewport(0, 0, 800, 800);
	//Set the correct perspective
	gluPerspective(45, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D); //Needed otherwise you get white boxes
	glEnable(GL_NORMAL_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.2;
	_lightPosition->y = 0.5;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void HelloGL::LightingMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.2; _material->Ambient.z = 0.8; _material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.8; _material->Diffuse.z = 0.8; _material->Diffuse.w = 1.0;
	_material->Specular.x = 0.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	//glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)text);
	glPopMatrix();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the scene
	if (!startGame)
	{
		startUpBackground->Draw();
	}

	else if (startGame)
	{
		background->Draw();
		for (int i = 0; i < 200; i++)
		{
			asteroids[i]->Draw();
		}
		for (int i = 0; i < 3; i++)
		{
			powerUps[i]->Draw();
		}
		if (startGame && !isPlayerDead)
			ship->Draw();
	}
	std::string strScore = std::to_string(score);
	const char* charScore = strScore.c_str();
	Color c = { 0.0f, 0.0f, 0.0f };

	if (!isPlayerDead)
	{
		Vector3 v = { -0.4f, 0.39f, 0.0f };
		DrawString("SCORE: ", &v, &c);
		Vector3 v2 = { -0.32f, 0.39f, 0.0f };
		DrawString(charScore, &v2, &c);
	}

	if (isPaused && !isPlayerDead)
	{
		Vector3 v = { -0.05f, 0.05f, 0.0f };
		Color c2 = { 200.0f, 0.0f, 0.0f };
		DrawString("PAUSED", &v, &c2);
	}

	if (isPlayerDead)
	{
		Vector3 v3 = { -0.05f, 0.35f, 0.0f };
		DrawString("GAME OVER", &v3, &c);
		Vector3 v4 = { -0.05f, 0.325f, 0.0f };
		DrawString("SCORE: ", &v4, &c);
		Vector3 v5 = { 0.02f, 0.325f, 0.0f };
		DrawString(charScore, &v5, &c);
	}

	glFlush(); //Flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	if (startGame && !isPaused)
	{
		for (int i = 0; i < 200; i++)
			asteroids[i]->Update();
		for (int i = 0; i < 3; i++)
			powerUps[i]->Update();
		ship->Update();
	}
	glutPostRedisplay();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	if (startGame && !isPlayerDead && !isPaused)
	{
		scoreTime++;
		if (scoreTime == 10)
		{
			score += 10;
			scoreTime = 0;
			if (powerUpActive)
				score += 10;
		}
	}

	if (!isPlayerDead && !isPaused)
	{
		if (wKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveUp();
		}

		if (aKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveLeft();
		}

		if (dKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveRight();
		}

		if (sKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveDown();
		}
	}

	CollisionDetection();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (startGame == false && key == ' ')
		startGame = true;

	if (startGame && !isPaused && !isPlayerDead && key == 'p')
	{
		isPaused = true;
	}

	else if (startGame && isPaused && key == 'p')
	{
		isPaused = false;
	}

	if (startGame && !doRestart && key == 'r')
	{
		RestartGame();
	}

	else if (key != 'r')
	{
		doRestart = false;
	}

	if (key == 'q')
	{
		exit(0);
	}

	if (startGame && key == 'w')
	{
		wKeyDown = true;
	}

	else if (key != 'w')
	{
		wKeyDown = false;
	}

	if (startGame && key == 's')
	{
		sKeyDown = true;
	}

	else if (key != 's')
	{
		sKeyDown = false;
	}

	if (startGame && key == 'a')
	{
		aKeyDown = true;
	}

	else if (key != 'a')
	{
		aKeyDown = false;
	}

	if (startGame && key == 'd')
	{
		dKeyDown = true;
	}

	else if (key != 'd')
	{
		dKeyDown = false;
	}
}

void HelloGL::CollisionDetection()
{
	float shipXPos = dynamic_cast<PlayerShip*>(ship)->getXPosition();
	float shipYPos = dynamic_cast<PlayerShip*>(ship)->getYPosition();
	float shipZPos = dynamic_cast<PlayerShip*>(ship)->getZPosition();

	for (int i = 0; i < 200; i++)
	{
		float cubeXPos = dynamic_cast<Cube*>(asteroids[i])->getXPosition();
		float cubeYPos = dynamic_cast<Cube*>(asteroids[i])->getYPosition();
		float cubeZPos = dynamic_cast<Cube*>(asteroids[i])->getZPosition();

		float distance = ((shipXPos - cubeXPos) * (shipXPos - cubeXPos) + (shipYPos - cubeYPos) * (shipYPos - cubeYPos) + (shipZPos - cubeZPos) * (shipZPos - cubeZPos));

		if (distance <= 5.0f && !powerUpActive)
		{
			isPlayerDead = true;
		}

		if (powerUpActive == true && powerUpTimer > 0 && !isPaused)
		{
			powerUpTimer--;
			dynamic_cast<Cube*>(asteroids[i])->PowerUpAsteroid();
		}

		else if (powerUpActive == true && powerUpTimer <= 0)
		{
			powerUpActive = false;
			powerUpTimer = 5000.0f;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		float powerUpXPos = dynamic_cast<PowerUp*>(powerUps[i])->getXPosition();
		float powerUpYPos = dynamic_cast<PowerUp*>(powerUps[i])->getYPosition();
		float powerUpZPos = dynamic_cast<PowerUp*>(powerUps[i])->getZPosition();

		float distance = ((shipXPos - powerUpXPos) * (shipXPos - powerUpXPos) + (shipYPos - powerUpYPos) * (shipYPos - powerUpYPos) + (shipZPos - powerUpZPos) * (shipZPos - powerUpZPos));

		if (distance <= 3.0f && !isPlayerDead)
		{
			score += 50;
			powerUpActive = true;
		}

		if (powerUpActive && !isPaused)
		{
			dynamic_cast<PowerUp*>(powerUps[i])->PowerUpEffect();
		}
	}
}

void HelloGL::RestartGame()
{
	score = 0;
	isPlayerDead = false;
	doRestart = true;
	InitObjects();
}