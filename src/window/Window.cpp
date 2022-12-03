//
// Created by abdoulayedia on 03.12.2022
//
#include "Window.h"

namespace TreeVisualizer
{
    Window::Window()
    {
        constexpr unsigned int width = 2560;
        constexpr unsigned int height = 1600;

        _window = new sf::RenderWindow(sf::VideoMode(width, height), "Tree Visualizer", sf::Style::Default);
        _window->setFramerateLimit(60);

        ImGui::SFML::Init(*_window);

        auto &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.IniFilename = "/Users/abdoulayedia/Projects/Dev/C++/tree_visualizer/src/config/imgui.ini";

        _imguiFont = io.Fonts->AddFontFromFileTTF(
            "/Users/abdoulayedia/Projects/Dev/C++/sfml_imgui/src/assets/fonts/Poppins/Poppins-Regular.ttf", 20);

        if (!ImGui::SFML::UpdateFontTexture())
        {
            std::cerr << "No luck\n";
        }

        // increase the font size
        io.FontGlobalScale = 1.5f;

        _shape.setRadius(10.f);
        _shape.setPointCount(50);

        setFancyImguiStyle();
    }

    Window::~Window()
    {
        ImGui::SFML::Shutdown();
    }

    void Window::Play()
    {
        if (_window == nullptr)
            return;

        while (_window->isOpen())
        {
            HandleEvents();
            Update();
            Render();
        }
    }

    void Window::setFancyImguiStyle()
    {

        ImGui::GetStyle().FrameRounding = 4.0f;
        ImGui::GetStyle().GrabRounding = 4.0f;

        ImGui::GetStyle().FramePadding = ImVec2(6, 4);
        ImGui::GetStyle().ItemSpacing = ImVec2(6, 2);
        ImGui::GetStyle().ItemInnerSpacing = ImVec2(6, 4);
        ImGui::GetStyle().IndentSpacing = 6.0f;

        ImVec4 *colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

    void Window::HandleEvents()
    {
        if (_window == nullptr)
            return;

        sf::Event event{};
        while (_window->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(*_window, event);

            switch (event.type)
            {
            case sf::Event::Closed:
                _window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    _window->close();
                }
                break;
            default:
                break;
            }
        }
    }

    void Window::Update()
    {
    }

    void Window::Render()
    {
        ImGui::SFML::Update(*_window, _clock.restart());

        static ImVec4 circleColor{1.0f, 0.0f, 1.0f, 0.5f};
        static float circleRadius = 100.f;
        static std::size_t circlePoints = 30;

        _shape.setFillColor(ImVec4toSFColor(circleColor));

        static ImVec2 viewportSize{500, 500};
        sf::RenderTexture rt{};
        rt.create(viewportSize.x, viewportSize.y);

        rt.clear(sf::Color::Black);
        rt.draw(_shape);

        ImGui::PushFont(_imguiFont);
        ImGui::DockSpaceOverViewport();

        ImGui::ShowDemoWindow();
        ShowExampleAppMainMenuBar();

        if (ImGui::Begin("Circle manipulator"))
        {
            ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaBar;
            ImGui::ColorPicker4("Circle Color", (float *)&circleColor, flags, nullptr);

            if (ImGui::DragFloat("Circle Radius", &circleRadius))
            {
                _shape.setRadius(circleRadius);
            }
            if (ImGui::DragInt("Circle Points", (int *)&circlePoints, 1.0f, 3, 500))
            {
                _shape.setPointCount(circlePoints);
            }
        }
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        if (ImGui::Begin("Viewport"))
        {
            viewportSize = ImGui::GetWindowSize();
            ImGui::Image(rt);
        }
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopFont();

        _window->clear();
        _window->draw(_shape);

        ImGui::SFML::Render(*_window);
        _window->display();
    }

} // TreeVisualizer
