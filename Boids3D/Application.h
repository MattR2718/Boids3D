#pragma once

#include "VulkanInclude.h"
#include "Window.h"
#include "GraphicsDevice.h"
#include "Swapchain.h"


#include <print>

class Application {
public:

	void run();

private:

	GraphicsDevice graphics_device;
	Window window;
	SwapChain swapchain;

	void init_vulkan();
	void main_loop();
	void cleanup();
};