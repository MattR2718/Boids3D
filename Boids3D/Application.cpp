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
	renderer.command_buffer.create_command_buffers(renderer.graphics_device);
	renderer.create_sync_objects(renderer.graphics_device);
}

void Application::main_loop(){
	//auto now = std::chrono::high_resolution_clock::now();
	//int frame_count = 0;
	while (!window.should_close()) {
		window.poll_events();
		renderer.draw_frame(&s);
		//auto n2 = std::chrono::high_resolution_clock::now();
		//if (frame_count++ == 1000) {
		//	frame_count = 0;
		//	auto n2 = std::chrono::high_resolution_clock::now();
		//	uint32_t num_us = std::chrono::duration_cast<std::chrono::microseconds>(n2 - now).count();
		//	std::println("FPS: {}", 1000000.0 / (num_us / 1000.0));
		//	now = n2;
		//}
	}
	renderer.graphics_device.logical_device.device.waitIdle();
}

void Application::cleanup(){
	window.cleanup();
}
