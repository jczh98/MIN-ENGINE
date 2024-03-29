#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 texCoords;
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;
uniform Material material;
uniform vec3 view_pos;

void main()
{
    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    // diffuse
    vec3 normal = normalize(Normal);
    vec3 light_direction = normalize(light.position - FragPos);
    float diffuse_factor = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = (diffuse_factor * vec3(texture(material.diffuse, texCoords))) * light.diffuse;
    // specular
    vec3 view_dirction = normalize(view_pos - FragPos);
    vec3 reflect_dirction = reflect(-light_direction, normal);
    float specular_factor = pow(max(dot(view_dirction, reflect_dirction), 0.0), material.shininess);
    vec3 specular = (specular_factor * vec3(texture(material.specular, texCoords))) * light.specular;

    vec3 result = (ambient + diffuse + specular) * attenuation;
    FragColor = vec4(result, 1.0);
}