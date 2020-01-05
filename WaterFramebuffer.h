#ifndef WATER_FRAMEBUFFER_H
#define WATER_FRAMEBUFFER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include<stdio.h>

class WaterFramebuffer {
public:
	WaterFramebuffer(int width, int height);
	virtual ~WaterFramebuffer() = default;
	
	void setScreenViewport(int width, int height);
	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFramebuffer();
	const GLuint& getReflectionTexture() const { return reflectionTexture; };
	const GLuint& getRefractionTexture() const { return refractionTexture; };
	const GLuint& getRefractionDepthTexture() const { return refractionDepthTexture; };

private:
	
	void initialiseReflectionFrameBuffer();
	void initialiseRefractionFrameBuffer();
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(int width, int height);
	GLuint createDepthTextureAttachment(int width, int height);
	GLuint createDepthBufferAttachment(int width, int height);
	void bindFramebuffer(GLuint frameBuffer, int width, int height);
	

	const int REFLECTION_WIDTH = 320;
	const int REFLECTION_HEIGHT = 180;
	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;

	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;
	GLuint refractionFrameBuffer;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;

	int screenWidth;
	int screenHeight;
};

#endif

