#include <thread>
#include <chrono>
#include <iostream>
#include <spear/engine/gui.hpp>
#include <spdlog/spdlog.h>

namespace {
auto logger = spdlog::stdout_color_mt("main.cc");
}

int main(int argc, char** argv)
{
	namespace gui = spear::engine::gui;

	gui::WindowParameters wp;
	{
		wp.name = "spear";
		wp.x = 0;
		wp.y = 0;
		wp.w = 640;
		wp.h = 480;
	}

	gui::Window window(wp);

	if (!window.good) {
		logger->error("Faileld to initialize basic window");
		return 2;
	}

	// Basic application
	window.run_forever();

    return 0;
}