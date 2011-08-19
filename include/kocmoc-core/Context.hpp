#ifndef KOCMOC_CORE_CONTEXT_HPP
#define KOCMOC_CORE_CONTEXT_HPP

namespace kocmoc {
	namespace core {
		
		/**
		 * main GL context
		 */
		class Context
		{
		public:
			/**
			 * Create a new context
			 */
			Context(void);

			/**
			 * initialize, i.e. construct the context
			 */
			void init(void);

			~Context(void);
			
			/**
			 * Print a bunch of usefull informations
			 */
			void getInfo(void);

		};
	}
}


#endif