#version 330

// very simple vertex shader that just transforms an object-space
// position into clip space and passes along a texture coordinate

in vec4 position;
in vec4 normal;
in vec2 uv;

uniform samplerBuffer data_tbo;

uniform mat4 Projection;
uniform mat4 View;

uniform mat4 Model;
uniform vec4 tintColor;
uniform vec4 uvData;
uniform vec2 Scale;
uniform vec2 Offset;


out VERTEX
{
	vec2 UV;
	vec4 Color;
}vertex;

void main()
{
	vertex.UV = uv * uvData.zw + uvData.xy;
	vertex.Color = tintColor;

	vec4 adjustedPos = ((position - vec4(Offset, 0.0, 0.0)) * vec4(Scale, 0.0, 1.0));
	gl_Position = Projection * View * Model * adjustedPos;
}