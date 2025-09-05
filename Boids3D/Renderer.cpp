#include "Renderer.h"


void Renderer::set_window_ptr(GLFWwindow* window){
	surface.p_window = window;
}

void Renderer::init_renderer(){
	graphics_device.init_graphics_device(surface);
	swap_chain.create_swap_chain(graphics_device, surface);
	swap_chain.create_image_views(graphics_device);
}
