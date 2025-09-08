#pragma once

#include <glm/glm.hpp>
#include "Mesh.h"
#include "Material.h"

struct RenderObject {
	Mesh mesh;
	Material material;
	glm::mat4 transform;
};