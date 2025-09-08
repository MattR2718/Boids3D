#pragma once

#include <vector>

#include "Renderer.h"
#include "RenderObject.h"

class Scene {
public:
	std::vector<RenderObject*> render_objects;

	// Camera?

	void init_scene(const Renderer& renderer);

private:

	RenderObject ro;
	Material mat;

};