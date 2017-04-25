#include <SDL.h>
#include <spear/engine/gui/window.hpp>
#include <spdlog/spdlog.h>

namespace {
auto logger = spdlog::stdout_color_mt("gui.cc");
}

namespace spear {
namespace engine {
namespace gui {

Window::Window(const WindowParameters& parameters)
{
	logger->info("Constructing new Window()");
	this->setup(parameters);
}

Window::~Window()
{
	if (sdl_window) {
		SDL_DestroyWindow(sdl_window);
	}
}

bool Window::setup(const WindowParameters& wp)
{
	good = false;

	if (!this->_setup_sdl(wp)) {
		return false;
	}

	if (!this->_setup_vulkan()) {
		return false;
	}

	good = true;
	return true;
}

bool Window::_setup_sdl(const WindowParameters& wp)
{
	logger->info("Initializing Video");
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return false;
	}

	sdl_window = SDL_CreateWindow(
		wp.name.c_str(),
		wp.x,
		wp.y,
		wp.w,
		wp.h,
		SDL_WINDOW_SHOWN
	);

	if (!sdl_window) {
		return false;
	}

	return true;
}

bool Window::_setup_vulkan()
{
	logger->info("Initializing Vulkan");
	uint32_t extension_count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
	logger->info("{} extensions supported", extension_count);

	const char* extension_names[] = {
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
	};

	VkApplicationInfo app_info = {};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "spear-launcher";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "spear";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;
	create_info.enabledExtensionCount = extension_count;
	create_info.ppEnabledExtensionNames = extension_names;
	create_info.enabledLayerCount = 0;

	return true;
}

bool Window::run_frame()
{
	SDL_Delay(1000);
	return true;
}

void Window::run_forever()
{
	while (good) {
		this->run_frame();
	}
}

void Window::add_event_loop(WindowEventFunction event_function)
{
	event_functions.push_back(event_function);
}

} // gui
} // engine
} // spear