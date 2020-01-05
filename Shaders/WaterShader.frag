#version 420

in float movement;
in float movement_2;
in vec3 fWorldPos;
in vec3 fWorldNormal;
in vec3 fWorldCam;

in vec3 fViewPos;
in mat3 fModelInvT;

in vec4 clipSpace;
in vec4 fTexCoord;

uniform sampler2D waterNormal1;
uniform sampler2D waterNormal2;
uniform sampler2D waterDudv1;
uniform sampler2D waterDudv2;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform vec3 worldSunDirection;
uniform float time;
uniform int terrainResolution;
uniform int tileFactor;

out vec4 fragmentColor;

float wave_strength = 0.1f;

vec4 water = vec4(0.1f, 1.0f, 0.9f, 1.0f);

float Strength_Sun = 1.0f;
float shiny = 120.0f;
vec4 specularColor = vec4(0.75f, 0.75f, 0.75f, 1.0f);
	
void main()
{

	vec3 V = normalize(fWorldCam - fWorldPos);
	vec3 L_Sun = normalize(worldSunDirection);

	vec2 timeCoords1 = fTexCoord.st + vec2((movement*0.1) / float(terrainResolution - 1) * tileFactor, (movement*0.1) / float(terrainResolution - 1) * tileFactor);
	vec2 timeCoords2 = fTexCoord.st - vec2(movement_2 / float(terrainResolution - 1) * tileFactor, movement_2 /float (terrainResolution - 1) * tileFactor);
	
	vec2 ndc = (clipSpace.xy / clipSpace.w) *0.5f + 0.5f;
	vec2 reflectionCoord = vec2(ndc.x, -ndc.y);
	vec2 refractionCoord = ndc;

	vec2 totalDistortion = (texture(waterDudv1, timeCoords1).rg + texture(waterDudv2, timeCoords2).rg *2.0 - 1.0 ) * wave_strength;
	
	reflectionCoord	+= totalDistortion;
	refractionCoord	+= totalDistortion;
	
	reflectionCoord.x = clamp(reflectionCoord.x, 0.001, 0.999);
	reflectionCoord.y = clamp(reflectionCoord.y, -0.999, -0.001);
	refractionCoord = clamp(refractionCoord, 0.001, 0.999);
	
	vec4 reflection = texture(reflectionTexture, reflectionCoord);
	vec4 refraction = texture(refractionTexture, refractionCoord);
	
	vec4 normalColors = texture(waterNormal1, timeCoords1).rgba + texture(waterNormal2, timeCoords2).rgba; 
	vec3 normalFromTexture = vec3(normalColors.r * 2.0f - 1.0f, normalColors.b, normalColors.g * 2.0f - 1.0f);
	vec3 normal = fWorldNormal + fModelInvT*normalFromTexture;
	normal = normalize(normal);

	vec3 viewVector = normalize(vec3(0.0f) - fViewPos);
	float refractiveFactor = dot(viewVector, normal);
//	refractiveFactor = pow(refractiveFactor, 1.0);
	refractiveFactor = clamp(refractiveFactor, 0.0f, 1.0f);
	
	// sun light
	vec3 H_Sun = normalize(V + L_Sun);
	
	vec4 waterMix = mix(reflection, refraction, refractiveFactor);
	waterMix = mix(waterMix, water, 0.3);
	
	fragmentColor = vec4(0.0);
	fragmentColor = waterMix * Strength_Sun * max(0.0, dot(normal, L_Sun));					// diffuse
	fragmentColor += specularColor * Strength_Sun * pow(max(0.0, dot(normal, H_Sun)), shiny);	// specular

}