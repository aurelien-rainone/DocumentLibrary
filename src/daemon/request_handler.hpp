/* Copyright (C) 
* 2010 - Aurelien Rainone
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
* 
*/

#ifndef DOCLIB_DAEMON_REQUEST_HANDLER_HPP
#define DOCLIB_DAEMON_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace doclib
{

	namespace daemon
	{

		struct reply;
		struct request;

		/**
		* @brief Common handler for all incoming requests.
		*/
		class request_handler
			: private boost::noncopyable
		{
			public:
				/// 
				explicit request_handler();

				/// Handle a request and produce a reply.
				void handle_request(const request& req, reply& rep);

				/// Handle a 'browser folder' request.
				void handle_browse_folder(const request& req, reply& rep);
		};

	}

}

#endif // !DOCLIB_DAEMON_REQUEST_HANDLER_HPP
