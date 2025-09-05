#include "Window.h"

void Window::init_window(){
	glfwInit();

	// Create no OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// Prevent resizing
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	auto [w, h] = Window::get_resolution();
	constexpr float WINDOW_RES_SCALE = 0.5; // Don't open at full size
	p_window = glfwCreateWindow(w * WINDOW_RES_SCALE, h * WINDOW_RES_SCALE, "Boids3D", nullptr, nullptr);

}

bool Window::should_close(){
	return glfwWindowShouldClose(p_window);
}

void Window::poll_events(){
	glfwPollEvents();
}




void Window::cleanup() {
	glfwDestroyWindow(p_window);
	glfwTerminate();
}
