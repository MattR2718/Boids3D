#pragma once

#include "VulkanInclude.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


#include <utility>
#include <span>


class Window {
public:

	vk::raii::SurfaceKHR surface = nullptr;

	void init_window();

	bool should_close();
	void poll_events();

	void create_surface(vk::raii::Instance& instance);

	void cleanup();

	static auto instance_extensions() -> std::span<char const* const> {
		auto count = std::uint32_t{};
		auto const* extensions = glfwGetRequiredInstanceExtensions(&count);
		return { extensions, static_cast<std::size_t>(count) };
	}


private:

	GLFWwindow* p_window;


	// Returns current monitor resolution, 1920 x 1080 default
	static std::pair<int, int> get_resolution() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		return (mode->width > 0 && mode->height > 0) ? std::make_pair(mode->width, mode->height) : std::make_pair(1920, 1080);
	}


};