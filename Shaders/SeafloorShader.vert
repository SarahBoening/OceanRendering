#version 420

uniform mat4 model;
uniform mat3 modelInvT;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 clipPlane;

layout(location = 0) in vec4 vPos;
layout(location = 2) in vec4 vNormal;
layout(location = 3) in vec4 vTexCoord;

out vec4 fTexCoord;
out vec3 fViewPos;
out vec3 fWorldCam;
out vec3 fWorldPos;
out vec3 fWorldNormal;
out mat3 fModelInvT;

//------------------------------------------------------------------------------------------------------------------
// MAIN 
//------------------------------------------------------------------------------------------------------------------
void main()
{

	vec4 worldPos = model * vPos;
	gl_ClipDistance[0] = dot(worldPos, clipPlane);
	
    gl_Position = (projection * view * model) * vPos;       	
	fTexCoord = vTexCoord; 
	fWorldPos = (model * vPos).xyz;
	fWorldCam = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
	fWorldNormal = normalize(modelInvT * vNormal.xyz);	
	fViewPos = (view * model * vPos).xyz;                   
	fModelInvT = modelInvT;
}