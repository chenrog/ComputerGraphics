#version 330

in vec3 myNormal;                   // And our fragment normal
in vec3 fragPos;                    // And our fragment position for lighting
in vec2 texCoords;                  // Take in our texture coordinate from our vertex shader

// We always define a fragment color that we output.
out vec4 fragColor;

// Define our light(s)
struct PointLight {
    vec3 color;
    vec3 position;
    float ambientIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Maintain our uniforms.
uniform sampler2D tex;              // our primary texture
uniform mat4 view;                  // we need the view matrix for highlights
const int pointLightCount = 2;
uniform PointLight pointLights[pointLightCount];  // Our lights

void main() {
  // TODO:  Implement some form of lighting.
  fragColor = vec4(0.0, 0.0, 0.0, 1.0);

  vec3 texColor;
  texColor = texture(tex, texCoords).rgb;

  for (int i = 0; i < pointLightCount; i++) {
    PointLight light = pointLights[i];

    vec3 norm = normalize(myNormal);

    // Diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diffImpact = max(dot(norm, lightDir), 0.0);

    // Specular
    vec3 viewPos = vec3(0.0, 0.0, 0.0);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    // combine results
    vec3 ambient = texColor * light.ambientIntensity * light.color;
    vec3 diffuse = texColor * diffImpact * light.color;
    vec3 specular = texColor * light.specularIntensity * spec * light.color;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 lighting = diffuse + ambient + specular;
    fragColor += vec4(lighting, 1.0);
  }
}
