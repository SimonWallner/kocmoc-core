#include <kocmoc-core/time/Timer.hpp>

#include <iostream>

#include <kocmoc-core/math/math.hpp>
#include <objectif-lune/Singleton.hpp>

using namespace kocmoc::core::time;

using kocmoc::core::math::max;

Timer::Timer(GLFWwindow _windowHandle, std::string _name)
	: lastT(glfwGetTime())
	, deltaT(0.0)
	, windowHandle(_windowHandle)
	, counter(0)
	, name(_name)
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
	
	
//	unsigned int bSize = 150;
//	char* buff = new char[bSize];
//	snprintf(buff, bSize, "sputnik | %4.3fms (max: %4.3fms, std: %4.3f) | %4.2ffps",
//			 average * 1000, peak * 1000, sqrt(std) * 1000, 1 / average);
//	glfwSetWindowTitle(windowHandle, buff);
//	delete [] buff;
	
	objectifLune::Singleton::Get()->scalar(name + " average", average * 1000);
	objectifLune::Singleton::Get()->scalar(name + " peak", peak * 1000);
	objectifLune::Singleton::Get()->scalar(name + " fps", 1 / average);

	// adding +0 so that xcode does not crash...???
	objectifLune::Singleton::Get()->data(lastT + 0, name, deltaT * 1000);
	
}
