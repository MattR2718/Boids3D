#include "Application.h"


void Application::run(){
	window.init_window();
	init_vulkan();
	//add_test_scene();
	s.init_scene(renderer);
	init_command_buffer();
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

void Application::init_command_buffer(){
	renderer.command_buffer.create_command_pool(renderer.graphics_device);
	renderer.command_buffer.create_command_buffer(renderer.graphics_device);
	renderer.create_sync_objects(renderer.graphics_device);
}

void Application::main_loop(){
	while (!window.should_close()) {
		window.poll_events();
		renderer.draw_frame(&s);
	}
	renderer.graphics_device.logical_device.device.waitIdle();
}

void Application::cleanup(){
	window.cleanup();
}
