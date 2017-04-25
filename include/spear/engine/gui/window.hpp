#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <vector>

#include <spear/engine/vulkan.hpp>

struct SDL_Window;

namespace spear {
namespace engine {
namespace gui {

class Window;

typedef std::function<void(const Window*)> WindowEventFunction;
typedef std::vector<WindowEventFunction> WindowEventFunctions;

struct WindowParameters {
	std::string name;
	uint32_t w, h, x, y;
};

class Window {
 public:
	Window(const WindowParameters& parameters);
	~Window();

	bool setup(const WindowParameters& parameters);
	bool run_frame();
	void run_forever();
	void add_event_loop(WindowEventFunction event_function);

 public:
    bool good;
	uint64_t frame_number;
	SDL_Window* sdl_window;
	WindowEventFunctions event_functions;
	VDeleter<VkInstance> instance{vkDestroyInstance};

 private:
	bool _setup_sdl(const WindowParameters&);
	bool _setup_vulkan();

};


} // gui
} // engine
} // spear