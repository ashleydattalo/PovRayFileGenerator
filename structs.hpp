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

//color gradient
struct ColorGradient
{
	int numColors = 0;
	std::vector<glm::vec4> colors;

	glm::vec3 hexToRGB(int hexValue) {
		glm::vec3 rgbColor;
		rgbColor.x = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
		rgbColor.y = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
		rgbColor.z = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte
		return rgbColor;
	}

	void addColor(glm::vec3 color) {
		colors.push_back(glm::vec4(color, 0.0f));
		numColors++;
	}
	void done() {
		float inc = 1.0f/(float)(numColors - 1);
		int i = 0;
		for (glm::vec4 &c : colors) {
			c.w = inc * i;
			i++;
		}
	}
	glm::vec3 get(float percent) {
		if (numColors == 0) {
			return glm::vec3(0.0f);
		}
		int i = 0;
		for (glm::vec4 currColor : colors) {
			if (percent < currColor.w) {
				glm::vec4 prevColor = colors[fmax(0, i - 1)];
				float valueDiff = prevColor.w - currColor.w;
				float fractBetween = (valueDiff==0) ? 0 : (percent - currColor.w) / valueDiff;
				float r, g, b;
				r   = (prevColor.x - currColor.x)*fractBetween + currColor.x;
			    g = (prevColor.y - currColor.y)*fractBetween + currColor.y;
			    b  = (prevColor.z - currColor.z)*fractBetween + currColor.z;
				return glm::vec3(r, g, b);
			}
			i++;
		}
		return glm::vec3(colors[0]);
	}
};

//Spiral
struct Spiral {
	float tStart;
	float tEnd;
	int numObjects;

	float radius;
	glm::vec3 offset;
	ColorGradient colGrad;

	//private variables
	//changing
	float tInc;
	int it;
	float t;
	glm::vec3 center;
	float percent; // 0 to 1;

	void setUp() {
		t = tStart;
		tInc = (glm::abs(tStart) + glm::abs(tEnd))/(float)(numObjects - 1);
		it = 0;
		percent = 0.0f; // 0 to 1 = 0.0f;
	}

	void step() {
		t += tInc;
		center.x = radius * glm::cos(t);
		center.z = radius * glm::sin(t);
		center.y = t*1.2f;

		// center.x = radius * glm::cos(t);
		// center.z = 0;
		// center.y = radius * glm::sin(t);

		// radius += 0.0

		center += offset;
		percent = (float)it / (float)(numObjects);
		it++;
	}
	Object *createObject() {
		Sphere *object = new Sphere();
		Pigment p;
		Finish f;
		f.ambient = 0.2f;
		f.diffuse = 0.4f;
		f.reflection = 0.1f;
		Transform transform;
		transform.scale = glm::vec3(1.0f);

		object->center = this->center;
		object->radius = 0.7;

		p.color = colGrad.get(percent);

		object->pigment = p;
		object->transform = transform;
		object->finish = f;
		return object;
	}

	std::vector<Object *> getObjects() {
		this->setUp();

		std::vector<Object *> objs;
		for (int i = 0; i < numObjects; i++) {
			this->step();
			objs.push_back(createObject());
		}
		return objs;
	}
};