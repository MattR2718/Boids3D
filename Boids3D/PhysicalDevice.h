#pragma once

#include <map>
#include <cstdint>
#include <print>
#include <vector>
#include <algorithm>

#include "VulkanInclude.h"


class PhysicalDevice {
public:

	std::vector<const char*> deviceExtensions = {
		vk::KHRSwapchainExtensionName,
		vk::KHRSpirv14ExtensionName,
		vk::KHRSynchronization2ExtensionName,
		vk::KHRCreateRenderpass2ExtensionName
	};

	vk::raii::PhysicalDevice physical_device = nullptr;


	void pick_physical_device(vk::raii::Instance& instance);

private:


	uint32_t find_queue_families(VkPhysicalDevice device);
};