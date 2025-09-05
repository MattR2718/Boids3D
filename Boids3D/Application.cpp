#include "Application.h"


void Application::run(){
	window.init_window();
	init_vulkan();
	main_loop();
	cleanup();
}

void Application::init_vulkan(){
	graphics_device.init_graphics_device(window);
	swapchain.create_swap_chain(graphics_device.physical_device.physical_device, 
								graphics_device.logical_device.device, 
								window.surface, 
								window.p_window, 
								graphics_device.logical_device.queue_family_indices);
}

void Application::main_loop(){
	while (!window.should_close()) {
		window.poll_events();
	}
}

void Application::cleanup(){
	window.cleanup();
}
