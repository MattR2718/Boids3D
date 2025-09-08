#pragma once

#include "VulkanInclude.h"

#include "Pipeline.h"

struct Material {
    Pipeline* pipeline = nullptr;
	//vk::raii::DescriptorSet descriptor_set;
};