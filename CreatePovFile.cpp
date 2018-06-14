#include "CreatePovFile.hpp"

CreatePovFile::CreatePovFile(std::string povFileName) :
	povFileName(povFileName)
{
	openFile(povFileName + ".pov");
	createExampleScene();
	writeScene();

	closeFile();

}
CreatePovFile::~CreatePovFile() {}
void CreatePovFile::createExampleScene() {
	setCamera();
	setLightSources();
	setPlanes();
	setObjects();
}

void CreatePovFile::setCamera() {
	Camera camera;
	camera.location = glm::vec3(0.0f, 0.0f,-15.0f);
	camera.up = glm::vec3(0.0f,1.0f,0.0f);
	camera.right = glm::vec3(1.333f, 0.0f, 0.0f);
	camera.look_at = glm::vec3(0.0f, 0.0f, 0.0f);
	scene.camera = camera;
}

void CreatePovFile::setLightSources() {
	std::vector<LightSource> lightSources;
	
	LightSource ls;
	ls.location = glm::vec3(10, 10, -10);
	ls.color  = glm::vec3(3.5, 3.5, 3.5);
	lightSources.push_back(ls);

	LightSource ls2;
	ls2.location = glm::vec3(-10, 10, -10);
	ls2.color  = glm::vec3(1.5, 1.5, 1.5);
	lightSources.push_back(ls2);

	scene.lightSources = lightSources;
}

void CreatePovFile::setPlanes() {
	Pigment p;
	Finish f;
	Transform transform;
	transform.scale = glm::vec3(1.0f);

	//gound plane
	Plane *plane = new Plane();
	plane->normal = glm::vec3(0.0f, 1.0f, 0.0f);
	plane->distance = -12.0f;
		p.color = glm::vec3(0.9f, 0.8f, 0.9f);
	plane->pigment = p;
	plane->transform = transform;
		f.ambient = 0.3f;
		f.diffuse = 0.5f;
		f.reflection = 0.6f;
	plane->finish = f;
	scene.objects.push_back(plane);
}

void CreatePovFile::setObjects() {
	Pigment p;
	p.color = glm::vec3(1.0f);

	Transform transform;
	transform.scale = glm::vec3(1.0f);

	Finish f;
	f.ambient = 0.2f;
	f.diffuse = 0.4f;
	f.reflection = 0.8f;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Box *s = new Box();
			s->center = glm::vec3(0.0f, 0.0f, 25.0f);
			s->radius = 5.0f;
			s->setPoints();
			transform.translate = glm::vec3(i*15.0f-15.0f, j*15.0f-15.0f, 0.0f);
			s->pigment = p;
			s->transform = transform;
			s->finish = f;
			scene.objects.push_back(s);
		}		
	}
}

void CreatePovFile::writeScene() {
	writeCamera(scene.camera);
	writeLightSources(scene.lightSources);
	writeObjects(scene.objects);
}

void CreatePovFile::writeCamera(Camera camera) {
	file << "camera {\n";
		file << tab << "location ";
		writeVec3(camera.location);
		file << tab << "\n";
		file << tab << "up ";
		writeVec3(camera.up);
		file << tab << "\n";
		file << tab << "right ";
		writeVec3(camera.right);
		file << tab << "\n";
		file << tab << "look_at ";
		writeVec3(camera.look_at);
		file << tab << "\n";
	file << "}";
	file << "\n";
}

void CreatePovFile::writeLightSources(std::vector<LightSource> lightSources) {
	for(LightSource ls : lightSources) {
		writeLightSource(ls);
	}
}

void CreatePovFile::writeLightSource(LightSource ls) {
	file << "\n";
	file << "lightsource {";
	writeVec3(ls.location);
	file << " color rgb ";
	writeVec3(ls.color);
	file << "}";
	file << "\n";
}

void CreatePovFile::writeObjects(std::vector<Object *> objects) {
	for (Object *o : objects ) {
		castAndWriteObject(o);
	}
}

