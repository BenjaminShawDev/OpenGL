#pragma once
#include "Structures.h"
#include <vector>

namespace MeshLoader
{
	Mesh* Load(char* path);
	Mesh* LoadOBJ(char* path);
};