#pragma once

#include "VulkanInstance.h"

class GraphicsDevice {
public:
	void init_graphics_device();
private:
	VulkanInstance vulkan_instance;
};