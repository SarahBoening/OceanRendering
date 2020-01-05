#include "TerrainShaders.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

TerrainShaders::TerrainShaders(std::vector<std::string> textureFile, int textureResolution, vec4 sunDirection, float waterHeight) :
	mSunDirection(sunDirection),
	mWaterHeight(waterHeight)
{
	mTextureID1 = generateTexture(textureResolution, textureFile[0].c_str());
	mTextureID2 = generateTexture(textureResolution, textureFile[1].c_str());

	for (int i = 2; i < textureFile.size(); i++)
		mFrameTexture.push_back(generateTexture(textureResolution, textureFile[i].c_str()));
}

void TerrainShaders::locateUniforms()
{
	glUseProgram(mShaderProgram);
	
	mModelLocation = glGetUniformLocation(mShaderProgram, "model");
	if (mModelLocation == -1)
		printf("[TerrainShaders] Model location not found\n");

	mModelInvTLocation = glGetUniformLocation(mShaderProgram, "modelInvT");
	if (mModelInvTLocation == -1)
		printf("[TerrainShaders] ModelInvT location not found\n");

	mViewLocation = glGetUniformLocation(mShaderProgram, "view");
	if (mViewLocation == -1)
		printf("[TerrainShaders] View location not found\n");

	mProjectionLocation = glGetUniformLocation(mShaderProgram, "projection");
	if (mProjectionLocation == -1)
		printf("[TerrainShaders] Projection location not found\n");

	mTextureSampler1Location = glGetUniformLocation(mShaderProgram, "seafloorTexture");
	if (mTextureSampler1Location == -1)
		printf("[TerrainShaders] Texture Sampler 1 location not found\n");
	glUniform1i(mTextureSampler1Location, 0);

	mTextureSampler2Location = glGetUniformLocation(mShaderProgram, "seafloorNormalTexture");
	if (mTextureSampler2Location == -1)
		printf("[TerrainShaders] Texture Sampler 2 location not found\n");
	glUniform1i(mTextureSampler2Location, 1);

	mTimeModuloLocation = glGetUniformLocation(mShaderProgram, "timeModulo");
	if (mTimeModuloLocation == -1)
		printf("[TerrainShaders] Time modulo location not found\n");

	mWorldSunDirectionLocation = glGetUniformLocation(mShaderProgram, "worldSunDirection");
	if (mWorldSunDirectionLocation == -1)
		printf("[TerrainShaders] WorldSunDirection location not found\n");
	glUniform3fv(mWorldSunDirectionLocation, 1, &mSunDirection[0]);

	mClipplaneLocation = glGetUniformLocation(mShaderProgram, "clipPlane");
	if (mClipplaneLocation == -1)
		printf("[TerrainShaders] Clipplane location not found\n");

	mCameraPosLocation = glGetUniformLocation(mShaderProgram, "camPos");
	if (mCameraPosLocation == -1)
		printf("[TerrainShaders] CameraLocation location not found\n");

	mWaterHeightLocation = glGetUniformLocation(mShaderProgram, "waterHeight");
	if (mWaterHeightLocation == -1)
		printf("[TerrainShaders] waterheight location not found\n");
	glUniform1f(mWaterHeightLocation, mWaterHeight);
}

void TerrainShaders::activate()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mTextureID2);

	for (int i = 0; i < mFrameTexture.size(); i++)
	{
		std::string currentSampler = "causticTexture" + std::to_string(i+1);
		GLint currentLocation = glGetUniformLocation(mShaderProgram, currentSampler.c_str());
		if (currentLocation < 0)
			printf("Location for \i not found",(i + 1));
		glUniform1i(currentLocation, (i+2));
		glActiveTexture(GL_TEXTURE0 + (i+2));
		glBindTexture(GL_TEXTURE_2D, mFrameTexture[i]);  
	}
	
	SimpleShaders::activate(); 
}


void TerrainShaders::setModelMatrix(const mat4& transformMatrix)
{
	if (mModelLocation < 0)
		printf("[TerrainShaders] uniform location for 'model' not known\n");

	glUseProgram(mShaderProgram);												
	glUniformMatrix4fv(mModelLocation, 1, GL_FALSE, &transformMatrix[0][0]);	
		if (mModelInvTLocation < 0)
			printf("[TerrainShaders] uniform location for 'modelInvT' not known\n");

	mat3 normalMatrix = mat3(transformMatrix);
	normalMatrix = glm::transpose(glm::inverse(normalMatrix));
	glUniformMatrix3fv(mModelInvTLocation, 1, GL_FALSE, &normalMatrix[0][0]);
}


// View Matrix
void TerrainShaders::setViewMatrix(const glm::mat4& viewMatrix)
{
	if (mViewLocation < 0)
		printf("[TerrainShaders] uniform location for 'view' not known\n");

	glUseProgram(mShaderProgram);
	glUniformMatrix4fv(mViewLocation, 1, GL_FALSE, &viewMatrix[0][0]);

}

// Projection Matrix
void TerrainShaders::setProjectionMatrix(const glm::mat4& projMatrix)
{
	if (mProjectionLocation < 0)
		printf("[TerrainShaders] uniform location for 'projection' not known\n");

	glUseProgram(mShaderProgram);
	glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, &projMatrix[0][0]);
}

void TerrainShaders::setClipPlane(const vec4& clipPlane)
{
	if (mClipplaneLocation < 0)
		printf("[TerrainShaders] uniform location for 'clipplane' not found\n");

	glUseProgram(mShaderProgram);
	glUniform4fv(mClipplaneLocation, 1, &clipPlane[0]);
}

void TerrainShaders::setTime(const float time, const float timeMS)
{
	if (mTimeModuloLocation < 0)
		printf("[TerrainShaders] uniform location for 'timeModulo' not found\n");

	glUseProgram(mShaderProgram);
	glUniform1i(mTimeModuloLocation, (int(timeMS) % 16));
}

void TerrainShaders::setCameraPos(const vec3& cameraPos)
{
	if (mCameraPosLocation < 0)
		printf("[TerrinShaders] uniform location for 'cameraPosition' not found\n");

	glUseProgram(mShaderProgram);
	glUniform3fv(mCameraPosLocation, 1, &cameraPos[0]);
}

// Load texture set all parameters
GLuint TerrainShaders::generateTexture(int imageResolution, const char* path)
{
	GLuint mId = 0;
	unsigned char* texture_data = SOIL_load_image(path, &imageResolution, &imageResolution, 0, SOIL_LOAD_RGBA);
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageResolution, imageResolution, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	return mId;
}