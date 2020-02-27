#version 330

in vec2 texCoords; // Take in our texture coordinate from our vertex shader
out vec4 fragColor; // We always define a fragment color that we output.
uniform sampler2D tex; // sampler to retrieve our color data from

void main() {
  // Set our output fragment color to whatever we pull from our input texture
  fragColor = texture(tex, texCoords);
}
