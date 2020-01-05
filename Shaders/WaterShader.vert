#version 420

uniform mat4 model;
uniform mat3 modelInvT;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 clipPlane;
uniform vec3 worldSunDirection;

uniform float time;
uniform float amplitude;
uniform float frequency;

layout(location = 0) in vec4 vPos;
layout(location = 2) in vec4 vNormal;
layout(location = 3) in vec4 vTexCoord;

out float movement;
out float movement_2;
out vec3 fWorldPos;
out vec3 fWorldNormal;
out vec3 fWorldCam;
out vec3 fViewPos;
out vec4 clipSpace;
out vec4 fTexCoord;
out mat3 fModelInvT;

float wave_speed = 1.5f;
float wave_speed2 = 0.02f;
float frequency2 = frequency * 2.0f;

// By Morgan McGuire @morgan3d, http://graphicscodex.com, https://www.shadertoy.com/view/4dS3Wd
// Reuse permitted under the BSD license.	
float hash(vec2 p) {
	return fract(1e4 * sin(17.0 * p.x + p.y * 0.1) * (0.1 + abs(sin(p.y * 13.0 + p.x))));
}

float noise(vec2 x) {
    vec2 i = floor(x);
    vec2 f = fract(x);

    // Four corners in 2D of a tile
    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    // Simple 2D lerp using smoothstep envelope between the values.
    // return vec3(mix(mix(a, b, smoothstep(0.0, 1.0, f.x)),
    //          mix(c, d, smoothstep(0.0, 1.0, f.x)),
    //          smoothstep(0.0, 1.0, f.y)));

    // Same code, with the clamps in smoothstep and common subexpressions
    // optimized away.
    vec2 u = f*f*f*(f*(f*6.0 - 15.0) + 10.0);
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

float getNoise(vec2 v)
{
	return (noise(vec2(v.x + time*wave_speed, v.y + time*wave_speed)*frequency) + noise(vec2(v.x+time*wave_speed2,v.y+time*wave_speed2)*frequency2)*0.25f )* amplitude;
}

//------------------------------------------------------------------------------------------------------------------
// MAIN 
//------------------------------------------------------------------------------------------------------------------
void main()
{
	vec4 worldPos = model * vPos;
	gl_ClipDistance[0] = dot(worldPos, clipPlane);
	
	vec4 position = vPos;

	position.y = getNoise(vec2(position.x, position.z));
	//calculate normals
	vec4 normal = vec4(0.0);
	normal.x = getNoise(vec2(position.x-1.0, position.z)) - getNoise(vec2(position.x+1.0, position.z));
	normal.y = 2.0f;
	normal.z = getNoise(vec2(position.x, position.z - 1.0)) - getNoise(vec2(position.x, position.z + 1.0));
	normal = normalize(normal);

	clipSpace = (projection * view * model) * position;
	gl_Position = clipSpace;

	fWorldPos = (model * position).xyz;
	fWorldNormal = normalize(modelInvT * normal.xyz);		
	fWorldCam = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;

	fViewPos = (view * model * position).xyz;

	fTexCoord = vTexCoord;
	fModelInvT = modelInvT;
	movement = time*wave_speed;
	movement_2 = time*wave_speed2;
}