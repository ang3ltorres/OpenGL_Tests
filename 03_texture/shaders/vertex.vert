#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

out VS_OUTPUT {
	vec3 color;
	vec2 texCoord;
} vs_out;

void main()
{
	vs_out.color = vColor;
	vs_out.texCoord = vTexCoord;
	gl_Position = vec4(position, 0.0, 1.0);
}
