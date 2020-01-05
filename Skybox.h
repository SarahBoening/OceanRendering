#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "VertexArrayObject.h"

class Skybox : public VertexArrayObject {

public:
	Skybox(float size);
	~Skybox();
private:
	void drawVAOPostions();

	float mSize;
};

#endif