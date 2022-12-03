//
// Created by abdoulayedia on 03.12.2022
//
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace TreeVisualizer
{
	// Window
	class Window
	{
	public:
		Window();
		~Window();

		void Play();

	private:
		sf::RenderWindow *_window = nullptr;
		sf::Clock _clock;
		sf::Font _font;
		ImFont *_imguiFont = nullptr;
		sf::CircleShape _shape;

		// ImGui Window init
		void setFancyImguiStyle();

		// Main loop
		void HandleEvents();
		// void HandleInputs();
		void Update();
		void Render();

		// TEMP utils, this will be moved later on a different file/class probably
		sf::Color ImVec4toSFColor(ImVec4 color)
		{
			return sf::Color(color.x * 255, color.y * 255, color.z * 255, color.w * 255);
		}

		static void ShowExampleAppMainMenuBar()
		{
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Undo", "CTRL+Z"))
					{
					}
					if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
					{
					} // Disabled item
					ImGui::Separator();
					if (ImGui::MenuItem("Cut", "CTRL+X"))
					{
					}
					if (ImGui::MenuItem("Copy", "CTRL+C"))
					{
					}
					if (ImGui::MenuItem("Paste", "CTRL+V"))
					{
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Edit"))
				{
					if (ImGui::MenuItem("Undo", "CTRL+Z"))
					{
					}
					if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
					{
					} // Disabled item
					ImGui::Separator();
					if (ImGui::MenuItem("Cut", "CTRL+X"))
					{
					}
					if (ImGui::MenuItem("Copy", "CTRL+C"))
					{
					}
					if (ImGui::MenuItem("Paste", "CTRL+V"))
					{
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Options"))
				{
					if (ImGui::MenuItem("Dark Mode"))
					{
					}
					ImGui::EndMenu();
				}

				HelpMarker(
					"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!"
					"\n"
					"- Drag from window title bar or their tab to dock/undock."
					"\n"
					"- Drag from window menu button (upper-left button) to undock an entire node (all windows)."
					"\n"
					"- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)"
					"\n"
					"- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)"
					"\n"
					"This demo app has nothing to do with enabling docking!"
					"\n\n"
					"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window."
					"\n\n"
					"Read comments in ShowExampleAppDockSpace() for more details.");
				ImGui::EndMainMenuBar();
			}
		}

		static void HelpMarker(const char *desc)
		{
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(desc);
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
	};
} // TreeVisualizer