void CreatePovFile::castAndWriteObject(Object *o) {
	if(Sphere *s = dynamic_cast<Sphere *>(o)) {
		writeSphere(s);
	}
	else if(Plane *p = dynamic_cast<Plane *>(o)) {
		writePlane(p);
	}
	else if(Triangle *t = dynamic_cast<Triangle *>(o)) {
		writeTriangle(t);
	}
	else if(Box *b = dynamic_cast<Box *>(o)) {
		writeBox(b);
	}
}

void CreatePovFile::writeSphere(Sphere *s) {
	file <<  "\n";
	file <<  "sphere { ";
	writeVec3(s->center);
	file <<  ", ";
	file <<  s->radius;
	
	writePigment(s->pigment);
	file << "\n";
	writeFinish(s->finish);
	file << "\n";
	writeTransform(s->transform);
	file << "\n";

	file <<  "}";
	file <<  "\n";
}

void CreatePovFile::writePlane(Plane *p) {
	file <<  "\n";
	file <<  "plane { ";
	writeVec3(p->normal);
	file <<  ", ";
	file <<  p->distance;
	
	writePigment(p->pigment);
	file << "\n";
	writeFinish(p->finish);
	file << "\n";
	writeTransform(p->transform);
	file << "\n";

	file <<  "}";
	file <<  "\n";
}

void CreatePovFile::writeTriangle(Triangle *t) {
	file <<  "\n";
	file <<  "triangle { ";
	file <<  "\n" << tab;
	writeVec3(t->p1);
	file <<  ", ";
	file <<  "\n" << tab;
	writeVec3(t->p2);
	file <<  ", ";
	file <<  "\n" << tab;
	writeVec3(t->p3);
	
	writePigment(t->pigment);
	file << "\n";
	writeFinish(t->finish);
	file << "\n";
	writeTransform(t->transform);
	file << "\n";

	file <<  "}";
	file <<  "\n";
}

void CreatePovFile::writeBox(Box *b) {
	file <<  "\n";
	file <<  "box { ";
	writeVec3(b->min);
	file <<  ", ";
	writeVec3(b->max);
	
	writePigment(b->pigment);
	file << "\n";
	writeFinish(b->finish);
	file << "\n";
	writeTransform(b->transform);
	file << "\n";

	file <<  "}";
	file <<  "\n";
}

void CreatePovFile::writeFinish(Finish finish) {
	file << tab << "finish {";
	file << "\n";
	file << tab << tab << " ambient " << finish.ambient;
	file << " diffuse " << finish.diffuse;
	file << " specular " << finish.specular;
	file << " roughness " << finish.roughness;
	file << " ior " << finish.ior;
	file << " reflection " << finish.reflection;
	file << " refraction " << finish.refraction;
	file << "\n";
	file << tab << "}";
}

void CreatePovFile::writePigment(Pigment pigment) {
	file << "\n";
	if (pigment.filter) {
		file << tab << "pigment { color rgbf ";
		writeVec4(glm::vec4(pigment.color, 1.0f));
	}
	else {
		file << tab << "pigment { color rgb ";
		writeVec3(pigment.color);
	}
	file <<  " }";
}

void CreatePovFile::writeTransform(Transform t) {
	file << tab << "translate ";
	writeVec3(t.translate);
	
	file << "\n";
	file << tab << "scale ";
	writeVec3(t.scale);

	file << "\n";
	file << tab << "rotate ";
	writeVec3(t.rotate);
}

void CreatePovFile::writeVec3(glm::vec3 vec) {
	file << "<";
	file << (double)vec.x;
	file << ", ";
	file << (double)vec.y;
	file << ", ";
	file << (double)vec.z;
	file << ">";
}

void CreatePovFile::writeVec4(glm::vec4 vec) {
	file << "<";
	file << vec.x;
	file << ", ";
	file << vec.y;
	file << ", ";
	file << vec.z;
	file << ", ";
	file << vec.w;
	file << ">";
}

void CreatePovFile::openFile(std::string povFileName) {
	file.open(povFileName);
}
void CreatePovFile::closeFile() {
	file.close();
}