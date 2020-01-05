#ifndef WATER_SHADERS_H
#define WATER_SHADERS_H

#include "SimpleShaders.h"
#include "WaterFramebuffer.h"

#include "External Libraries\SOIL\include\SOIL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class WaterShaders : public SimpleShaders
{
public:
	explicit WaterShaders(std::vector<std::string> texturePaths, int textureResolution, glm::vec4 sunDirection, WaterFramebuffer* fbo, std::vector<std::string> textureCubePaths, float frequency, float amplitude, int tileFactor, int terrainResolution);
	virtual ~WaterShaders() = default;

	void locateUniforms();
	void activate() override;

	void setModelMatrix(const glm::mat4& transformMatrix);
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projMatrix);
	void setTime(const float time);
	void setClipPlane(const glm::vec4& clipPlane);
	void setCameraPos(const glm::vec3& cameraPos);

private:
	GLuint generateTexture(int resolution, const char* path);

	GLint mModelLocation = -1;
	GLint mModelInvTLocation = -1;
	GLint mViewLocation = -1;
	GLint mProjectionLocation = -1;
	GLint mTextureSampler1Location = -1;
	GLint mTextureSampler2Location = -1;
	GLint mTextureSampler4Location = -1;
	GLint mTextureSampler5Location = -1;
	GLint mTextureSampler6Location = -1;
	GLint mTextureSampler7Location = -1;
	GLint mWorldSunDirectionLocation = -1;
	GLint mClipplaneLocation = -1;
	GLint mCameraPosLocation = -1;
	GLint mAmplitudeLocation = -1;
	GLint mFrequencyLocation = -1;
	GLint mTimeLocation = -1;
	GLint mTileFactorLocation = -1;
	GLint mTerrainResolutionLocation = -1;
	GLuint mTextureID1;
	GLuint mTextureID2;
	GLuint mTextureID4;
	GLuint mTextureID5;
	GLuint mTextureID6;
	GLuint mTextureID7;

	glm::vec4 mSunDirection;
	float const mFrequency;
	float const mAmplitude;
	const int mTerrainResolution;
	const int mTileFactor;
};

#endif