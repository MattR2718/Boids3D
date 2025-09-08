#include "Shader.h"

std::vector<char> Shader::read_shader_file(const std::string& filename){
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		throw std::runtime_error("ERROR [Shader::read_shader_file]: Failed to open file: " + filename);
	}

	std::vector<char> buffer(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));

	return buffer;
}

vk::raii::ShaderModule Shader::create_shader_module(const GraphicsDevice& graphics_device, const std::vector<char>& code){
	vk::ShaderModuleCreateInfo create_info{
			.codeSize = code.size() * sizeof(char),
			.pCode = reinterpret_cast<const uint32_t*>(code.data())
		};

	return vk::raii::ShaderModule(graphics_device.logical_device.device, create_info);
}

vk::raii::ShaderModule Shader::create_shader_module(const GraphicsDevice& graphics_device, const std::string& filename){
	return create_shader_module(graphics_device, read_shader_file(filename));
}
