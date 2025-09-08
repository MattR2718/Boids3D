#include "Scene.h"

void Scene::init_scene(const Renderer& renderer){
	mat.pipeline.create_graphics_pipeline(renderer.graphics_device, renderer.swap_chain, "shaders/vert.spv", "shaders/frag.spv");
	ro.material = &mat;

	render_objects.emplace_back(&ro);
}
