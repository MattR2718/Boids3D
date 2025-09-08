#include "Application.h"


void Application::run(){
	window.init_window();
	init_vulkan();
	add_test_scene();
	main_loop();
	cleanup();
}

void Application::add_scene(const Scene& scene){
	scenes.push_back(scene);
}

void Application::add_test_scene(){
	Scene scene;

	//Pipeline p;
	p.create_graphics_pipeline(renderer.graphics_device, "shaders/vert.spv", "shaders/frag.spv");

	Material mat;
	mat.pipeline = &p;

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
