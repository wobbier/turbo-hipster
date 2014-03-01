/*
 * .obj Model Loader
 * By: Mitchell Andrews (Wobbier) / Robert Evola (RelishZombie)
 * November 11, 2013
 * Loads a .obj file into faces and vertices and then renders the model.
 */
#pragma once
#include "Vector3.h"
class Model {
public:
	Model(std::string);
	~Model();
	void Render();
private:
	Vector3<float>* vertices;
	Vector3<int>* faces;
	int vertSize, faceSize;
	std::string currentString;
	void addPoint(int);
	void addFace(int);
	bool fileLoaded = false;
};