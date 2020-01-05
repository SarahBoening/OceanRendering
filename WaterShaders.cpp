#include "WaterShaders.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
using namespace glm;

WaterShaders::WaterShaders(std::vector<std::string> texturePaths, int textureResolution, vec4 sunDirection, WaterFramebuffer* fbo, std::vector<std::string> textureCubePaths, float frequency, float amplitude, int tileFactor, int terrainResolution) :
	mSunDirection(sunDirection),
	mAmplitude(amplitude),
	mFrequency(frequency),
	mTileFactor(tileFactor),
	mTerrainResolution(terrainResolution)
{
	mTextureID1 = fbo->getReflectionTexture();
	mTextureID2 = fbo->getRefractionTexture();
	mTextureID4 = generateTexture(textureResolution, texturePaths[0].c_str());
	mTextureID5 = generateTexture(textureResolution, texturePaths[1].c_str());
	mTextureID6 = generateTexture(textureResolution, texturePaths[2].c_str());
	mTextureID7 = generateTexture(textureResolution, texturePaths[3].c_str());
}

void WaterShaders::locateUniforms()
{
	glUseProgram(mShaderProgram);

	mModelLocation = glGetUniformLocation(mShaderProgram, "model");
	if (mModelLocation == -1)
		printf("[WaterShaders] Model location not found\n");

	mModelInvTLocation = glGetUniformLocation(mShaderProgram, "modelInvT");
	if (mModelInvTLocation == -1)
		printf("[WaterShaders] ModelInvT location not found\n");

	mViewLocation = glGetUniformLocation(mShaderProgram, "view");
	if (mViewLocation == -1)
		printf("[WaterShaders] View location not found\n");

	mProjectionLocation = glGetUniformLocation(mShaderProgram, "projection");
	if (mProjectionLocation == -1)
		printf("[WaterShaders] Projection location not found\n");

	mWorldSunDirectionLocation = glGetUniformLocation(mShaderProgram, "worldSunDirection");
	if (mWorldSunDirectionLocation == -1)
		printf("[WaterShaders] WorldSunDirection location not found\n");
	glUniform3fv(mWorldSunDirectionLocation, 1, &mSunDirection[0]);

	mAmplitudeLocation = glGetUniformLocation(mShaderProgram, "amplitude");
	if (mAmplitudeLocation == -1)
		printf("[WaterShaders] Amplitude not found\n");

	glUniform1f(mAmplitudeLocation, mAmplitude);

	mFrequencyLocation = glGetUniformLocation(mShaderProgram, "frequency");
	if (mFrequencyLocation == -1)
		printf("[WaterShaders] Frequency not found\n");
	glUniform1f(mFrequencyLocation, mFrequency);

	mTextureSampler1Location = glGetUniformLocation(mShaderProgram, "reflectionTexture");
	if (mTextureSampler1Location == -1)
		printf("[WaterShaders] Texture Sampler 1 location not found\n");
	glUniform1i(mTextureSampler1Location, 0);

	mTextureSampler2Location = glGetUniformLocation(mShaderProgram, "refractionTexture");
	if (mTextureSampler2Location == -1)
		printf("[WaterShaders] Texture Sampler 2 location not found\n");
	glUniform1i(mTextureSampler2Location, 1);

	mTextureSampler4Location = glGetUniformLocation(mShaderProgram, "waterNormal1");
	if (mTextureSampler4Location == -1)
		printf("[WaterShaders] Texture Sampler 4 location not found\n");
	glUniform1i(mTextureSampler4Location, 2);

	mTextureSampler5Location = glGetUniformLocation(mShaderProgram, "waterNormal2");
	if (mTextureSampler5Location == -1)
		printf("[WaterShaders] Texture Sampler 5 location not found\n");
	glUniform1i(mTextureSampler5Location, 3);
	
	mTextureSampler6Location = glGetUniformLocation(mShaderProgram, "waterDudv1");
	if (mTextureSampler6Location == -1)
		printf("[WaterShaders] Texture Sampler 6 location not found\n");
	glUniform1i(mTextureSampler6Location, 4);

	mTextureSampler7Location = glGetUniformLocation(mShaderProgram, "waterDudv2");
	if (mTextureSampler7Location == -1)
		printf("[WaterShaders] Texture Sampler 7 location not found\n");
	glUniform1i(mTextureSampler7Location, 5);

	mAmplitudeLocation = glGetUniformLocation(mShaderProgram, "amplitude");
	if (mAmplitudeLocation == -1)
		printf("[WaterShaders] Amplitude not found\n");
	glUniform1f(mAmplitudeLocation, mAmplitude);

	mFrequencyLocation = glGetUniformLocation(mShaderProgram, "frequency");
	if (mFrequencyLocation == -1)
		printf("[WaterShaders] Frequency not found\n");
	glUniform1f(mFrequencyLocation, mFrequency);

	mTimeLocation = glGetUniformLocation(mShaderProgram, "time");
	if (mTimeLocation == -1)
		printf("[WaterShaders] Time location not found\n");

	mClipplaneLocation = glGetUniformLocation(mShaderProgram, "clipPlane");
	if (mClipplaneLocation == -1)
		printf("[WaterShaders] Clipplane location not found\n");

	mTileFactorLocation = glGetUniformLocation(mShaderProgram, "tileFactor");
	if (mTileFactorLocation == -1)
		printf("[WaterShaders] tilefactor location not found\n");
	glUniform1i(mTileFactorLocation, mTileFactor);

	mTerrainResolutionLocation = glGetUniformLocation(mShaderProgram, "terrainResolution");
	if (mTerrainResolutionLocation == -1)
		printf("[WaterShaders] terrainresolution location not found\n");
	glUniform1i(mTerrainResolutionLocation, mTerrainResolution);
}

