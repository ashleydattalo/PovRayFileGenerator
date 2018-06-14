#ifndef CreatePovFileHPP
#define CreatePovFileHPP

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <typeinfo>
#include <stdio.h>
#include <string.h>
#include <memory>
#include <cstdlib>
#include <vector>
#include <sstream>

#include <glm/glm.hpp>

#include "structs.hpp"

class CreatePovFile {

public:
	CreatePovFile(std::string povFileName);
	~CreatePovFile();
	
	void createExampleScene();
	void setCamera();
	void setLightSources();
	void setPlanes();
	void setObjects();

	void writeScene();
	void writeCamera(Camera c);
	
	//writing light soures
	void writeLightSources(std::vector<LightSource> lightSources);
	void writeLightSource(LightSource ls);
	
	//writing object
	void writeObjects(std::vector<Object *> objects);
	void castAndWriteObject(Object *o);
	void writeSphere(Sphere *s);
	void writePlane(Plane *p);
	void writeTriangle(Triangle *t);
	void writeBox(Box *b);
	
	//writing extra object data
	void writeFinish(Finish finish);
	void writePigment(Pigment pigment);
	void writeTransform(Transform t);

	//Helpers
	void writeVec3(glm::vec3 vec);
	void writeVec4(glm::vec4 vec);

	// file opening/closing
	void openFile(std::string povFileName);
	void closeFile();
	
// private:
	std::string povFileName;
	std::ofstream file;
	std::string tab = "  ";
	Scene scene;
};

#endif