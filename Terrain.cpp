#include "Terrain.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <GL/freeglut.h>

#ifndef TYPE_WATER
#define TYPE_WATER 1
#endif
#ifndef TYPE_SEA
#define TYPE_SEA 2
#endif
#ifndef TYPE_DEFAULT
#define TYPE_DEFAULT 0
#endif

using namespace glm;

Terrain::Terrain(int resolution, int tileNumber, bool generateHeightValues)
{
	mFrequency = 1.0;
	mAmplitude = 1.0;
	mResolution = resolution;
    mHeight.resize(resolution*resolution); //mHeight.size = resolution^2 => store all values needed for grid in this vector
	mTileNumber = tileNumber;
	// flat grid
    for (int i = 0 ; i < (resolution*resolution); i++)
		mHeight[i] = 0.0f;
	
	setVAOPositions(generateHeightValues);
}

Terrain::Terrain(int resolution, int tileNumber, bool generateHeightValues, float frequency, float amplitude)
{
	mFrequency = frequency;
	mAmplitude = amplitude;
	mResolution = resolution;
	mHeight.resize(resolution*resolution); //mHeight.size = resolution^2 => store all values needed for grid in this vector
	mTileNumber = tileNumber;
	// flat grid
	for (int i = 0; i < (resolution*resolution); i++)
		mHeight[i] = 0.0f;

	setVAOPositions(generateHeightValues);
}

Terrain::~Terrain()
{
}

void Terrain::generateHeight()
{

	for (int z = 1; z < mResolution; z++) {
		for (int x = 1; x < mResolution; x++)
			setHeight(x, z, perlin2D(x,z) * mAmplitude);
	}
}

float Terrain::hash(vec2 v)
{
	return fract(1e4 * sin(17.0f * v.x + v.y * 0.1f) * (0.1f + abs(sin(v.y * 13.0f + v.x))));
}

float Terrain::perlin2D(int x, int z)
{
	vec2 p = vec2(x,z) * mFrequency;
	vec2 i = floor(p);
	vec2 f = fract(p);

	// Four corners in 2D of a tile
	float a = hash(i);
	float b = hash(i + vec2(1.0, 0.0));
	float c = hash(i + vec2(0.0, 1.0));
	float d = hash(i + vec2(1.0, 1.0));

	vec2 u = f * f*f*(f*(f*6.0f - 15.0f) + 10.0f);
	return mix(a, b, u.x) + (c - a) * u.y * (1.0f - u.x) + (d - b) * u.x * u.y;
}

void Terrain::drawSimplePlane() {
	begin(GL_QUADS);

	addVertex3f(0.0f, 0.0f, 0.0f);
	addVertex3f((float)mResolution, 0.0f, 0.0f);
	addVertex3f((float)mResolution, 0.0f, (float)mResolution);
	addVertex3f(0.0f, 0.0f, (float)mResolution);

	addTexCoord2f(0.0f, 0.0f);
	addTexCoord2f(1.0f, 0.0f);
	addTexCoord2f(0.0f, 1.0f);
	addTexCoord2f(1.0f, 1.0f);

	end();
}

void Terrain::setVAOPositions(bool generateHeightValues)
{
	if (generateHeightValues)
		generateHeight();

	vec3 n;

	begin(GL_TRIANGLES);

	for (int z = 1; z < mResolution - 1; z++) {

		for (int x = 1; x < mResolution - 1; x++) {

			// calculate normals
			n.x = getHeight(x - 1, z) - getHeight(x + 1, z);
			n.y = 2.0f;
			n.z = getHeight(x, z - 1) - getHeight(x, z + 1);
			n = normalize(n);
			addNormal3f(n.x, n.y, n.z);

			addVertex3f(static_cast<float>(x), getHeight(x, z), static_cast<float>(z));

			// calculate texture coordinates
			float s = x / static_cast<float>(mResolution - 1) * mTileNumber;
			float t = z / static_cast<float>(mResolution - 1) * mTileNumber;

			addTexCoord2f(s, t);

			// calculate indices
			if (z < mResolution - 3 && x < mResolution - 3) {

				addIndex1ui(calcIndex(x, z));
				addIndex1ui(calcIndex(x+1, z));
				addIndex1ui(calcIndex(x+1 , z+1));

				addIndex1ui(calcIndex(x, z));
				addIndex1ui(calcIndex(x+1, z+1));
				addIndex1ui(calcIndex(x, z+1));
			}
		}
    }
	end();
}


void Terrain::setHeight(int x, int z, float height)
{
	if (getHeight(x, z) == 0)
		mHeight[z*mResolution + x] = height;
}

float Terrain::getHeight(int x, int z) const
{
	return mHeight[z*mResolution + x];

}

// return the height value for when the terrain has already been translated to (0,0,0)
float Terrain::getHeightValue(float x, float z) const
{
	x += static_cast<int>(mResolution / 2.0f);
	z += static_cast<int>(mResolution / 2.0f);
	return mHeight[z*mResolution + x];

}

int Terrain::calcIndex(int x, int z)
{
	return z * (mResolution - 2) + x;
}
