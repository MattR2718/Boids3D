#pragma once

/*
	Responsibilities: Manages everything related to presenting images to the screen.

	Owns: vk::raii::SwapchainKHR, std::vector<vk::Image>, std::vector<vk::raii::ImageView>.

	Manages: Swap chain creation, image views, handling "out of date" errors, and recreation when the window is resized.

*/



#define NOMINMAX
#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>

#include "VulkanInclude.h"
#include "Window.h"
#include "PhysicalDevice.h"


class SwapChain {
public:

	vk::raii::SwapchainKHR swap_chain = nullptr;
	std::vector<vk::Image> swap_chain_images;

	void create_swap_chain(vk::raii::PhysicalDevice& physical_device, vk::raii::Device& device, vk::raii::SurfaceKHR& surface, GLFWwindow* window, const std::array<uint32_t, 2>& queue_family_indices);
	void create_image_views(vk::raii::Device& device);

private:

	vk::SurfaceFormatKHR surface_format;
	vk::Extent2D swap_chain_extent;

	std::vector<vk::raii::ImageView> swap_chain_image_views;

	static vk::SurfaceFormatKHR choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>& available_formats);
	vk::PresentModeKHR choose_swap_present_mode(const std::vector<vk::PresentModeKHR>& available_present_modes);
	vk::Extent2D choose_swap_extent(const vk::SurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

};