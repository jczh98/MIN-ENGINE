#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 view_pos;

void main()
{
    // ambient
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * lightColor;
    // diffuse
    vec3 normal = normalize(Normal);
    vec3 light_direction = normalize(lightPos - FragPos);
    float diffuse_factor = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = diffuse_factor * lightColor;
    // specular
    float specular_strength = 0.5;
    vec3 view_dirction = normalize(view_pos - FragPos);
    vec3 reflect_dirction = reflect(-light_direction, normal);
    float specular_factor = pow(max(dot(view_dirction, reflect_dirction), 0.0), 32);
    vec3 specular = specular_strength * specular_factor * lightColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}