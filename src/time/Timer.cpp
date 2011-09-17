#include <kocmoc-core/time/Timer.hpp>

#include <GL/glfw3.h>

using namespace kocmoc::core::time;

Timer::Timer(void)
	:lastT(glfwGetTime())
	, deltaT(0.0)
{
	tick();
}

void Timer::tick()
{
	double now = glfwGetTime();
	deltaT = now - lastT;
	lastT = now;
}