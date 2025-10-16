#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

// These 'out' variables MUST match the 'in' variables in the fragment shader
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Pass the texture coordinates through
    TexCoords = aTexCoord;

    // Calculate the world position of the vertex and pass it to the fragment shader
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Calculate the normal vector and pass it
    // This is a common way to transform normals to world space
    Normal = mat3(transpose(inverse(model))) * aPos;

    // Calculate the final screen position of the vertex
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}