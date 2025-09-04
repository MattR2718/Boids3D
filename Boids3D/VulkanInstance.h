#pragma once

#include <vector>
#include <print>
#include <string>

#include "VulkanInclude.h"
#include "Window.h"

class VulkanInstance {
private:
	vk::raii::Context context;

public:
	vk::raii::Instance instance = nullptr;


	void create_instance();
	void setup_debug_messenger();

private:
	vk::raii::DebugUtilsMessengerEXT debug_messenger = nullptr;

	


	std::vector<const char*> get_required_extensions();
	static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity, vk::DebugUtilsMessageTypeFlagsEXT type, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void*) {
		std::println("Validation layer: type {}, msg: {}", to_string(type), pCallbackData->pMessage);

		return vk::False;
	}
};
