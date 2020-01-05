#version 420

in vec4 fTexCoord;

uniform samplerCube skyboxSampler;
uniform vec3 camPos;
uniform float waterHeight;

out vec4 fragmentColor;

float lowerLimit = -15.0f;
float upperLimit = 5.0f;
vec4 fogColor = vec4(0.0f, 0.6f, 1.0f, 1.0f);

void main()
{
	vec4 skyColor = texture(skyboxSampler, vec3(fTexCoord)).rgba;
	float fogFactor = (fTexCoord.y - lowerLimit) / (upperLimit - lowerLimit); 
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	
	vec4 color;
	if (camPos.y < waterHeight){
		color = fogColor;
	} else {
		color = mix(fogColor, skyColor, fogFactor); 
	}

	fragmentColor = color;
}