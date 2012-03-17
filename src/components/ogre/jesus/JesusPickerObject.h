//
// C++ Interface: JesusPickerObject
//
// Description:
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2005
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
#ifndef EMBEROGREJESUSPICKEROBJECT_H
#define EMBEROGREJESUSPICKEROBJECT_H

#include "../EmberOgrePrerequisites.h"
#include <OgreUserDefinedObject.h>

namespace Ember {
namespace OgreView {

class ModelBlock;
class AttachPointNode;

/**
@author Erik Hjortsberg
*/
class JesusPickerObject : public Ogre::UserDefinedObject
{
public:
	static const std::string s_TypeName;
    JesusPickerObject(ModelBlock* modelBlock, AttachPointNode* pointNode);

    virtual ~JesusPickerObject();

	ModelBlock* getModelBlock() const;
	AttachPointNode* getPointNode() const;
	virtual const Ogre::String & 	getTypeName (void) const;
protected:
ModelBlock* mModelBlock;
AttachPointNode* mPointNode;

};

inline ModelBlock* JesusPickerObject::getModelBlock() const { return mModelBlock; }
inline AttachPointNode* JesusPickerObject::getPointNode() const { return mPointNode; }

}

}

#endif
