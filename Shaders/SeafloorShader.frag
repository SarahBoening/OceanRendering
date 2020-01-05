#version 420

in vec4 fTexCoord;
in vec3 fViewPos;
in vec3 fWorldCam;
in vec3 fWorldPos;
in mat3 fModelInvT;
in vec3 fWorldNormal;

uniform sampler2D seafloorTexture;
uniform sampler2D seafloorNormalTexture;
uniform sampler2D causticTexture1;
uniform sampler2D causticTexture2;
uniform sampler2D causticTexture3;
uniform sampler2D causticTexture4;
uniform sampler2D causticTexture5;
uniform sampler2D causticTexture6;
uniform sampler2D causticTexture7;
uniform sampler2D causticTexture8;
uniform sampler2D causticTexture9;
uniform sampler2D causticTexture10;
uniform sampler2D causticTexture11;
uniform sampler2D causticTexture12;
uniform sampler2D causticTexture13;
uniform sampler2D causticTexture14;
uniform sampler2D causticTexture15;
uniform sampler2D causticTexture16;

uniform vec3 camPos;
uniform vec3 worldSunDirection;
uniform float waterHeight;
uniform int timeModulo;

out vec4 fragmentColor;

vec4 fogColor = vec4(0.0f, 0.6f, 1.0f, 1.0f);
float Strength_Sun = 1.0f;
float wave_speed1 = 0.1f;
float wave_speed2 = 0.2f;
float wave_strength = 0.1f;
vec4 water = vec4(0.1f, 1.0f, 0.9f, 1.0f);

void main()
{

	vec4 caustic1 = texture(causticTexture1, fTexCoord.st).rgba;
	vec4 caustic2 = texture(causticTexture2, fTexCoord.st).rgba;
	vec4 caustic3 = texture(causticTexture3, fTexCoord.st).rgba;
	vec4 caustic4 = texture(causticTexture4, fTexCoord.st).rgba;
	vec4 caustic5 = texture(causticTexture5, fTexCoord.st).rgba;
	vec4 caustic6 = texture(causticTexture6, fTexCoord.st).rgba;
	vec4 caustic7 = texture(causticTexture7, fTexCoord.st).rgba;
	vec4 caustic8 = texture(causticTexture8, fTexCoord.st).rgba;
	vec4 caustic9 = texture(causticTexture9, fTexCoord.st).rgba;
	vec4 caustic10 = texture(causticTexture10, fTexCoord.st).rgba;
	vec4 caustic11 = texture(causticTexture11, fTexCoord.st).rgba;
	vec4 caustic12 = texture(causticTexture12, fTexCoord.st).rgba;
	vec4 caustic13 = texture(causticTexture13, fTexCoord.st).rgba;
	vec4 caustic14 = texture(causticTexture14, fTexCoord.st).rgba;
	vec4 caustic15 = texture(causticTexture15, fTexCoord.st).rgba;
	vec4 caustic16 = texture(causticTexture16, fTexCoord.st).rgba;
	vec4 causticColor = vec4(0.0f);
	
	if(timeModulo == 0){
		causticColor = caustic1;
	}
	else if (timeModulo == 1){
		causticColor = caustic2;
	}
	else if (timeModulo == 2){
		causticColor = caustic3;
	}
	else if (timeModulo == 3){
		causticColor = caustic4;
	}
	else if (timeModulo == 4){
		causticColor = caustic5;
	}
	else if (timeModulo == 5){
		causticColor = caustic6;
	}
	else if (timeModulo == 6){
		causticColor = caustic7;
	}
	else if (timeModulo == 7){
		causticColor = caustic8;
	}
	else if (timeModulo == 8){
		causticColor = caustic9;
	}
	else if (timeModulo == 9){
		causticColor = caustic10;
	}	
	else if (timeModulo == 10){
		causticColor = caustic11;
	}
	else if (timeModulo == 11){
		causticColor = caustic12;
	}
	else if (timeModulo == 12){
		causticColor = caustic13;
	}
	else if (timeModulo == 13){
		causticColor = caustic14;
	}
	else if (timeModulo == 14){
		causticColor = caustic15;
	}
	else if (timeModulo == 15){
		causticColor = caustic16;
	}
	
	//texture
	vec4 seafloor = texture(seafloorTexture, fTexCoord.st).rgba;
	vec4 color = seafloor + causticColor;
	color = clamp(color, 0.0f, 1.0f);
	
	// normals
	vec3 normalColors = texture(seafloorNormalTexture, fTexCoord.st).rgb;
	vec3 normalFromTexture = vec3(normalColors.r * 2.0f - 1.0f, normalColors.b, normalColors.g * 2.0f - 1.0f);
	vec3 normal = fWorldNormal + fModelInvT*normalFromTexture;
	normal = normalize(normal);
	
	// sun light
	vec3 V = normalize(fWorldCam - fWorldPos);
	vec3 L_Sun = normalize(worldSunDirection);
	
	// Fog
	if(camPos.y < waterHeight){
		float dist = length(fViewPos);
		float fogFactor = exp(-pow(dist*0.01, 2.0));
		fogFactor = clamp(fogFactor, 0.0, 1.0);
		color = mix(fogColor, color, fogFactor);
	}

	fragmentColor = color * Strength_Sun * max(0.0, dot(normal, L_Sun));
}