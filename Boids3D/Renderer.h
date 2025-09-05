#pragma once

#include "VulkanInclude.h"
#include "Window.h"
#include "GraphicsDevice.h"
#include "SwapChain.h"
#include "Pipeline.h"
#include "Surface.h"

class Renderer {
public:

	void set_window_ptr(GLFWwindow* window);
	void init_renderer();

private:

	GraphicsDevice graphics_device;
	Surface surface;
	SwapChain swap_chain;
	Pipeline pipeline;


};