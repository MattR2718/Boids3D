#pragma once

/*

	Responsibilities: Handles the low-level Vulkan context.

	Owns: vk::raii::Instance, vk::raii::PhysicalDevice, vk::raii::Device, vk::raii::Queue.

	Manages: Instance creation, physical device selection, logical device creation, and queue retrieval. 
		Acts as a factory for creating other Vulkan resources like buffers and images.

*/



#include "VulkanInstance.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"
#include "Window.h"

class GraphicsDevice {
public:
	VulkanInstance vulkan_instance;
	PhysicalDevice physical_device;
	LogicalDevice logical_device;

	void init_graphics_device(Window& window);
private:
	
};