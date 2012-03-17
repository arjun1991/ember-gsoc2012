//
// C++ Implementation: EntityMover
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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "EntityMover.h"
#include "EntityMoveManager.h"
#include "components/ogre/EmberEntity.h"
#include "components/ogre/NodeAttachment.h"
#include "components/ogre/Convert.h"
#include "components/ogre/World.h"
#include "components/ogre/Scene.h"

#include "services/EmberServices.h"
#include "services/server/ServerService.h"
#include <OgreSceneNode.h>

namespace Ember
{
namespace OgreView
{
namespace Authoring
{
EntityMover::EntityMover(NodeAttachment& nodeAttachment, EntityMoveManager& manager) :
	EntityMoverBase(nodeAttachment.getAttachedEntity(), nodeAttachment.getNode(), manager.getWorld().getScene().getSceneManager()), mNodeAttachment(nodeAttachment), mManager(manager), mPreviousControlDelegate(nodeAttachment.getControlDelegate()), mControlDelegate(new EntityMoverControlDelegate(*this))
{
	nodeAttachment.setControlDelegate(mControlDelegate);
}

EntityMover::~EntityMover()
{
	delete mControlDelegate;
}

const IEntityControlDelegate& EntityMover::getControlDelegate() const
{
	return *mControlDelegate;
}

void EntityMover::finalizeMovement()
{
	if (mEntity.getLocation()) {
		//send to server
		EmberServices::getSingleton().getServerService().place(&mEntity, mEntity.getLocation(), getPosition(), getOrientation());
	}
	mNodeAttachment.updatePosition();
	cleanup();
	mManager.EventFinishedMoving.emit();

}
void EntityMover::cancelMovement()
{
	cleanup();
	mNodeAttachment.updatePosition();
	mManager.EventCancelledMoving.emit();
}

void EntityMover::cleanup()
{
	mNodeAttachment.setControlDelegate(mPreviousControlDelegate);
}
void EntityMover::newEntityPosition(const Ogre::Vector3& position)
{
	mNodeAttachment.updatePosition();
}

EntityMoverControlDelegate::EntityMoverControlDelegate(EntityMover& entityMover) :
	mEntityMover(entityMover)
{

}

const WFMath::Point<3>& EntityMoverControlDelegate::getPosition() const
{
	return mEntityMover.getPosition();
}

const WFMath::Quaternion& EntityMoverControlDelegate::getOrientation() const
{
	return mEntityMover.getOrientation();
}

const WFMath::Vector<3>& EntityMoverControlDelegate::getVelocity() const
{
	return WFMath::Vector<3>::ZERO();
}

}

}
}
