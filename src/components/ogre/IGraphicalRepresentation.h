/*
 Copyright (C) 2009 Erik Hjortsberg <erik.hjortsberg@gmail.com>

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

#ifndef IGRAPHICALREPRESENTATION_H_
#define IGRAPHICALREPRESENTATION_H_

#include "IVisualizable.h"
#include <string>

namespace Ember
{
namespace OgreView
{

class EmberEntity;

/**
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 * @brief A graphical representation of an entity.
 *
 * The entities can be represented through many means inside the world. The most common case would probably be to use an instance of Model, through the ModelRepresentation class, but there are many other cases where another representation would be suitable.
 * All of these representations share this common interface. An instance of this is normally held by an EmberEntity instance.
 *
 * Most of the subclasses of this are expected to provide methods for safely casting into the concrete subclass. The getType() method is expected to be used for helping with this.
 */
class IGraphicalRepresentation : public IVisualizable
{
public:

	/**
	 * @brief Dtor.
	 */
	virtual ~IGraphicalRepresentation()
	{
	}

	/**
	 * @brief Gets the unique type name for a subclass of this.
	 * The main purpose of this is to allow late binding casts, so that it's possible to more safely cast an instance into a concrete subclass.
	 */
	virtual const std::string& getType() const = 0;

};
}

}

#endif /* IGRAPHICALREPRESENTATION_H_ */
