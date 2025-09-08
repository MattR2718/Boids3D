#include "Application.h"


void Application::run(){
	window.init_window();
	init_vulkan();
	//add_test_scene();
	s.init_scene(renderer);
	main_loop();
	cleanup();
}

//void Application::add_test_scene(){
//	Scene scene;
//
//	Material mat;
//	mat.pipeline.create_graphics_pipeline(renderer.graphics_device, renderer.swap_chain, "shaders/vert.spv", "shaders/frag.spv");
//
//	RenderObject ro;
//	ro.material = mat;
//
//
//}

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
