//
// Created by abdoulayedia on 05.12.2022
//
#include "Application.h"

namespace TreeVisualizer
{
    Application::Application()
    {
        std::cout << "Application created\n";
    }

    Application::~Application()
    {
        std::cout << "Application destroyed\n";
    }

    int Application::Play()
    {
        _window.Play();
        return 1;
    }
}