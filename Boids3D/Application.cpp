#include "Application.h"


void Application::run(){
	window.init_window();
	init_vulkan();
	main_loop();
	cleanup();
}

void Application::init_vulkan(){
	renderer.set_window_ptr(window.p_window);
	renderer.init_renderer();

}

void Application::main_loop(){
	while (!window.should_close()) {
		window.poll_events();
	}
}

void Application::cleanup(){
	window.cleanup();
}
