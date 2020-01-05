#version 420

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 clipPlane;
uniform int numberOfRows;
uniform int index;
uniform int terrainResolution;
uniform int tileFactor;

layout(location = 0) in vec4 vPos;
layout(location = 2) in vec4 vNormal;
layout(location = 3) in vec4 vTexCoord;

out vec3 fWorldPos;
out vec4 fTexCoord;
out vec3 fWorldCam;
out vec3 fViewPos;
out vec2 fTexCoordCaustic;

vec2 calcIndexOffset()
{
	int column = int(floor(mod(index, numberOfRows)));
	float xOffset =  float(column)/ float(numberOfRows);
	
	int row = int(floor(index / numberOfRows));
	float  yOffset = float(row) / float(numberOfRows);
	
	return vec2(xOffset, yOffset);
}

void main()
{

	vec4 worldPos = model * vPos;
	gl_ClipDistance[0] = dot(worldPos, clipPlane);
	
    gl_Position = (projection * view * model) * vPos;       	
	
	fTexCoord = vTexCoord / numberOfRows + vec4(calcIndexOffset(), 0.0f, 0.0f); 
	fTexCoordCaustic = vec2(vPos.x / float(terrainResolution - 1) * tileFactor, vPos.z / float(terrainResolution - 1) * tileFactor);
	fWorldPos = (model * vPos).xyz;
	fWorldCam = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
	fViewPos = (view * model * vPos).xyz;                  

}