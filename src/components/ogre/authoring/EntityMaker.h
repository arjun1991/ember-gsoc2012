/*
 Copyright (C) 2011 Erik Hjortsberg

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

#ifndef ENTITYMAKER_H_
#define ENTITYMAKER_H_

#include "framework/ConsoleCommandWrapper.h"
#include "framework/ConsoleObject.h"

namespace Eris
{
class TypeInfo;
class Connection;
class Entity;
}

namespace Ember {
namespace OgreView {
namespace Authoring {

/**
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 *
 * Enables the creation of entities through the "/make <entitytype>" and "/createentity <entitytype>" console commands.
 * The entity will be created in front of the avatar.
 *
 */
class EntityMaker : public ConsoleObject
{
public:

	/**
	 * @brief Ctor.
	 * @param avatarEntity The avatar entity.
	 * @param connection The connection to the server.
	 */
	EntityMaker(Eris::Entity& avatarEntity, Eris::Connection& connection);

	/**
	 * @brief Dtor.
	 */
	virtual ~EntityMaker();

	virtual void runCommand(const std::string &command, const std::string &args);

	/**
	 * @brief Console command "/createentity <entitytype>".
	 *
	 * Will create an entity in front of the avatar.
	 */
	const ConsoleCommandWrapper CreateEntity;

	/**
	 * @brief Console command "/make <entitytype>".
	 *
	 * Will create an entity in front of the avatar.
	 */
	const ConsoleCommandWrapper Make;


protected:

	/**
	 * @brief The avatar entity.
	 */
	Eris::Entity& mAvatarEntity;

	/**
	 * @brief The connection to the server.
	 */
	Eris::Connection& mConnection;

	/**
	 * @brief Creates a new entity of the supplied type, placed in front of the avatar.
	 * @param typeinfo The kind of entity to create.
	 * @param name The optional name of the enttity. If empty, the type name will be used.
	 */
	void createEntityOfType(Eris::TypeInfo* typeinfo, const std::string& name = "");

};

}
}
}
#endif /* ENTITYMAKER_H_ */
