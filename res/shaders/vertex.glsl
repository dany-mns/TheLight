#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;


out vec3 vsPosition;
out vec3 vsColor;
out vec2 vsTexcoord;
out vec3 vsNormal;

uniform mat4 MVP;
uniform mat4 modelMatrix, viewMatrix, projectionMatrix;

out mat4 vsModelMatrix;

void main() {

	vsPosition = vec4(modelMatrix * vec4(position, 1.0f)).xyz;
	vsColor = color;
	vsTexcoord = vec2(texcoord.x, texcoord.y);

	// De ce transpuse and inverse?
	vsNormal = mat3(transpose(inverse(modelMatrix))) * normal;
	
	vsModelMatrix = modelMatrix;
	
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(position, 1.0f);
}