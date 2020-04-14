#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// output vec2 for our texture coordinates
out vec2 texCoords;

void main()
{
    // We have our transformed position set properly now
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    gl_Position = mvp * vec4(position, 1.0);

    // And we map our texture coordinates as appropriate
    texCoords = textureCoords;
}
