#pragma once
#include <SFML/Graphics.hpp>

struct Palette
{
    struct ColorPoint
    {
        float        value;
        sf::Vector3f rgb;
    };

    std::vector<ColorPoint> points;

    void addColorPoint(float value, sf::Color color)
    {
        points.push_back({value, {static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b)}});
    }

    sf::Vector3f getColorVec(float value)
    {
        if (value >= 1.0f) {
            return points.back().rgb;
        } else if (value <= 0.0f) {
            return points.front().rgb;
        }
        uint32_t i{0};
        for (const auto& cp : points) {
            if (cp.value > value) {
                const float range = cp.value - points[i-1].value;
                const float pos   = value - points[i-1].value;
                const float ratio = pos / range;
                return (1.0f - ratio) * points[i-1].rgb + ratio * cp.rgb;
            }
            ++i;
        }
        return {255.0f, 255.0f, 255.0f};
    }

    sf::Color getColor(float value)
    {
        return vec3ToColor(getColorVec(value));
    }

    static sf::Color vec3ToColor(sf::Vector3f v)
    {
        return {
            static_cast<uint8_t>(std::min(std::max(0.0f, v.x), 255.0f)),
            static_cast<uint8_t>(std::min(std::max(0.0f, v.y), 255.0f)),
            static_cast<uint8_t>(std::min(std::max(0.0f, v.z), 255.0f)),
        };
    }
};