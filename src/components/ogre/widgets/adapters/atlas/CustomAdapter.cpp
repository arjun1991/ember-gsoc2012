//
// C++ Implementation: CustomAdapter
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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "CustomAdapter.h"
using Atlas::Message::Element;
using Atlas::Message::ListType;
using Atlas::Message::MapType;

namespace Ember {
namespace OgreView {

namespace Gui {

namespace Adapters {

namespace Atlas {

CustomAdapter::CustomAdapter(const ::Atlas::Message::Element& element)
: AdapterBase(element)
{
}


CustomAdapter::~CustomAdapter()
{
}

void CustomAdapter::updateGui(const ::Atlas::Message::Element& element)
{
	QueryUpdateGui(&element);
}

void CustomAdapter::fillElementFromGui()
{
	Element element;
	QueryFillElementFromGui(&element);
}
bool CustomAdapter::_hasChanges()
{
	bool hasChanges;
	QueryHasChanges(hasChanges);
	return hasChanges;
}
::Atlas::Message::Element CustomAdapter::_getChangedElement()
{
	Element element;
	QueryGetChangedElement(&element);
	return element;
}


}

}

}

}
}