void WaterShaders::activate()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mTextureID2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mTextureID4);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, mTextureID5);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, mTextureID6);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, mTextureID7);

	SimpleShaders::activate();
}


void WaterShaders::setModelMatrix(const mat4& transformMatrix)
{
	if (mModelLocation < 0)
		printf("[WaterShaders] uniform location for 'model' not known\n");

	glUseProgram(mShaderProgram);
	glUniformMatrix4fv(mModelLocation, 1, GL_FALSE, &transformMatrix[0][0]);


	if (mModelInvTLocation < 0)
		printf("[WaterShaders] uniform location for 'modelInvT' not known\n");

	mat3 normalMatrix = mat3(transformMatrix);
	normalMatrix = glm::transpose(glm::inverse(normalMatrix));
	glUniformMatrix3fv(mModelInvTLocation, 1, GL_FALSE, &normalMatrix[0][0]);
}


// View Matrix
void WaterShaders::setViewMatrix(const glm::mat4& viewMatrix)
{
	if (mViewLocation < 0)
		printf("[WaterShaders] uniform location for 'view' not known\n");

	glUseProgram(mShaderProgram);
	glUniformMatrix4fv(mViewLocation, 1, GL_FALSE, &viewMatrix[0][0]);

}

// Projection Matrix
void WaterShaders::setProjectionMatrix(const glm::mat4& projMatrix)
{
	if (mProjectionLocation < 0)
		printf("[WaterShaders] uniform location for 'projection' not known\n");

	glUseProgram(mShaderProgram);
	glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, &projMatrix[0][0]);
}

void WaterShaders::setTime(const float time)
{
	if(mTimeLocation < 0)
		printf("[WaterShaders] uniform location for 'time' not found\n");
	glUniform1f(mTimeLocation, time);
}

void WaterShaders::setClipPlane(const vec4& clipPlane)
{
	if (mClipplaneLocation < 0)
		printf("[WaterShaders] uniform location for 'clipplane' not found\n");

	glUseProgram(mShaderProgram);
	glUniform4fv(mClipplaneLocation,1, &clipPlane[0]);
}

void WaterShaders::setCameraPos(const vec3& cameraPos)
{
	if (mCameraPosLocation < 0)
		printf("[WaterShaders] uniform location for 'cameraPosition' not found\n");

	glUseProgram(mShaderProgram);
	glUniform3fv(mCameraPosLocation, 1, &cameraPos[0]);
}

// Load texture set all parameters
GLuint WaterShaders::generateTexture(int imageResolution, const char* path)
{
	GLuint mId;
	unsigned char* texture_data = SOIL_load_image(path, &imageResolution, &imageResolution, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageResolution, imageResolution, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	return mId;
}
