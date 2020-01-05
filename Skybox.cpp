#include "Skybox.h"

Skybox::Skybox(float size):
	mSize(size)
{
	drawVAOPostions();
}


Skybox::~Skybox()
{
}

void Skybox::drawVAOPostions()
{
	begin(GL_TRIANGLES);

	addVertex3f(-(mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));
	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));
	addVertex3f(-(mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));

	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));
	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f(-(mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));
	addVertex3f(-(mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));
	addVertex3f(-(mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));

	addVertex3f((mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));

	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));
	addVertex3f(-(mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));
	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));

	addVertex3f(-(mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f(-(mSize/2.0f), (mSize/2.0f), (mSize/2.0f));
	addVertex3f(-(mSize/2.0f), (mSize/2.0f), -(mSize/2.0f));

	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), -(mSize/2.0f));
	addVertex3f(-(mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));
	addVertex3f((mSize/2.0f), -(mSize/2.0f), (mSize/2.0f));

	end();
}