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

#include "connection.hpp"
#include "../core/core_includes.hpp"
#include <vector>
#include <boost/bind.hpp>
#include "request_handler.hpp"

namespace doclib
{

	namespace daemon
	{

		connection::connection(boost::asio::io_service& io_service, request_handler& handler)
			:	socket_(io_service),
				request_handler_(handler)
		{
		}

		boost::asio::ip::tcp::socket& connection::socket()
		{
			return socket_;
		}

		void connection::start()
		{
			socket_.async_read_some(boost::asio::buffer(buffer_),
					boost::bind(&connection::handle_read, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
		}

		void connection::handle_read(const boost::system::error_code& e,
				std::size_t bytes_transferred)
		{
			if (!e)
			{
				boost::tribool result;
				boost::tie(result, boost::tuples::ignore) = request_parser_.parse(
						request_, buffer_.data(), buffer_.data() + bytes_transferred);

				if (result)
				{
					// request is well formed
					request_handler_.handle_request(request_, reply_);

					// handle it and write reply
					boost::asio::async_write(socket_, reply_.to_buffers(),
							boost::bind(&connection::handle_write, shared_from_this(),
								boost::asio::placeholders::error));
				}
				else if (!result)
				{
					// bad request
					reply_.stock_reply(reply::bad_request);
					LERR_ << "bad request";	

					// write error reply
					boost::asio::async_write(socket_, reply_.to_buffers(),
							boost::bind(&connection::handle_write, shared_from_this(),
								boost::asio::placeholders::error));
				}
				else
				{
					// request parsing should continue
					socket_.async_read_some(boost::asio::buffer(buffer_),
							boost::bind(&connection::handle_read, shared_from_this(),
								boost::asio::placeholders::error,
								boost::asio::placeholders::bytes_transferred));
				}
			}

			// If an error occurs then no new asynchronous operations are started. This
			// means that all shared_ptr references to the connection object will
			// disappear and the object will be destroyed automatically after this
			// handler returns. The connection class's destructor closes the socket.
		}

		void connection::handle_write(const boost::system::error_code& e)
		{
			if (!e)
			{
				// Initiate graceful connection closure.
				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			}

			// No new asynchronous operations are started. This means that all shared_ptr
			// references to the connection object will disappear and the object will be
			// destroyed automatically after this handler returns. The connection class's
			// destructor closes the socket.
		}

	}

}
