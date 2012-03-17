//
// C++ Interface: IServerAdapter
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
#ifndef EMBERISERVERADAPTER_H
#define EMBERISERVERADAPTER_H

#include <Atlas/Objects/Entity.h>

#include <wfmath/atlasconv.h>
#include <wfmath/point.h>

namespace Eris
{
class Entity;
}

namespace Ember
{

/**
 @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 */
class IServerAdapter
{
public:

  virtual ~IServerAdapter()
  {
  }

  virtual void moveToPoint(const WFMath::Point<3>& dest) = 0;
  virtual void moveInDirection(const WFMath::Vector<3>& velocity, const WFMath::Quaternion& orientation) = 0;
  virtual void moveInDirection(const WFMath::Vector<3>& velocity) = 0;
// 	virtual void teleportTo(const WFMath::Point<3>& dest) = 0;
  virtual void say(const std::string &message) = 0;

  /**
   * @brief Says something, addressed to a list of entities.
   *
   * Note that the message will be heard by everyone within earshot, even those not addressed.
   *
   * @param message The message.
   * @param entities A list of entities to which the message will be addressed.
   */
  virtual void sayTo(const std::string &message, const std::vector<const Eris::Entity*>& entities) = 0;

  /**
   * @brief Says something, addressed to an entity.
   *
   * Note that the message will be heard by everyone within earshot, even those not addressed.
   *
   * @param message The message.
   * @param entities The entity to which the message is addressed.
   */
  virtual void sayTo(const std::string &message, const Eris::Entity& entity) = 0;
  virtual void touch(Eris::Entity* entity) = 0;
  virtual void emote(const std::string& emote) = 0;
  virtual void drop(Eris::Entity* entity, const WFMath::Vector<3>& offset, const WFMath::Quaternion& orientation) = 0;
  virtual void place(Eris::Entity* entity, Eris::Entity* target, const WFMath::Point<3>& pos = WFMath::Point<3>(0, 0, 0)) = 0;
  virtual void place(Eris::Entity* entity, Eris::Entity* target, const WFMath::Point<3>& pos, const WFMath::Quaternion& orient) = 0;
  virtual void wield(Eris::Entity* entity, const std::string& outfitSlot) = 0;
  virtual void take(Eris::Entity* entity) = 0;
  virtual void use(Eris::Entity* entity, WFMath::Point<3> pos, const std::string& operation) = 0;
  virtual void useStop() = 0;
  virtual void actuate(Eris::Entity* entity, const std::string& action) = 0;
  virtual void attack(Eris::Entity* entity) = 0;
  virtual void eat(Eris::Entity* entity) = 0;
  virtual void deleteEntity(Eris::Entity* entity) = 0;
  virtual void setAttributes(Eris::Entity* entity, Atlas::Message::MapType& attributes) = 0;
  virtual void adminTell(const std::string& entityId, const std::string& attribute, const std::string &value) = 0;
  virtual void createTypeInfo(const Atlas::Objects::Root& typeInfo) = 0;
  virtual void setTypeInfo(const Atlas::Objects::Root& typeInfo) = 0;
};

}

#endif
