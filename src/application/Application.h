//
// Created by abdoulayedia on 05.12.2022
//
#pragma once

#include "../window/Window.h"

namespace TreeVisualizer
{
	// Application
	class Application
	{
	public:
		Application();
		~Application();

		Application(const Application &) = delete;
		Application &operator=(const Application &) = delete;
		Application(Application &&) = delete;
		Application &operator=(Application &&) = delete;

		int Play();

		static Application &Get()
		{
			static Application instance;
			return instance;
		}

	private:
		Window _window;
	};
} // TreeVisualizer
