#version 330 core

layout(location = 0) in vec3 position;

out vec4 vertexColor;
uniform mat4 PVM;

void main()
{
	gl_Position = PVM * vec4(position, 1.0);
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}
