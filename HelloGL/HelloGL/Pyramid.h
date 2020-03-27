#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:
	Vector3 _position;
public:
	//static bool Load(char* path);

	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();
};