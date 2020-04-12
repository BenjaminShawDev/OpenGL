#include "MeshLoader.h"
#include <iostream>
#include <fstream>
#include <vector>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh* mesh);
	//void LoadColours(ifstream& inFile, Mesh* mesh);
	void LoadTexCoords(ifstream& inFile, Mesh* mesh);
	void LoadNormals(ifstream& inFile, Mesh* mesh);
	void LoadIndices(ifstream& inFile, Mesh* mesh);

	void LoadVertices(ifstream& inFile, Mesh* mesh)
	{
		inFile >> mesh->numVertices;

		if (mesh->numVertices > 0)
		{
			mesh->Vertices = new Vertex[mesh->numVertices];

			for (int i = 0; i < mesh->numVertices; i++)
			{
				inFile >> mesh->Vertices[i].x;
				inFile >> mesh->Vertices[i].y;
				inFile >> mesh->Vertices[i].z;
			}
		}
	}

	//void LoadColours(ifstream& inFile, Mesh* mesh)
	//{
	//	inFile >> mesh->numColors;
	//	
	//	if (mesh->numColors > 0)
	//	{
	//		mesh->Colors = new Color[mesh->numColors];

	//		for (int i = 0; i < mesh->numColors; i++)
	//		{
	//			inFile >> mesh->Colors[i].r;
	//			inFile >> mesh->Colors[i].g;
	//			inFile >> mesh->Colors[i].b;
	//		}
	//	}
	//}

	void LoadTexCoords(ifstream& inFile, Mesh* mesh)
	{
		inFile >> mesh->TexCoordCount;

		if (mesh->TexCoordCount > 0)
		{
			mesh->TexCoords = new TexCoord[mesh->TexCoordCount];

			for (int i = 0; i < mesh->TexCoordCount; i++)
			{
				inFile >> mesh->TexCoords[i].u;
				inFile >> mesh->TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh* mesh)
	{
		inFile >> mesh->NormalCount;

		if (mesh->NormalCount > 0)
		{
			mesh->Normals = new Vector3[mesh->NormalCount];

			for (int i = 0; i < mesh->NormalCount; i++)
			{
				inFile >> mesh->Normals[i].x;
				inFile >> mesh->Normals[i].y;
				inFile >> mesh->Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh* mesh)
	{
		inFile >> mesh->numIndices;

		if (mesh->numIndices > 0)
		{
			mesh->Indices = new GLushort[mesh->numIndices];
			for (int i = 0; i < mesh->numIndices; i++)
			{
				inFile >> mesh->Indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, mesh);
		//LoadColours(inFile, mesh);
		LoadTexCoords(inFile, mesh);
		LoadNormals(inFile, mesh);
		LoadIndices(inFile, mesh);

		return mesh;
	}

	

	Mesh* LoadOBJ(char* inputfile)
	{
		Mesh* mesh = new Mesh();

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile);

		if (!warn.empty()) {
			std::cout << warn << std::endl;
		}

		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		if (!ret) {
			exit(1);
		}

		for (size_t s = 0; s < shapes.size(); s++) {
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				for (size_t v = 0; v < fv; v++) {

					mesh->numVertices += 3;
					mesh->NormalCount += 3;
					mesh->TexCoordCount += 2;
					mesh->numIndices += 1;
				}
				index_offset += fv;

				shapes[s].mesh.material_ids[f];
			}
		}

		mesh->Vertices = new Vertex[mesh->numVertices];
		mesh->TexCoords = new TexCoord[mesh->TexCoordCount];
		mesh->Normals = new Vector3[mesh->NormalCount];
		mesh->Indices = new GLushort[mesh->numIndices];

		int index = 0;

		for (size_t s = 0; s < shapes.size(); s++) {
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];
				for (size_t v = 0; v < fv; v++) {
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					mesh->Vertices[index].x = attrib.vertices[3 * idx.vertex_index + 0];
					mesh->Vertices[index].y = attrib.vertices[3 * idx.vertex_index + 1];
					mesh->Vertices[index].z = attrib.vertices[3 * idx.vertex_index + 2];
					mesh->Normals[index].x = attrib.normals[3 * idx.normal_index + 0];
					mesh->Normals[index].y = attrib.normals[3 * idx.normal_index + 1];
					mesh->Normals[index].z = attrib.normals[3 * idx.normal_index + 2];
					mesh->TexCoords[index].u = attrib.texcoords[2 * idx.texcoord_index + 0];
					mesh->TexCoords[index].v = attrib.texcoords[2 * idx.texcoord_index + 1];
					mesh->Indices[index] = index;

					index++;
				}
				index_offset += fv;

				shapes[s].mesh.material_ids[f];
			}
		}

		return mesh;
	}
}