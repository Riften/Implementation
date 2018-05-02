#include "plydecoder.h"
#include <iostream>
using namespace std;
PLY::PLY() {
	vertice = NULL;
	faces = NULL;
	verticeNum = 0;
	faceNum = 0;
	xmax = -1000;
	xmin = 1000;
	ymax = -1000;
	ymin = 1000;
	zmax = -1000;
	zmin = 1000;
}

PLY::~PLY() {
	if (vertice != NULL) {
		delete[]vertice;
	}
	if (faces != NULL) {
		delete[]faces;
	}
}

void PLY::Load(char* filePath, const float& scale = 1.0, Material* _material = NULL) {

	FILE* file = fopen(filePath, "r");
	char buffer[500];
	float x, y, z;
	int tmp, v1, v2, v3;

	//Decode the header.
	while (strncmp("element vertex", buffer, strlen("element vertex")) != 0)
	{
		fgets(buffer, 300, file);
	}
	strcpy(buffer, buffer + strlen("element vertex"));
	sscanf(buffer, "%i", &verticeNum);
	while (strncmp("element face", buffer, strlen("element face")) != 0)
	{
		fgets(buffer, 300, file);
	}
	strcpy(buffer, buffer + strlen("element face"));
	sscanf(buffer, "%i", &faceNum);

	while (strncmp("end_header", buffer, strlen("end_header")) != 0)
	{
		fgets(buffer, 300, file);
	}
	vertice = new GVector3[verticeNum];
	faces = new face[faceNum];


	for (int i = 0; i < verticeNum; i++)
	{
		fgets(buffer, 300, file);
		sscanf(buffer, "%f %f %f", &x, &y, &z);
		vertice[i] = GVector3(x*scale, y*scale, z*scale);
	}

	for (int i = 0; i < faceNum; i++)
	{
		fgets(buffer, 300, file);
		sscanf(buffer, "%i %i %i %i", &tmp, &v1, &v2, &v3);
		faces[i].set(vertice[v1], vertice[v2], vertice[v3], _material);
		xmax = (xmax > vertice[v1].x ? xmax : vertice[v1].x);
		xmax = (xmax > vertice[v2].x ? xmax : vertice[v2].x);
		xmax = (xmax > vertice[v3].x ? xmax : vertice[v3].x);
		ymax = (ymax > vertice[v1].y ? ymax : vertice[v1].y);
		ymax = (ymax > vertice[v2].y ? ymax : vertice[v2].y);
		ymax = (ymax > vertice[v3].y ? ymax : vertice[v3].y);
		zmax = (zmax > vertice[v1].z ? zmax : vertice[v1].z);
		zmax = (zmax > vertice[v2].z ? zmax : vertice[v2].z);
		zmax = (zmax > vertice[v3].z ? zmax : vertice[v3].z);
		xmin = (xmin < vertice[v1].x ? xmin : vertice[v1].x);
		xmin = (xmin < vertice[v2].x ? xmin : vertice[v2].x);
		xmin = (xmin < vertice[v3].x ? xmin : vertice[v3].x);
		ymin = (ymin < vertice[v1].y ? ymin : vertice[v1].y);
		ymin = (ymin < vertice[v2].y ? ymin : vertice[v2].y);
		ymin = (ymin < vertice[v3].y ? ymin : vertice[v3].y);
		zmin = (zmin < vertice[v1].z ? zmin : vertice[v1].z);
		zmin = (zmin < vertice[v2].z ? zmin : vertice[v2].z);
		zmin = (zmin < vertice[v3].z ? zmin : vertice[v3].z);

	}
}

void PLY::showLimit() {
	cout << "xmax:" << xmax << "\txmin:" << xmin << endl;
	cout << "ymax:" << ymax << "\tymin:" << ymin << endl;
	cout << "zmax:" << zmax << "\tzmin:" << zmin << endl;
}