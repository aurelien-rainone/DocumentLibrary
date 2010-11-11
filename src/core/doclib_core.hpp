#ifndef DOCLIB_CORE_DOCLIB_CORE_HPP
#define DOCLIB_CORE_DOCLIB_CORE_HPP

#include "core_includes.hpp"
#include "doclib_conf.hpp"

namespace doclib
{

	namespace core
	{

        using namespace std;

		// TODO : put this function in doclib daemon executable and not here
		//bool init_daemon_or_quit();


		class core_services
		{
			public:

				/**	create core_services singleton instance
				  @note
					  (will throw if already exists)
				  */
				static void create();


				/** checks if core_services singleton already exists or not

				*/
				static bool exists();

				/** get core_services singleton instance

				*/
				static core_services& get();

				/** init logging system
				  @note
					  (will throw if instances doesn't exist)
				 */
				static void init_logging(string log_file, bl::level::type log_level);

			private:

				// private constructor
				core_services();
				static core_services * _inst;

		};

	}

}

#endif // !DOCLIB_CORE_DOCLIB_CORE_HPP