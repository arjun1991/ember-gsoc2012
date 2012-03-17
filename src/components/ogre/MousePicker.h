//
// C++ Interface: MousePicker
//
// Description: 
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2004
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
#ifndef EMBEROGRE_MOUSEPICKER_H
#define EMBEROGRE_MOUSEPICKER_H

#include <sigc++/signal.h>


#include "IWorldPickListener.h"
#include "EmberOgrePrerequisites.h"

namespace Ember {
namespace OgreView {


/**
Class used for picking stuff in the world.
Since we sometimes want different picking behaviour (sometimes we want to pick building blocks, sometimes we want to pick entities) it's possible to create derived classes and register them with the GUIManager.

@author Erik Hjortsberg
*/
class MousePicker 
{
public:
	enum ClickMasks
	{
		CM_AVATAR = 1<<9,
		CM_ENTITY = 1<<10,
		CM_NATURE = 1<<11,
		CM_UNDEFINED = 1<<12,
		CM_NONPICKABLE = 1<<13
	};
};

}

}

#endif
