#version 330

in vec2 texCoords;                  // Take in our texture coordinate from our vertex shader

// We always define a fragment color that we output.
out vec4 fragColor;

// Maintain our uniforms.
uniform sampler2D tex;              // our primary texture

void main() {
  vec3 texColor = texture(tex, texCoords).rgb;
  fragColor = vec4(texColor, 1.0);
}
