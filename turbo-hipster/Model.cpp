/*
* .obj Model Loader
* By: Mitchell Andrews (Wobbier) / Robert Evola (RelishZombie)
* November 11, 2013
* Loads a .obj file into faces and vertices and then renders the model.
*/
#include "Vaereal.h"
#include "Model.h"
#include "GL\glut.h"

Model::Model(std::string filename)
{
	int tempVerts = 0;
	int tempFaces = 0;
	std::ifstream fileStream;
	fileStream.open(filename);
	if (fileStream.is_open()) {
		while (std::getline(fileStream, currentString)) {
			switch (currentString[0]) {
			case 'v':
				tempVerts++;
				std::cout << "Read Vert" << std::endl;
				break;
			case 'f':
				tempFaces++;
				std::cout << "Read Face" << std::endl;
				break;
			}
		}
		vertices = new Vector3<float>[tempVerts];
		faces = new Vector3<int>[tempFaces];
		tempVerts = 0;
		tempFaces = 0;
		fileStream.clear();
		fileStream.seekg(0, std::ios::beg);
		while (std::getline(fileStream, currentString)) {
			switch (currentString[0]) {
			case 'v':
				addPoint(tempVerts);
				tempVerts++;
				break;
			case 'f':
				addFace(tempFaces);
				tempFaces++;
				break;
			}
		}
		fileStream.close();
		fileLoaded = true;
		vertSize = tempVerts;
		faceSize = tempFaces;
	}
}


Model::~Model()
{
	delete [] vertices;
	delete [] faces;
}

void Model::Render()
{
	if (fileLoaded)
	{
		for (int i = 0; i < faceSize; i++)
		{
			glBegin(GL_POLYGON);
			glVertex3f(vertices[faces[i].x].x, vertices[faces[i].x].y, vertices[faces[i].x].z);
			glVertex3f(vertices[faces[i].y].x, vertices[faces[i].y].y, vertices[faces[i].y].z);
			glVertex3f(vertices[faces[i].z].x, vertices[faces[i].z].y, vertices[faces[i].z].z);
			glEnd();
		}
	}
}

void Model::addPoint(int currentVert)
{
	int stringPos;
	std::string tempString;
	for (int i = 0; i < 3; ++i)  {
		stringPos = currentString.find_last_of(" ");
		tempString = currentString.substr(stringPos+1);
		if (i == 0) vertices[currentVert].x = std::stof(tempString.c_str());
		if (i == 1) vertices[currentVert].y = std::stof(tempString.c_str());
		if (i == 2) vertices[currentVert].z = std::stof(tempString.c_str());
		currentString = currentString.erase(stringPos, currentString.length());
	}
}

void Model::addFace(int currentFace)
{
	int stringPos;
	std::string tempString;
	for (int i = 0; i < 3; ++i)  {
		stringPos = currentString.find_last_of(" ");
		tempString = currentString.substr(stringPos + 1);
		if (i == 0) faces[currentFace].x = std::stoi(tempString.c_str()) - 1;
		if (i == 1) faces[currentFace].y = std::stoi(tempString.c_str()) - 1;
		if (i == 2) faces[currentFace].z = std::stoi(tempString.c_str()) - 1;
		currentString = currentString.erase(stringPos, currentString.length());
	}
}