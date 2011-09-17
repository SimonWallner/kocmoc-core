#ifndef KOCMOC_CORE_TIME_TIMER_HPP
#define KOCMOC_CORE_TIME_TIMER_HPP

namespace kocmoc
{
	namespace core
	{
		namespace time
		{
			class Timer
			{
			public:
				/**
				 * Create a new timer and start it instantly.
				 */
				Timer(void);
				
				/**
				 * tick the timer.
				 */
				void tick(void);
				
				/**
				 * Get the elapsed time between the last two ticks.
				 * This value is initialized as 0 and at least two ticks (the 
				 * constructor schould take care of the first) should have happended
				 * in advance.
				 */
				float getDeltaT(void) {return deltaT;}
					
			private:
				double lastT;
				double deltaT;
			};
		}
	}
}

#endif
