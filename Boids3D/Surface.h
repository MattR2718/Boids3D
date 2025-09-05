#pragma once

#include "Window.h"
#include "VulkanInclude.h"

class Surface {
public:

	vk::raii::SurfaceKHR surface = nullptr;
	GLFWwindow* p_window = nullptr;

	void create_surface(vk::raii::Instance& instance);

private:



};