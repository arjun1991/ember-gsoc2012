//
// C++ Interface: IconManager
//
// Description: 
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2007
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
#ifndef EMBEROGRE_GUI_ICONSICONMANAGER_H
#define EMBEROGRE_GUI_ICONSICONMANAGER_H

#include "IconStore.h"
#include "IconRenderer.h"

namespace Eris 
{
	class TypeInfo;
}

namespace Ember {
namespace OgreView {

	class EmberEntity;

namespace Gui {

namespace Icons {


/**
	@author Erik Hjortsberg <erik.hjortsberg@gmail.com>
*/
class IconManager{
public:

    IconManager();

    ~IconManager();
    
    Icon* getIcon(int pixelWidth, EmberEntity* entity);
    Icon* getIcon(int pixelWidth, Eris::TypeInfo* erisType);

    void render(Icon& icon, const std::string& modelName);
    void render(Icon& icon, EmberEntity& entity);
    void render(Icon& icon, Eris::TypeInfo& erisType);

protected:

	IconStore mIconStore;
	IconRenderer mIconRenderer;
	

};

}

}

}

}

#endif
