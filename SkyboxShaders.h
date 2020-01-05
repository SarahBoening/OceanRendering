#ifndef SKYBOX_SHADERS_H
#define SKYBOX_SHADERS_H

#include "SimpleShaders.h"
#include "External Libraries\SOIL\include\SOIL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
class SkyboxShaders : public SimpleShaders
{
public:
	
	SkyboxShaders(int textureResolution, std::vector<std::string> texture_path, float waterHeight);
	~SkyboxShaders();
	void locateUniforms();
	void activate() override;

	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projMatrix);
	void setCameraPos(const glm::vec3& cameraPos);


private:

	GLuint generateSkyBox(int resolution, std::vector<std::string> texture_path);

	GLint mViewLocation = -1;
	GLint mProjectionLocation = -1;
	GLint mCubeSamplerLocation = -1;
	GLint mCameraPosLocation = -1;
	GLint mWaterHeightLocation = -1;
	GLint mTextureID;

	std::vector<std::string> mTexturePath;
	const float mWaterHeight;
};

#endif