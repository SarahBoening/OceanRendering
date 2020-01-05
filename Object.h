#ifndef OBJECT_H
#define OBJECT_H

#include "VertexArrayObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace glm;

class Object : public VertexArrayObject {
public:

	Object(const char* objectFiles);
	Object(const char* objectFiles, vec3 position);
	Object(const char* objectFiles, vec3 position, float scale);
	Object(const char* objectFiles, vec3 position, float scale, int index);
	virtual ~Object() = default;

	const mat4& getModelMatrix();
	void translate(vec3 const& v);
	void rotate(vec3 const& axis, float angle);
	void scale(float scale);
	int getIndex();
	std::string getName();
	const glm::vec3& getPostion() const;

	mat4 mTranslationMatrix = mat4{ 1.0f };
	mat4 mRotationMatrix = mat4{ 1.0f };
	mat4 mScaleMatrix = mat4{ 1.0f };
	mat4 mModelMatrix = mat4{ 1.0f };

private:
	void loadObject();

	const char* mFile;
	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec2> mUVs;
	std::vector<glm::vec3> mNormals;

	glm::vec3 mPosition;
	float mScale;
	int mIndex = 0;
};
#endif
