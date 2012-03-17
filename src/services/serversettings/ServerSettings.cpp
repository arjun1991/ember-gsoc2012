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

#include "ServerSettings.h"
#include "ServerSettingsCredentials.h"
#include "framework/LoggingInstance.h"
#include "services/config/ConfigService.h"
#include <varconf/varconf.h>
#include <fstream>
#include <sstream>

namespace Ember
{

namespace Services
{

ServerSettings::ServerSettings() :
    mConfig(new varconf::Config())
{
  setName("Server settings Service");
}

ServerSettings::~ServerSettings()
{
}

Service::Status ServerSettings::start()
{
  readFromDisk();
  setRunning(true);
  return Service::OK;
}

void ServerSettings::stop(int code)
{
  Service::stop(code);
  writeToDisk();
}

std::string ServerSettings::getSectionForServerCredentials(const ServerSettingsCredentials & credentials) const
{
  //This should be expanded to a more complex way of assuring that the section returned is correct for the server credentials.
  std::stringstream ss;
  ss << "hostname_" << credentials.getHostName() << "_servername_" << credentials.getServerName();
  std::string sectionName(ss.str());
  mConfig->clean(sectionName);
  return sectionName;
}

void ServerSettings::writeToDisk()
{
  std::string filePath = getFullConfigFilePath();

  mConfig->writeToFile(filePath); //calling this without any scope arguments makes it write all settings in all scopes
}

void ServerSettings::readFromDisk()
{
  std::string filePath = getFullConfigFilePath();

  std::ifstream file(filePath.c_str());

  // If an existing server settings is present, then read it in.
  if (!file.fail()) {
    // read in file
    // 		serverCache.readFromFile(cacheFile.c_str(),varconf::GLOBAL);
    S_LOG_VERBOSE("Loading existing server settings [ " << filePath << " ]");
    try {
      // make sure it is well formed
      mConfig->parseStream(file, varconf::GLOBAL);
    } catch (varconf::ParseError& ex) {
      S_LOG_FAILURE("Error loading server settings file: " << ex);
      return;
    }
    file.close();
  }
}

void ServerSettings::setItem(const ServerSettingsCredentials & credentials, const std::string & key, const varconf::Variable& item)
{
  mConfig->setItem(getSectionForServerCredentials(credentials), key, item);
}

bool ServerSettings::findItem(const ServerSettingsCredentials & credentials, const std::string & key) const
{
  std::string cleanKey(key);
  mConfig->clean(cleanKey);
  return mConfig->findItem(getSectionForServerCredentials(credentials), cleanKey);
}

varconf::Variable ServerSettings::getItem(const ServerSettingsCredentials & credentials, const std::string & key) const
{
  std::string cleanKey(key);
  mConfig->clean(cleanKey);
  return mConfig->getItem(getSectionForServerCredentials(credentials), cleanKey);
}

bool ServerSettings::eraseItem(const ServerSettingsCredentials & credentials, const std::string & key)
{
  std::string cleanKey(key);
  mConfig->clean(cleanKey);
  return mConfig->erase(getSectionForServerCredentials(credentials), cleanKey);
}

const varconf::sec_map & ServerSettings::getServerSettings(const ServerSettingsCredentials & credentials)
{
  return mConfig->getSection(getSectionForServerCredentials(credentials));
}

std::string ServerSettings::getFullConfigFilePath() const
{
  ConfigService& cfgService = EmberServices::getSingleton().getConfigService();
  // fetch the configuration file
  if (cfgService.hasItem("general", "serversettings")) {
    return cfgService.getHomeDirectory() + "/" + static_cast<std::string>(cfgService.getValue("general", "serversettings"));
  } else {
    // default fallback value
    return cfgService.getHomeDirectory() + "/serversettings.conf";
  }
}
}
}
