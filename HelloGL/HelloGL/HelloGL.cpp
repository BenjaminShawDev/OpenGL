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
	speedPowerUpActive = false;
	slowPowerUpActive = false;
	beamPowerUpActive = false;
	newHighScore = false;
	wKeyDown = false;
	aKeyDown = false;
	dKeyDown = false;
	sKeyDown = false;
	score = 0;
	scoreTime = 0;
	powerUpTimer = 10000;
	numOfSpeedPowerUps = 0;
	numOfSlowPowerUps = 0;
	numOfBeamPowerUps = 0;

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
	delete startUpBackground;
	delete background;
	delete ship;
	for (int i = 0; i < 500; i++)
		delete asteroids[i];
	for (int i = 0; i < 3; i++)
		delete powerUps[i];
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
	startUpBackgroundTexture->Load((char*)"Textures/StartUpMenu2.raw", 1024, 1024);
	startUpBackground = new StartUpBackground(startUpBackgroundMesh, startUpBackgroundTexture, 0, 0, -65);

	Mesh* backgroundMesh = MeshLoader::Load((char*)"ObjectFiles/Background.txt");
	Texture2D* backgroundTexture = new Texture2D();
	backgroundTexture->Load((char*)"Textures/Space.raw", 1024, 1024);
	background = new StarBackground(backgroundMesh, backgroundTexture, 0, 0, -240);

	Mesh* AsteroidMesh = MeshLoader::LoadOBJ((char*)"ObjectFiles/Asteroid.obj");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Textures/Asteroid.raw", 512, 512);
	for (int i = 0; i < 500; i++)
	{
		asteroids[i] = new Asteroid(AsteroidMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 10000) / 10.0f);
	}

	//Mesh* powerUpMesh = MeshLoader::Load((char*)"ObjectFiles/PowerUp.txt");
	//Texture2D* powerUpTexture = new Texture2D();
	//powerUpTexture->Load((char*)"Textures/PowerUp.raw", 512, 512);
	//for (int i = 0; i < 3; i++)
	//{
	//	powerUps[i] = new PowerUp(powerUpMesh, powerUpTexture, ((rand() % 80) / 10.0f) - 4.0f, ((rand() % 70) / 10.0f) - 3.5f, -(rand() % 10000) / 10.0f);
	//}

	Mesh* powerUpMesh = MeshLoader::LoadOBJ((char*)"ObjectFiles/PowerUp.obj");
	Texture2D* powerUpTexture0 = new Texture2D();
	powerUpTexture0->Load((char*)"Textures/PowerUp.raw", 512, 512);
	Texture2D* powerUpTexture1 = new Texture2D();
	powerUpTexture1->Load((char*)"Textures/PowerUp2.raw", 512, 512);
	Texture2D* powerUpTexture2 = new Texture2D();
	powerUpTexture2->Load((char*)"Textures/PowerUp3.raw", 512, 512);
	powerUps[0] = new PowerUp(powerUpMesh, powerUpTexture0, ((rand() % 80) / 10.0f) - 4.0f, ((rand() % 70) / 10.0f) - 3.5f, -(rand() % 10000) / 10.0f);
	powerUps[1] = new PowerUp(powerUpMesh, powerUpTexture1, ((rand() % 80) / 10.0f) - 4.0f, ((rand() % 70) / 10.0f) - 3.5f, -(rand() % 10000) / 10.0f);
	powerUps[2] = new PowerUp(powerUpMesh, powerUpTexture2, ((rand() % 80) / 10.0f) - 4.0f, ((rand() % 70) / 10.0f) - 3.5f, -(rand() % 10000) / 10.0f);

	Mesh* shipMesh = MeshLoader::LoadOBJ((char*)"ObjectFiles/Ship.obj");
	Texture2D* shipTexture = new Texture2D();
	shipTexture->Load((char*)"Textures/ShipRedTexture.raw", 512, 512);
	ship = new PlayerShip(shipMesh, shipTexture, 0, 0, -10);

	Mesh* beamMesh = MeshLoader::LoadOBJ((char*)"ObjectFiles/Beam.obj");
	Texture2D* beamTexture = new Texture2D();
	beamTexture->Load((char*)"Textures/Beam.raw", 512, 512);
	powerUpBeam = new PowerUpBeam(beamMesh, beamTexture, 0, 0, -12);
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
	_lightPosition->x = 0.3;
	_lightPosition->y = 0.5;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.3;
	_lightData->Ambient.y = 0.3;
	_lightData->Ambient.z = 0.3;
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
	_material->Ambient.x = 1.0; _material->Ambient.y = 0.0; _material->Ambient.z = 1.0; _material->Ambient.w = 0.0;
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
		if (beamPowerUpActive)
		{
			powerUpBeam->Draw();
		}
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
		Vector3 v = { -0.05f, 0.35f, 0.0f };
		DrawString("GAME OVER", &v, &c);
		Vector3 v2 = { -0.05f, 0.325f, 0.0f };
		DrawString("SCORE: ", &v2, &c);
		Vector3 v3 = { 0.02f, 0.325f, 0.0f };
		DrawString(charScore, &v3, &c);
	}

	if (newHighScore)
	{
		Vector3 v = { -0.05f, 0.3f, 0.0f };
		DrawString("NEW HIGH SCORE!", &v, &c);
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
	}

	glutPostRedisplay();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	if (startGame && !isPlayerDead && !isPaused)
	{
		//Score system
		scoreTime++;
		if (scoreTime == 10)
		{
			score += 10;
			scoreTime = 0;
			if (speedPowerUpActive)
				score += 10;
		}

		//Movement
		if (wKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveUp();
			dynamic_cast<PowerUpBeam*>(powerUpBeam)->moveUp();
		}

		else if (aKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveLeft();
			dynamic_cast<PowerUpBeam*>(powerUpBeam)->moveLeft();
		}

		else if (dKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveRight();
			dynamic_cast<PowerUpBeam*>(powerUpBeam)->moveRight();
		}

		else if (sKeyDown == true)
		{
			dynamic_cast<PlayerShip*>(ship)->moveDown();
			dynamic_cast<PowerUpBeam*>(powerUpBeam)->moveDown();
		}

		CollisionDetection();
	}
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (startGame == false && key == ' ')
		startGame = true;
	if (startGame && !isPaused && !isPlayerDead && key == 'p')
		isPaused = true;
	else if (startGame && isPaused && key == 'p')
		isPaused = false;
	if (startGame && !doRestart && key == 'r')
		RestartGame();
	else if (key != 'r')
		doRestart = false;
	if (key == 'q')
		exit(0);

	//Movement
	if (startGame && key == 'w')
		wKeyDown = true;
	else if (key == 'a' || key == 's' || key == 'd')
		wKeyDown = false;
	if (startGame && key == 's')
		sKeyDown = true;
	else if (key == 'a' || key == 'w' || key == 'd')
		sKeyDown = false;
	if (startGame && key == 'a')
		aKeyDown = true;
	else if (key == 'w' || key == 's' || key == 'd')
		aKeyDown = false;
	if (startGame && key == 'd')
		dKeyDown = true;
	else if (key == 'a' || key == 's' || key == 'w')
		dKeyDown = false;
}

