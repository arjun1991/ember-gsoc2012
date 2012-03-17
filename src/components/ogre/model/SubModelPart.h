/*
 -------------------------------------------------------------------------------
 This source file is part of Cataclysmos
 For the latest info, see http://www.cataclysmos.org/

 Copyright (c) 2005 The Cataclysmos Team
 Copyright (C) 2005  Erik Hjortsberg

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 -------------------------------------------------------------------------------
 */
#ifndef SUBMODELPART_H
#define SUBMODELPART_H

#include "components/ogre/EmberOgrePrerequisites.h"

#include <set>
#include <vector>

namespace Ogre
{
class SubEntity;
}

namespace Ember
{
namespace OgreView
{
namespace Model
{

class SubModel;
class Model;
class ModelDefinition;
class SubEntityDefinition;

class SubModelPartEntity
{
public:
  SubModelPartEntity(Ogre::SubEntity* s, SubEntityDefinition* d) :
      SubEntity(s), Definition(d)
  {
  }

  Ogre::SubEntity* SubEntity;
  SubEntityDefinition* Definition;
};

class SubModelPart
{
  friend class ModelDefinition;
public:
  typedef std::set<Ogre::SubEntity*> SubEntitySet;
  typedef std::vector<SubModelPartEntity> SubModelPartEntityStore;

  SubModelPart(const std::string& name);
  virtual ~SubModelPart();

  bool addSubEntity(Ogre::SubEntity* subentity, SubEntityDefinition* definition);
  bool removeSubEntity(const Ogre::SubEntity* subentity);

  void show();
  void hide();

  const std::string& getName() const;

  const SubModelPartEntityStore& getSubentities() const;

protected:
  std::string mName;
  SubModelPartEntityStore mSubEntities;
};

}
}
}
#endif // SUBMODELPART_H
