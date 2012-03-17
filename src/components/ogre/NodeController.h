/*
 Copyright (C) 2009 Erik Hjortsberg

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
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef NodeController_H_
#define NodeController_H_

#include "components/ogre/IMovable.h"

#include <sigc++/trackable.h>

namespace Ember
{
namespace OgreView
{

class NodeAttachment;
class IEntityControlDelegate;

/**
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 * @brief Handles the position and orientation updates of a NodeAttachment.
 *
 * This functionality is separated from the NodeAttachment so that it will be possible to intercept and alter it, as is the case when a player controls one of the entities.
 * In normal behavior, all position and orientation updates are fetched from the entity to which the attachment is attached.
 * This class is however expected to be extended with a subclass which provides other behavior.
 */
class NodeController: public virtual sigc::trackable, public IMovable
{
public:
	/**
	 * @brief Ctor.
	 * @param The attachment which will be controlled.
	 */
	NodeController(NodeAttachment& attachment);

	/**
	 * @brief Dtor.
	 */
	virtual ~NodeController();

	virtual void updateMotion(float timeSlice);

	void forceMovementUpdate();

	virtual IEntityControlDelegate* getControlDelegate() const;

protected:

	NodeAttachment& mAttachment;

	void movementUpdate();
	void entity_Moved();
	virtual void updatePosition();

};

}

}

#endif /* NodeController_H_ */
