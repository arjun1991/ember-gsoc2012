//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2010
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.//
//

#ifndef SERVERSETTINGSCREDENTIALS_H_
#define SERVERSETTINGSCREDENTIALS_H_

#include <string>

namespace Eris {
class ServerInfo;
}

namespace Ember {

namespace Services {

/**
 * @brief Server credentials, identifying a server instance.
 *
 * An instance of this class is used to identify a certain server and map this to a section in the server settings configuration.
 *
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 */
class ServerSettingsCredentials
{
public:

	/**
	 * @brief Ctor.
	 *
	 * @param hostName The host name of the server
	 * @param serverName The name of the server instance.
	 */
	ServerSettingsCredentials(const std::string& hostName, const std::string& serverName);

	/**
	 * @brief Ctor.
	 *
	 * @param serverInfo A server info object from Eris from which the needed data will be extracted.
	 */
	ServerSettingsCredentials(const Eris::ServerInfo& serverInfo);

	/**
	 * @brief Gets the host name of the server.
	 *
	 * @returns The host name of the server.
	 */
	const std::string& getHostName() const;

	/**
	 * @brief Gets the name of the server instance.
	 *
	 * @returns The name of the server instance.
	 */
	const std::string& getServerName() const;

private:

	/**
	 * @brief The host name of the server.
	 */
	std::string mHostName;

	/**
	 * @brief The name of the server instance.
	 */
	std::string mServerName;
};

}

}

#endif /* SERVERSETTINGSCREDENTIALS_H_ */
