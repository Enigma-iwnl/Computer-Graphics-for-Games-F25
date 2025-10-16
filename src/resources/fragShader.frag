#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform int shadingMode;  // 0: Phong, 1: Normal, 2: Depth
uniform bool useTexture;

void main()
{
    // Get the base texture color first
    vec3 texColor = texture(texture1, TexCoords).rgb;

    if (shadingMode == 1) // Normal Shading
    {
        vec3 normalColor = normalize(Normal) * 0.5 + 0.5;
        // If useTexture is checked, multiply the normal color by the texture
        vec3 result = useTexture ? normalColor * texColor : normalColor;
        FragColor = vec4(result, 1.0);
    }
    else if (shadingMode == 2) // Depth Shading
    {
        vec3 depthColor = vec3(gl_FragCoord.z);
        // If useTexture is checked, multiply the depth color by the texture
        vec3 result = useTexture ? depthColor * texColor : depthColor;
        FragColor = vec4(result, 1.0);
    }
    else // Phong Shading (mode 0)
    {
        vec3 objectColor = useTexture ? texColor : vec3(1.0, 0.5, 0.31);

        // Ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        // Diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // Specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;

        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0);
    }
}