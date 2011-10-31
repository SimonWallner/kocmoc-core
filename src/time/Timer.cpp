#include <kocmoc-core/time/Timer.hpp>

#include <iostream>

using namespace kocmoc::core::time;

Timer::Timer(GLFWwindow _windowHandle)
	: lastT(glfwGetTime())
	, deltaT(0.0)
	, windowHandle(_windowHandle)
	, counter(0)
{
	tick();
}

void Timer::tick()
{
	double now = glfwGetTime();
	deltaT = now - lastT;
	lastT = now;
	
	counter++;
	unsigned int index = counter % KOCMOC_CORE_TIMER_AVERAGE_LENGTH;
	frameTimes[index] = deltaT;
}

void Timer::print()
{
	float sum = 0;
	for (unsigned int i = 0; i < KOCMOC_CORE_TIMER_AVERAGE_LENGTH; i++)
		sum += frameTimes[i];
	
	float average = sum / KOCMOC_CORE_TIMER_AVERAGE_LENGTH;
	
	char buff[50];
	sprintf(buff, "sputnik | %4.3f ms | %4.2f fps",  average * 1000, 1 / average);
	glfwSetWindowTitle(windowHandle, buff);
}