#version 330 core
out vec4 fragColor;
in vec3 vFragPos;
in vec3 vNormal;
in vec2 texCoords;
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float constant;
    float linear;
    float quadratic;
    float outerCutOff;
};
uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main()
{
    vec3 lightDir = normalize(light.position - vFragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    // diffuse
    vec3 normal = normalize(vNormal);
    float diffuse_factor = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = (diffuse_factor * vec3(texture(material.diffuse, texCoords))) * light.diffuse;
    // specular
    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (specularFactor * vec3(texture(material.specular, texCoords))) * light.specular;

    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float distance = length(light.position - vFragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}