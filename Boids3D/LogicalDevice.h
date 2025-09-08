#pragma once

#include <ranges>
#include <vector>
#include <array>


#include "VulkanInclude.h"
#include "PhysicalDevice.h"

class LogicalDevice {
public:
	std::array<uint32_t, 2> queue_family_indices{ 0 };
	vk::raii::Device device = nullptr;
	vk::raii::Queue graphics_queue = nullptr;

	
	void create_logical_device(PhysicalDevice& physical_device, vk::raii::SurfaceKHR& surface);

private:
	vk::raii::Queue present_queue = nullptr;
};