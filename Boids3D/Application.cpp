#include "Application.h"


void Application::run(){
	window.init_window();
	init_vulkan();
	main_loop();
	cleanup();
}

void Application::init_vulkan(){
	graphics_device.init_graphics_device(window);
}

void Application::main_loop(){
	while (!window.should_close()) {
		window.poll_events();
	}
}

void Application::cleanup(){
	window.cleanup();
}
