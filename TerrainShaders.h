#ifndef TERRAIN_SHADERS_H
#define TERRAIN_SHADERS_H

#include "SimpleShaders.h"
#include "External Libraries\SOIL\include\SOIL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class TerrainShaders : public SimpleShaders
{
public:
	explicit TerrainShaders(std::vector<std::string> textureFile, int textureResolution, glm::vec4 sunDirection, float waterHeight);
	virtual ~TerrainShaders() = default;

	void locateUniforms();
	void activate() override;

	void setModelMatrix(const glm::mat4& transformMatrix);
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projMatrix);
	void setClipPlane(const glm::vec4& clipPlane);
	void setTime(const float time, const float timeMS);
	void setCameraPos(const glm::vec3& cameraPos);

private:
	GLuint generateTexture(int resolution, const char* path);

	GLint mModelLocation = -1;
	GLint mModelInvTLocation = -1;
	GLint mViewLocation = -1;
	GLint mProjectionLocation = -1;
	GLint mTextureSampler1Location = -1;
	GLint mTextureSampler2Location = -1;
	GLint mTimeModuloLocation = -1;
	GLint mClipplaneLocation = -1;
	GLint mCameraPosLocation = -1;
	GLint mWorldSunDirectionLocation = -1;
	GLint mWaterHeightLocation = -1;

	GLuint mTextureID1;
	GLuint mTextureID2;
	std::vector<GLuint> mFrameTexture;
	glm::vec4 mSunDirection;
	const float mWaterHeight;
};

#endif