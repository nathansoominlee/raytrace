#include "common/Scene/Lights/Point/PointLight.h"


void PointLight::ComputeSampleRays(std::vector<Ray>& output, glm::vec3 origin, glm::vec3 normal) const
{
    origin += normal * LARGE_EPSILON;
    const glm::vec3 lightPosition = glm::vec3(GetPosition());
    const glm::vec3 rayDirection = glm::normalize(lightPosition - origin);
    const float distanceToOrigin = glm::distance(origin, lightPosition);
    output.emplace_back(origin, rayDirection, distanceToOrigin);
}

float PointLight::ComputeLightAttenuation(glm::vec3 origin) const
{
    
    if (this->isAttenuated)
    {
        // Return a value betwen 0 and 1 for attenuation factor,
        // intensity for a point light falls off as 1 / d ** 2

        const glm::vec3 lightPosition = glm::vec3(GetPosition());
        const float dist = glm::distance(lightPosition, origin);
        const float exponent = 1.1;
        return 1.f / pow(1.f + dist, exponent);
    }
    else
    {
        return 1.f;
    }
}
