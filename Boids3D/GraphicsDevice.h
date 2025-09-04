#pragma once

#include "VulkanInstance.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "Window.h"

class GraphicsDevice {
public:
	void init_graphics_device(Window& window);
private:
	VulkanInstance vulkan_instance;
	PhysicalDevice physical_device;
	LogicalDevice logical_device;
};