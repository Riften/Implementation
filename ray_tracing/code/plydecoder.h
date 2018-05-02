#include <stdio.h>
#include <string>
#include <string.h>
#include "gvector.h"
#include "object.h"

class PLY {
public:
	int verticeNum;
	int faceNum;
	float xmax, xmin, ymax, ymin, zmax, zmin;
	GVector3* vertice;
	face* faces;
	PLY();
	~PLY();
	void Load(char* filePath, const float& scale, Material* _material);
	void showLimit();

};