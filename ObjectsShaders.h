#ifndef OBJECTS_SHADERS_H
#define OBJECTS_SHADERS_H

#include "SimpleShaders.h"
#include "External Libraries\SOIL\include\SOIL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class ObjectsShaders : public SimpleShaders
{
public:
	explicit ObjectsShaders(std::vector<std::string> textureFile, int textureResolution, float waterHeight, glm::vec4 sunDirection, int tileFactor, int terrainResolution);
	explicit ObjectsShaders(std::vector<std::string> textureFile, int textureResolution, int NumberOfRows, float waterHeight, glm::vec4 sunDirection, int tileFactor, int terrainResolution);
	virtual ~ObjectsShaders() = default;

	void locateUniforms();
	void activate() override;

	void setModelMatrix(const glm::mat4& transformMatrix);
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projMatrix);
	void setClipPlane(const glm::vec4& clipPlane);
	void setIndex(const int index);
	void setTime(const float timeModulo);
	void setCameraPos(const glm::vec3& cameraPos);


private:
	GLuint generateTexture(int resolution, const char* path);

	GLint mModelLocation = -1;
	GLint mViewLocation = -1;
	GLint mProjectionLocation = -1;
	GLint mTextureSampler1Location = -1;
	GLint mTextureSampler2Location = -1;
	GLint mClipplaneLocation = -1;
	GLint mTimeModuloLocation = -1;
	GLint mIndexLocation = -1;
	GLint mNumberOfRowsLocation = -1;
	GLint mCameraPosLocation = -1;
	GLint mWaterHeightLocation = -1;
	GLint mWorldSunDirectionLocation = -1;
	GLint mTileFactorLocation = -1;
	GLint mTerrainResolutionLocation = -1;
	GLuint mTextureID1;
	GLint mTextureID2;

	std::vector<GLuint> mFrameTexture;
	glm::vec4 mSunDirection;
	const float mWaterHeight;
	const int mTerrainResolution;
	const int mTileFactor;
	int mNumberOfRows = 1;
	int index = 0;
};

#endif