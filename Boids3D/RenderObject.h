#pragma once

#include <glm/glm.hpp>
#include "Mesh.h"
#include "Material.h"

struct RenderObject {
	//std::shared_ptr<Mesh> mesh;
	Material* material;
	glm::mat4 transform;
};