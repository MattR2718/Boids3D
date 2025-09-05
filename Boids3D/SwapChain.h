#pragma once
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


private:

	vk::SurfaceFormatKHR surface_format;
	vk::Extent2D swap_chain_extent;

	static vk::SurfaceFormatKHR choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>& available_formats);
	vk::PresentModeKHR choose_swap_present_mode(const std::vector<vk::PresentModeKHR>& available_present_modes);
	vk::Extent2D choose_swap_extent(const vk::SurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

};