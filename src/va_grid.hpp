#pragma once
#include <SFML/Graphics.hpp>

struct VertexArrayGrid
{
    sf::VertexArray va;
    sf::Vector2u    size;

    VertexArrayGrid(uint32_t width, uint32_t height)
        : va{sf::PrimitiveType::Points, width * height}
        , size{width, height}
    {
        uint32_t idx = 0;
        for (uint32_t x{0}; x < width; ++x) {
            for (uint32_t y{0}; y < height; ++y) {
                va[idx++].position = sf::Vector2f{static_cast<float>(x), static_cast<float>(y)};
            }
        }
    }

    void setCellColor(uint32_t x, uint32_t y, sf::Color color)
    {
        const uint32_t idx = x * size.y + y;
        va[idx].color = color;
    }
};