#pragma once

#include <ranges>
#include <vector>

#include "VulkanInclude.h"
#include "PhysicalDevice.h"

class LogicalDevice {
public:
	void create_logical_device(PhysicalDevice& physical_device);

private:
	vk::raii::Device device = nullptr;
	vk::raii::Queue graphics_queue = nullptr;
};