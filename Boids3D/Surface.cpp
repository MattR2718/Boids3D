#include "Surface.h"


void Surface::create_surface(vk::raii::Instance& instance) {
	VkSurfaceKHR _surface;
	if (glfwCreateWindowSurface(*instance, p_window, nullptr, &_surface) != 0) {
		throw std::runtime_error("ERROR [Surface::create_surface]: Failed to create window surface");
	}
	surface = vk::raii::SurfaceKHR(instance, _surface);
}