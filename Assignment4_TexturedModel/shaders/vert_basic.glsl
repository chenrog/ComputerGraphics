#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertColor;

void main()
{
  mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
  gl_Position = mvp * vec4(position, 1.0);
  vertColor = vec4(1.0f, 0.4f, 0.4f, 1.0f);
}
