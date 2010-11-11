#ifndef DOCLIB_CORE_DOCLIB_CONF_HPP
#define DOCLIB_CORE_DOCLIB_CONF_HPP

#include "core_includes.hpp"

namespace doclib
{

	namespace core
	{

		using namespace std;


		class doclib_conf
		{
			public:

				/**
				 * create default configuration 
				 */
				doclib_conf();

				/**
				 * load configuration from given filename 
				 */
				bool load(string filename);

				/**
				 * save current configuration to given filename
				 */
				bool save(string filename);

				string	filename;			// configuration filename

				// general values
				string	log_filename;		// log file path
				bl::level::type	log_level;	// logger level

				// databse description file
				string	db_description_file;		// document database descritption file path
		};

	}

}

#endif // !DOCLIB_CORE_DOCLIB_CONF_HPP
