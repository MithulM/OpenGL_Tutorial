#version 330 core

out vec4 col;
uniform vec3 res;

void main()
{
	col = vec4(gl_FragCoord.x / res.x, gl_FragCoord.y / res.y, res.z, 1.0);
}
