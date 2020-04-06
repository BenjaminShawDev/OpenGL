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
	int score = 0;

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

	Mesh* backgroundMesh = MeshLoader::Load((char*)"ObjectFiles/Background.txt");
	Texture2D* backgroundTexture = new Texture2D();
	backgroundTexture->Load((char*)"Textures/Space.raw", 1024, 1024);
	background = new StarBackground(backgroundMesh, backgroundTexture, 0, 0, -240);

	Mesh* cubeMesh = MeshLoader::Load((char*)"ObjectFiles/Cube.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Textures/Asteroid.raw", 512, 512);
	for (int i = 0; i < 500; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 10000) / 10.0f);
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
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");
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
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.2;
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
	_material->Ambient.x = 0.6; _material->Ambient.y = 0.3; _material->Ambient.z = 0.6; _material->Ambient.w = 1.0;
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
	background->Draw();
	for (int i = 0; i < 200; i++)
	{
		objects[i]->Draw();
	}
	if (startGame && !isPlayerDead)
		ship->Draw();

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

	if (isPlayerDead)
	{
		Vector3 v3 = { -0.05f, 0.05f, 0.0f };
		DrawString("GAME OVER", &v3, &c);
		Vector3 v4 = { -0.05f, 0.0f, 0.0f };
		DrawString("SCORE: ", &v4, &c);
		Vector3 v5 = { 0.02f, 0.0f, 0.0f };
		DrawString(charScore, &v5, &c);
	}



	glFlush(); //Flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	if (startGame)
	{
		for (int i = 0; i < 200; i++)
			objects[i]->Update();
		ship->Update();
	}
	glutPostRedisplay();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	if (startGame && !isPlayerDead)
	{
		score += 10;
	}

	if (wKeyDown == true && !isPlayerDead)
	{
		dynamic_cast<PlayerShip*>(ship)->moveUp();
	}

	if (aKeyDown == true && !isPlayerDead)
	{
		dynamic_cast<PlayerShip*>(ship)->moveLeft();
	}

	if (dKeyDown == true && !isPlayerDead)
	{
		dynamic_cast<PlayerShip*>(ship)->moveRight();
	}

	if (sKeyDown == true && !isPlayerDead)
	{
		dynamic_cast<PlayerShip*>(ship)->moveDown();
	}

	CollisionDetection();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	
	//if (key == 'w')
	//{		
	//	for (int i = 0; i < 500; i++)
	//	{
	//		dynamic_cast<Cube*>(objects[i])->moveUp();
	//	}
	//}

	//if (key == 's')
	//{
	//	for (int i = 0; i < 500; i++)
	//	{
	//		dynamic_cast<Cube*>(objects[i])->moveDown();
	//	}
	//}

	//if (key == 'a')
	//{
	//	for (int i = 0; i < 500; i++)
	//	{
	//		dynamic_cast<Cube*>(objects[i])->moveLeft();
	//	}
	//}

	//if (key == 'd')
	//{
	//	for (int i = 0; i < 500; i++)
	//	{
	//		dynamic_cast<Cube*>(objects[i])->moveRight();
	//	}
	//}

	if (startGame == false && key == ' ')
		startGame = true;

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

//void HelloGL::Keyboard(unsigned char key, int x, int y)
//{
//	if (key == 'w')
//		camera->eye.z -= 0.1f;
//
//	if (key == 's')
//		camera->eye.z += 0.1f;
//
//	if (key == 'a')
//		camera->eye.x += 0.1f;
//
//	if (key == 'd')
//		camera->eye.x -= 0.1f;
//}

void HelloGL::CollisionDetection()
{
	float shipXPos = dynamic_cast<PlayerShip*>(ship)->getXPosition();
	float shipYPos = dynamic_cast<PlayerShip*>(ship)->getYPosition();
	float shipZPos = dynamic_cast<PlayerShip*>(ship)->getZPosition();

	for (int i = 0; i < 200; i++)
	{
		float cubeXPos = dynamic_cast<Cube*>(objects[i])->getXPosition();
		float cubeYPos = dynamic_cast<Cube*>(objects[i])->getYPosition();
		float cubeZPos = dynamic_cast<Cube*>(objects[i])->getZPosition();

		//cout << "Cube " << i << " X: " << cubeXPos << " Y: " << cubeYPos << endl;

		float distance = ((shipXPos - cubeXPos) * (shipXPos - cubeXPos) + (shipYPos - cubeYPos) * (shipYPos - cubeYPos) + (shipZPos - cubeZPos) * (shipZPos - cubeZPos));
		//cout << distance << endl;

		if (distance <= 5.0f)
		{
			isPlayerDead = true;
		}
	}


}