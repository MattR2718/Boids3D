#pragma once

#include "VulkanInclude.h"
#include "Window.h"
#include "GraphicsDevice.h"
#include "Swapchain.h"
#include "Renderer.h"
#include "Scene.h"

#include <print>
#include <chrono>

class Application {
public:

	void run();
	//void add_test_scene();

private:

	Renderer renderer;
	Window window;
	
	std::vector<Scene> scenes;

	Scene s;


	void init_vulkan();
	void init_command_buffer();
	void main_loop();
	void cleanup();
};