struct Finish {
	float ambient = 0.0f;
	float diffuse = 0.0f;
	float specular = 0.0f;
	float roughness = 0.0f;
	float metallic = 0.0f;
	float ior = 0.0f;

	float reflection = 0.0f;
	float refraction = 0.0f;
};

struct Pigment {
	bool filter;
	glm::vec3 color;
};

struct Transform {
	glm::vec3 translate;
	glm::vec3 rotate;
	glm::vec3 scale;
};

struct Object {
	virtual ~Object() = default;
	Finish finish;
	Pigment pigment;
	Transform transform;
	glm::vec3 center;
};

struct Sphere : Object {
  float radius;
};
struct Plane : Object {
  glm::vec3 normal;
  float distance;
};
struct Triangle : Object {
  glm::vec3 p1;
  glm::vec3 p2;
  glm::vec3 p3;
};
struct Box : Object {
  glm::vec3 min;
  glm::vec3 max;
  float radius;
  void setPoints(glm::vec3 center, glm::vec3 radius) {
  	min = center - radius;
  	max = center + radius;
  }
  void setPoints() {
  	min = center - glm::vec3(radius);
  	max = center + glm::vec3(radius);
  }
};

struct LightSource : Object {
	glm::vec3 location;
	glm::vec3 color;
};

struct Camera {
	glm::vec3 location;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 look_at;
};

struct Scene {
	Camera camera;
	std::vector<Object *> objects; 
	std::vector<LightSource> lightSources; 
};