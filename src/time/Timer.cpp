#include <kocmoc-core/time/Timer.hpp>
#include <kocmoc-core/math/math.hpp>

#include <iostream>

using namespace kocmoc::core::time;

using kocmoc::core::math::max;

Timer::Timer(GLFWwindow _windowHandle)
	: lastT(glfwGetTime())
	, deltaT(0.0)
	, windowHandle(_windowHandle)
	, counter(0)
{
	tick();
	for (unsigned int i = 0; i < KOCMOC_CORE_TIMER_AVERAGE_LENGTH; i++)
	{
		frameTimes[i] = 0.0f;
	}
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
	float sum = 0.0f;
	float peak = 0.0f;
	for (unsigned int i = 0; i < KOCMOC_CORE_TIMER_AVERAGE_LENGTH; i++)
	{
		sum += frameTimes[i];
		peak = max<float>(peak, frameTimes[i]);
	}
	
	float average = sum / KOCMOC_CORE_TIMER_AVERAGE_LENGTH;
	
	float std = 0.0f;
	for (unsigned int i = 0; i < KOCMOC_CORE_TIMER_AVERAGE_LENGTH; i++)
		std += pow(average - frameTimes[i], 2.0f);
	
	std /= KOCMOC_CORE_TIMER_AVERAGE_LENGTH;
	
	
	unsigned int bSize = 150;
	char* buff = new char[bSize];
	snprintf(buff, bSize, "sputnik | %4.3fms (max: %4.3fms, std: %4.3f) | %4.2ffps",  average * 1000, peak * 1000, sqrt(std) * 1000, 1 / average);
	glfwSetWindowTitle(windowHandle, buff);
	delete [] buff;
}
