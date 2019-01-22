// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	//Rodriques' rotation formula: cos(degrees) +sin(degrees)A* + (1 - cos(degrees))(axis(transpose(axis))
	vec3 axisr = glm::normalize(axis);
	float radians = (pi / 180) * degrees; 
	return 
		glm::cos(radians) * mat3(1) 
		+ glm::sin(radians) * mat3(0, -axisr.z, axisr.y, axisr.z, 0, -axisr.x, -axisr.y, axisr.x, 0)
		+ (1 - glm::cos(radians)) * mat3(axisr.x * axisr.x, axisr.x * axisr.y, axisr.x * axisr.z, axisr.x * axisr.y, axisr.y * axisr.y, axisr.y * axisr.z, axisr.x * axisr.z, axisr.y * axisr.z, axisr.z * axisr.z);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	eye = Transform::rotate(-degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 axisr = glm::cross(eye, up);
	eye = Transform::rotate(-degrees, axisr) * eye;
	up = Transform::rotate(-degrees, axisr) * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	//Center is (0,0,0).
	  //Have position of eye and up vector...
	vec3 w = glm::normalize(eye - vec3(0,0,0));
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::normalize(glm::cross(w, u));
	mat4 rotation = mat4(vec4(u, 0), vec4(v, 0), vec4(w, 0), vec4(0, 0, 0, 1));
	mat4 translation = mat4(vec4(1, 0, 0, -eye.x), vec4(0, 1, 0, -eye.y), vec4(0, 0, 1, -eye.z), vec4(0, 0, 0, 1));
	//GLM and OpenGL stores matrices in column major order ... WTF!
	return glm::transpose(rotation) * glm::transpose(translation);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}