#pragma once

#include "VulkanInstance.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"

class GraphicsDevice {
public:
	void init_graphics_device();
private:
	VulkanInstance vulkan_instance;
	PhysicalDevice physical_device;
	LogicalDevice logical_device;
};