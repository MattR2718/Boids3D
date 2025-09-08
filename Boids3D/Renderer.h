#pragma once

#include <print>

#include "VulkanInclude.h"
#include "Window.h"
#include "GraphicsDevice.h"
#include "SwapChain.h"
#include "Pipeline.h"
#include "Surface.h"
#include "CommandBuffer.h"

class Scene;

class Renderer {
public:

	GraphicsDevice graphics_device;
	Surface surface;
	SwapChain swap_chain;
	CommandBuffer command_buffer;

	void set_window_ptr(GLFWwindow* window);
	void init_renderer();
	void draw_frame(const Scene* scene);
	void create_sync_objects(const GraphicsDevice& graphics_device);

private:

	vk::raii::Semaphore present_complete_semaphore = nullptr;
	vk::raii::Semaphore render_finished_semaphore = nullptr;
	vk::raii::Fence draw_fence = nullptr;

};