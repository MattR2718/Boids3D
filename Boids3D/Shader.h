#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "VulkanInclude.h"
#include "GraphicsDevice.h"

class Shader {
public:

	static std::vector<char> read_shader_file(const std::string& filename);

	static vk::raii::ShaderModule create_shader_module(const GraphicsDevice& graphics_device, const std::vector<char>& code);
	static vk::raii::ShaderModule create_shader_module(const GraphicsDevice& graphics_device, const std::string& filename);

private:


};