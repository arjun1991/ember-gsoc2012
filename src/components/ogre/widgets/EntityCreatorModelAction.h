//
// C++ Interface: EntityCreatorModelAction
//
// Description:
//
//
// Author: Alexey Torkhov <atorkhov@gmail.com>, (C) 2008
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2009
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
#ifndef EMBEROGRE_GUIENTITYCREATORMODELACTION_H
#define EMBEROGRE_GUIENTITYCREATORMODELACTION_H

#include "components/entitymapping/Actions/Action.h"
#include <string>

namespace Ember {
namespace OgreView {

namespace Gui {

class EntityCreatorCreationInstance;

/**
 * @brief Shows or hides specific model in entity creator preview.
 */
class EntityCreatorModelAction : public EntityMapping::Actions::Action
{
public:
	EntityCreatorModelAction(EntityCreatorCreationInstance& creationInstance, const std::string& modelName);
	virtual ~EntityCreatorModelAction();
	/**
	 * Shows specific model. Called by model mapping framework.
	 */
	virtual void activate(EntityMapping::ChangeContext& context);
	/**
	 * Hides model. Called by model mapping framework.
	 */
	virtual void deactivate(EntityMapping::ChangeContext& context);
protected:
	EntityCreatorCreationInstance& mCreationInstance;
	const std::string mModelName;
};

}

}

}

#endif
