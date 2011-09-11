#include "RenderMesh21.hpp"

#include <iostream>

using namespace kocmoc::core::renderer;

using kocmoc::core::scene::Camera;

void RenderMesh21::prepare(void)
{
	;
}

void RenderMesh21::draw(Camera *camera)
{
	std::cout << "drawing with camera: " << camera << std::endl;
}
