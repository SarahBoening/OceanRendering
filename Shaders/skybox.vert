#version 420

uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec4 vPos;

out vec4 fTexCoord;
void main()
{
	fTexCoord = vPos;
	gl_Position = (projection * view) * vPos;

}