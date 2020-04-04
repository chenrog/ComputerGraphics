#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoords;
layout(location = 3) in vec3 tangents;
layout(location = 4) in vec3 bitangents;

// We now have our camera system set up.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// We define a new output vec2 for our texture coorinates.
out vec3 myNormal;
out vec3 fragPos;
out vec2 texCoords;

void main()
{
    // We have our transformed position set properly now
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);

    // Make sure to transform the normal
    vec4 tmpnorm = modelMatrix*vec4(normal, 0.0);
    myNormal = normalize(tmpnorm.xyz);

    // Our fragment pos for lighting.
    fragPos = (modelMatrix*vec4(position, 1.0)).xyz;

    // And we map our texture coordinates as appropriate
    texCoords = textureCoords;
}
