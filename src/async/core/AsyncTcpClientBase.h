/**
@file	 AsyncTcpClientBase.h
@brief   Contains a base class for creating TCP client connections
@author  Tobias Blomberg
@date	 2003-04-12

This file contains a class that make it easy to create a new TCP connection
to a remote host. See usage instructions in the class definition.

\verbatim
Async - A library for programming event driven applications
Copyright (C) 2003-2017 Tobias Blomberg

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/

#ifndef ASYNC_TCP_CLIENT_BASE_INCLUDED
#define ASYNC_TCP_CLIENT_BASE_INCLUDED


/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <sigc++/sigc++.h>
#include <stdint.h>

#include <string>


/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/

#include <AsyncTcpConnection.h>


/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Forward declarations
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Namespace
 *
 ****************************************************************************/

namespace Async
{

/****************************************************************************
 *
 * Forward declarations of classes inside of the declared namespace
 *
 ****************************************************************************/

class FdWatch;
class DnsLookup;
class IpAddress;


/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Class definitions
 *
 ****************************************************************************/

/**
@brief	A base class for creating a TCP client connection
@author Tobias Blomberg
@date   2003-04-12

This is a base class for creating TCP client connections. It should notmally
not be used direclt but rather the TcpClient class should be used.
*/
class TcpClientBase
{
  public:
    /**
     * @brief   Constructor
     * @param 	con The connection object associated with this client
     *
     * The object will be constructed and variables will be initialized but
     * no connection will be created until the connect function
     * (see @ref TcpClient::connect) is called.
     * When using this variant of the constructor the connect method which
     * take host and port must be used.
     */
    explicit TcpClientBase(TcpConnection *con);

    /**
     * @brief 	Constructor
     * @param 	con           The connection object associated with this client
     * @param 	remote_host   The hostname of the remote host
     * @param 	remote_port   The port on the remote host to connect to
     *
     * The object will be constructed and variables will be initialized but
     * no connection will be created until the connect function
     * (see @ref TcpClient::connect) is called.
     */
    TcpClientBase(TcpConnection *con, const std::string& remote_host,
                  uint16_t remote_port);

    /**
     * @brief 	Constructor
     * @param 	con           The connection object associated with this client
     * @param 	remote_ip     The IP address of the remote host
     * @param 	remote_port   The port on the remote host to connect to
     *
     * The object will be constructed and variables will be initialized but
     * no connection will be created until the connect function
     * (see @ref TcpClient::connect) is called.
     */
    TcpClientBase(TcpConnection *con, const IpAddress& remote_ip,
                  uint16_t remote_port);

    /**
     * @brief 	Destructor
     */
    ~TcpClientBase(void);

    /**
     * @brief   Bind to the interface having the specified IP address
     * @param   bind_ip The IP address of the interface to bind to
     */
    void bind(const IpAddress& bind_ip);

    /**
     * @brief 	Connect to the remote host
     * @param 	remote_host   The hostname of the remote host
     * @param 	remote_port   The port on the remote host to connect to
     *
     * This function will initiate a connection to the remote host. The
     * connection must not be written to before the connected signal
     * (see @ref TcpClient::connected) has been emitted. If the connection is
     * already established or pending, nothing will be done.
     */
    void connect(const std::string &remote_host, uint16_t remote_port);

    /**
     * @brief 	Connect to the remote host
     * @param 	remote_ip     The IP address of the remote host
     * @param 	remote_port   The port on the remote host to connect to
     *
     * This function will initiate a connection to the remote host. The
     * connection must not be written to before the connected signal
     * (see @ref TcpClient::connected) has been emitted. If the connection is
     * already established or pending, nothing will be done.
     */
    void connect(const Async::IpAddress& remote_ip, uint16_t remote_port);

    /**
     * @brief 	Connect to the remote host
     *
     * This function will initiate a connection to the remote host. The
     * connection must not be written to before the connected signal
     * (see @ref TcpClient::connected) has been emitted. If the connection is
     * already established or pending, nothing will be done.
     */
    void connect(void);

    /**
     * @brief 	Disconnect from the remote host
     *
     * Call this function to disconnect from the remote host. If already
     * disconnected, nothing will be done. The disconnected signal is not
     * emitted when this function is called
     */
    void disconnect(void);

    /**
     * @brief   Check if the connection is idle
     * @return  Returns \em true if the connection is idle
     *
     * A connection being idle means that it is not connected nor connecting.
     */
    bool isIdle(void) const { return (sock == -1); }

    /**
     * @brief 	A signal that is emitted when a connection has been established
     */
    sigc::signal<void>       	      	  connected;

  protected:

  private:
    TcpConnection *   con;
    DnsLookup *       dns;
    std::string       remote_host;
    int       	      sock;
    FdWatch *         wr_watch;
    Async::IpAddress  bind_ip;

    void dnsResultsReady(DnsLookup& dns_lookup);
    void connectToRemote(void);
    void connectHandler(FdWatch *watch);

};  /* class TcpClientBase */


} /* namespace */

#endif /* ASYNC_TCP_CLIENT_BASE_INCLUDED */



/*
 * This file has not been truncated
 */

