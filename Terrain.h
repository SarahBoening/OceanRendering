#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "VertexArrayObject.h"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;

class Terrain : public VertexArrayObject {

public:
    Terrain(int resolution, int tileNumber, bool generateHeightValues);
	Terrain(int resolution, int tileNumber, bool generateHeightValues, float frequency, float amplitude);
	~Terrain();
    
    void setHeight(int x, int z, float height);
    float getHeightValue(float x, float z) const;
	int calcIndex(int x, int z);

	void setVAOPositions(bool generateHeight);

private:     
	void drawSimplePlane();
	void generateHeight();
	float getHeight(int x, int z) const;
	float perlin2D(int x, int z);
	float hash(vec2 v);

    int mResolution;    
	int mTileNumber;
	std::vector<float> mHeight;
	float mFrequency;
	float mAmplitude;
};


#endif

