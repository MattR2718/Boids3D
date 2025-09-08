#pragma once

#include <vector>

#include "RenderObject.h"

class Renderer;

class Scene {
public:
	std::vector<RenderObject*> render_objects;

	// Camera?

	void init_scene(const Renderer& renderer);

private:

	RenderObject ro;
	Material mat;

};