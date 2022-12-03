#pragma once

#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h

#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads

#include <SFML/Graphics.hpp>
#include <memory>

class Particles
{
public:
    struct Particle
    {
        sf::Vector2f velocity;
        int lifetime;
    };

    std::shared_ptr<sf::RenderWindow> window;
    std::vector<Particle> m_particles;
    sf::VertexArray vertices;
    sf::Color color;
    float size, x, y;
    std::size_t count;

    void reset_particles();
    void reset_particle(std::size_t, bool);
    void update();

    Particles();
    void run();
};