#pragma once

#include "VulkanInclude.h"

#include "Pipeline.h"

struct Material {
    Pipeline pipeline;
	//vk::raii::DescriptorSet descriptor_set;
};