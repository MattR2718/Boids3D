#pragma once

#include "VulkanInclude.h"
#include "Window.h"
#include "GraphicsDevice.h"
#include "Swapchain.h"
#include "Renderer.h"


#include <print>

class Application {
public:

	void run();

private:

	Renderer renderer;
	Window window;
	

	void init_vulkan();
	void main_loop();
	void cleanup();
};