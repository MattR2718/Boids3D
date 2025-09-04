#pragma once

#include "VulkanInclude.h"
#include "Window.h"
#include "GraphicsDevice.h"

#include <print>

class Application {
public:
	void run();

private:

	Window window;
	GraphicsDevice graphics_device;

	void init_vulkan();
	void main_loop();
	void cleanup();
};