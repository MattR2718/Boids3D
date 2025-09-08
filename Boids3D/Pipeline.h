#pragma once

/*

	Responsibilities: Encapsulates the Vulkan graphics pipeline state.

	Owns: vk::raii::Pipeline, vk::raii::PipelineLayout, vk::raii::DescriptorSetLayout.

	Manages: Loading shaders, defining vertex input, and configuring all pipeline stages (rasterization, color blending, depth testing, etc.). 
			A Pipeline would be configured for a specific type of material or rendering effect.

*/

#include <string>
#include <vector>
#include <print>

#include "VulkanInclude.h"
#include "Shader.h"
#include "GraphicsDevice.h"
#include "SwapChain.h"

class Pipeline {
public:

	//Pipeline() = default;

	vk::raii::PipelineLayout pipeline_layout = nullptr;
	vk::raii::Pipeline graphics_pipeline = nullptr;

	void create_graphics_pipeline(const GraphicsDevice& graphics_device, const SwapChain& swapchain, const std::string& vertex_shader_filename, const std::string& fragment_shader_filename);

private:


};