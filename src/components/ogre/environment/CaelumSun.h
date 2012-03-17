//
// C++ Interface: CaelumSun
//
// Description:
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2006
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
#ifndef EMBEROGRECAELUMSUN_H
#define EMBEROGRECAELUMSUN_H
#include "components/ogre/EmberOgrePrerequisites.h"
#include "CaelumEnvironment.h"
#include "services/config/ConfigListenerContainer.h"

namespace Ember
{
class ConfigListener;
}

namespace varconf
{
class Variable;
}

namespace Ember {
namespace OgreView {



namespace Environment {

/**
	@author Erik Hjortsberg <erik.hjortsberg@gmail.com>
*/
class CaelumSun :  public CaelumEnvironmentComponent, public ISun, public ConfigListenerContainer
{
public:
    CaelumSun(CaelumEnvironment& environment, Caelum::BaseSkyLight* sun);

    virtual ~CaelumSun();

	virtual void setAmbientLight(const Ogre::ColourValue& colour);

	virtual Ogre::Vector3 getSunDirection() const;

	virtual WFMath::Vector<3> getMainLightDirection() const;

	virtual Ogre::ColourValue getAmbientLightColour() const;

private:

	Caelum::BaseSkyLight* mSun;


	/**
	 *    Listend for changes to the config.
	 * @param section
	 * @param key
	 * @param variable
	 */
	void Config_SunAmbientMultiplier(const std::string& section, const std::string& key, varconf::Variable& variable);
	/**
	 *    Listend for changes to the config.
	 * @param section
	 * @param key
	 * @param variable
	 */
	void Config_SunDiffuseMultiplier(const std::string& section, const std::string& key, varconf::Variable& variable);
	/**
	 *    Listend for changes to the config.
	 * @param section
	 * @param key
	 * @param variable
	 */
	void Config_SunSpecularMultiplier(const std::string& section, const std::string& key, varconf::Variable& variable);



	bool parse(varconf::Variable& variable, Ogre::ColourValue& colour);
};

}

}

}

#endif