void HelloGL::CollisionDetection()
{
	float shipXPos = dynamic_cast<PlayerShip*>(ship)->getXPosition();
	float shipYPos = dynamic_cast<PlayerShip*>(ship)->getYPosition();
	float shipZPos = dynamic_cast<PlayerShip*>(ship)->getZPosition();

	for (int i = 0; i < 200; i++)
	{
		float asteroidXPos = dynamic_cast<Asteroid*>(asteroids[i])->getXPosition();
		float asteroidYPos = dynamic_cast<Asteroid*>(asteroids[i])->getYPosition();
		float asteroidZPos = dynamic_cast<Asteroid*>(asteroids[i])->getZPosition();

		float distance = ((shipXPos - asteroidXPos) * (shipXPos - asteroidXPos) + (shipYPos - asteroidYPos) * (shipYPos - asteroidYPos) + (shipZPos - asteroidZPos) * (shipZPos - asteroidZPos));

		if (distance <= 4.8f && !speedPowerUpActive && !isPlayerDead)
		{
			isPlayerDead = true;
			string highScore;
			int tempHighScore = 0;
			outStream.open("Highscore/Score.txt");
			getline(outStream, highScore);
			tempHighScore = stoi(highScore);
			outStream.close();
			if (score > tempHighScore)
			{
				newHighScore = true;
				inStream.open("Highscore/Score.txt");
				inStream << score << "\nSpeed powerups used: " << numOfSpeedPowerUps << "\nSlow powerups used: " << numOfSlowPowerUps << "\nBeam powerups used: " << numOfBeamPowerUps;
				inStream.close();
			}
		}

		//PowerUps
		if (speedPowerUpActive == true && powerUpTimer > 0 && !isPaused)
		{
			powerUpTimer--;
			dynamic_cast<Asteroid*>(asteroids[i])->SpeedPowerUpAsteroid();
		}
		else if (speedPowerUpActive == true && powerUpTimer <= 0)
		{
			speedPowerUpActive = false;
			powerUpTimer = 10000.0f;
		}
		if (slowPowerUpActive == true && powerUpTimer > 0 && !isPaused)
		{
			powerUpTimer--;
			dynamic_cast<Asteroid*>(asteroids[i])->SlowPowerUpAsteroid();
		}
		else if (slowPowerUpActive == true && powerUpTimer <= 0)
		{
			slowPowerUpActive = false;
			powerUpTimer = 10000.0f;
		}
		if (beamPowerUpActive == true && powerUpTimer > 0 && !isPaused)
		{
			powerUpTimer--;
			if (shipXPos - asteroidXPos >= -2.5f && shipXPos - asteroidXPos <= 2.5f && shipYPos - asteroidYPos >= -2.5f && shipYPos - asteroidYPos <= 2.5f)
				dynamic_cast<Asteroid*>(asteroids[i])->BeamPowerUpAsteroid();
		}
		else if (beamPowerUpActive == true && powerUpTimer <= 0)
		{
			beamPowerUpActive = false;
			powerUpTimer = 10000.0f;
		}

	}

	for (int i = 0; i < 3; i++)
	{
		float powerUpXPos = dynamic_cast<PowerUp*>(powerUps[i])->getXPosition();
		float powerUpYPos = dynamic_cast<PowerUp*>(powerUps[i])->getYPosition();
		float powerUpZPos = dynamic_cast<PowerUp*>(powerUps[i])->getZPosition();

		float distance = ((shipXPos - powerUpXPos) * (shipXPos - powerUpXPos) + (shipYPos - powerUpYPos) * (shipYPos - powerUpYPos) + (shipZPos - powerUpZPos) * (shipZPos - powerUpZPos));

		if (distance <= 3.5f && !isPlayerDead)
		{
			score += 20;
			if (i == 0)
			{
				speedPowerUpActive = true;
				numOfSpeedPowerUps++;
			}
			else if (i == 1)
			{
				beamPowerUpActive = true;
				numOfBeamPowerUps++;
			}
			else
			{
				slowPowerUpActive = true;
				numOfSlowPowerUps++;
			}
			dynamic_cast<PowerUp*>(powerUps[i])->PowerUpPickUp();
		}

		if (speedPowerUpActive && !isPaused)
			dynamic_cast<PowerUp*>(powerUps[i])->PowerUpPickUp();
	}
}

void HelloGL::RestartGame()
{
	score = 0;
	numOfSpeedPowerUps = 0;
	numOfSlowPowerUps = 0;
	numOfBeamPowerUps = 0;
	isPlayerDead = false;
	newHighScore = false;
	doRestart = true;
	wKeyDown = false;
	aKeyDown = false;
	sKeyDown = false;
	dKeyDown = false;

	system("CLS");
	InitObjects();
}