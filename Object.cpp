#include "Object.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include"External Libraries/tiny_obj_loader.h"

using namespace glm;

Object::Object(const char* objectFile):
	mFile(objectFile)
{
		loadObject();
}

Object::Object(const char* objectFiles, vec3 position):
	mFile(objectFiles),
	mPosition(position)

{
	loadObject();
	translate(mPosition);
}

Object::Object(const char* objectFile, vec3 position, float scaleFactor) :
	mFile(objectFile),
	mPosition(position),
	mScale(scaleFactor)
{
	loadObject();
	scale(mScale);
	translate(mPosition);
}

Object::Object(const char* objectFile, vec3 position, float scaleFactor, int index) :
	mFile(objectFile),
	mPosition(position),
	mScale(scaleFactor),
	mIndex(index)
{
	loadObject();
	scale(mScale);
	translate(mPosition);
}

const mat4& Object::getModelMatrix() {
	mModelMatrix = mTranslationMatrix * mScaleMatrix * mRotationMatrix;
	return mModelMatrix;
}

int Object::getIndex()
{
	return mIndex;
}

std::string Object::getName()
{
	return mFile;
}

const glm::vec3& Object::getPostion() const
{
	return mPosition;
}

void Object::translate(vec3 const& v)
{
	mTranslationMatrix = glm::translate(mTranslationMatrix, v);
}

void Object::rotate(vec3 const& axis, float angle)
{
	mRotationMatrix = glm::rotate(mRotationMatrix, angle, axis);
}

void Object::scale(float scaleFactor)
{
	mScaleMatrix = glm::scale(mScaleMatrix,vec3(scaleFactor));
}

void Object::loadObject()
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err,mFile)) {
		printf("Error while loading obj: \s", mFile);
	}
	else
	{
		begin(GL_TRIANGLES);
		for (const auto& shape : shapes) {
			for (size_t f = 0; f < shape.mesh.indices.size() / 3; f++) {
				tinyobj::index_t idx0 = shape.mesh.indices[3 * f + 0];
				tinyobj::index_t idx1 = shape.mesh.indices[3 * f + 1];
				tinyobj::index_t idx2 = shape.mesh.indices[3 * f + 2];
				
				addVertex3f(attrib.vertices[3 * idx0.vertex_index + 0], attrib.vertices[3 * idx0.vertex_index + 1], attrib.vertices[3 * idx0.vertex_index + 2]);
				addVertex3f(attrib.vertices[3 * idx1.vertex_index + 0], attrib.vertices[3 * idx1.vertex_index + 1], attrib.vertices[3 * idx1.vertex_index + 2]);
				addVertex3f(attrib.vertices[3 * idx2.vertex_index + 0], attrib.vertices[3 * idx2.vertex_index + 1], attrib.vertices[3 * idx2.vertex_index + 2]);
				
				addNormal3f(attrib.normals[3 * idx0.normal_index + 0], attrib.normals[3 * idx0.normal_index + 1], attrib.normals[3 * idx0.normal_index + 2]);
				addNormal3f(attrib.normals[3 * idx1.normal_index + 0], attrib.normals[3 * idx1.normal_index + 1], attrib.normals[3 * idx1.normal_index + 2]);
				addNormal3f(attrib.normals[3 * idx2.normal_index + 0], attrib.normals[3 * idx2.normal_index + 1], attrib.normals[3 * idx2.normal_index + 2]);
				
				addTexCoord2f(attrib.texcoords[2 * idx0.texcoord_index], 1.0f - attrib.texcoords[2 * idx0.texcoord_index + 1]);
				addTexCoord2f(attrib.texcoords[2 * idx1.texcoord_index], 1.0f - attrib.texcoords[2 * idx1.texcoord_index + 1]);
				addTexCoord2f(attrib.texcoords[2 * idx2.texcoord_index], 1.0f - attrib.texcoords[2 * idx2.texcoord_index + 1]);
			}
		}
		end();
	}
}