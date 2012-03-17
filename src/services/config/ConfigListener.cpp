//
// C++ Implementation: ConfigListener
//
// Description:
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2008
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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ConfigListener.h"
#include "../EmberServices.h"
#include "ConfigService.h"

namespace Ember
{

ConfigListener::ConfigListener(const std::string& section, const std::string& key, ConfigListenerContainer::SettingChangedSlot slot) :
    mSection(section), mKey(key), mSlot(slot), mInternalSlot(sigc::mem_fun(*this, &ConfigListener::ConfigService_EventChangedConfigItem))
{
  EmberServices::getSingleton().getConfigService().EventChangedConfigItem.connect(mInternalSlot);
}

ConfigListener::~ConfigListener()
{
  mSlot.disconnect();
  mInternalSlot.disconnect();
}

void ConfigListener::ConfigService_EventChangedConfigItem(const std::string& section, const std::string& key)
{
  if (section == mSection && key == mKey) {
    varconf::Variable variable = EmberServices::getSingleton().getConfigService().getValue(section, key);
    mSlot(section, key, variable);
  }
}

bool ConfigListener::evaluate()
{
  if (EmberServices::getSingleton().getConfigService().itemExists(mSection, mKey)) {
    varconf::Variable variable = EmberServices::getSingleton().getConfigService().getValue(mSection, mKey);
    mSlot(mSection, mKey, variable);
    return true;
  }
  return false;
}

}

