#ifndef KOCMOC_CORE_TIME_TIMER_HPP
#define KOCMOC_CORE_TIME_TIMER_HPP

#include <string>

#include <kocmoc-core/gl.h>

#define KOCMOC_CORE_TIMER_AVERAGE_LENGTH 100

namespace kocmoc
{
	namespace core
	{
		namespace time
		{
			/**
			 * Simple timer class. All times are in secods.
			 */
			class Timer
			{
			public:
				/**
				 * Create a new timer and start it instantly.
				 */
				Timer(GLFWwindow windowHandle, std::string name);
				
				/**
				 * tick the timer.
				 */
				void tick();
				
				/**
				 * Get the elapsed time between the last two ticks.
				 * This value is initialized as 0 and at least two ticks (the 
				 * constructor schould take care of the first) should have happended
				 * in advance.
				 */
				float getDeltaT() {return deltaT;}
				
				/**
				 * Get the time at the last tick
				 */
				float getLastT() {return lastT;}
				
				/**
				 * print the timer
				 */
				void print();
					
			private:
				double lastT;
				double deltaT;
				
				GLFWwindow windowHandle;
				
				double frameTimes[KOCMOC_CORE_TIMER_AVERAGE_LENGTH];
				unsigned int counter;
				
				std::string name;
			};
		}
	}
}

#endif
