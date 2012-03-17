//
// C++ Interface: SizeAdapter
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
#ifndef EMBEROGRE_GUI_ADAPTERS_ATLASSIZEADAPTER_H
#define EMBEROGRE_GUI_ADAPTERS_ATLASSIZEADAPTER_H

#include "AdapterBase.h"

namespace Ember
{
namespace OgreView
{

namespace Gui
{

namespace Adapters
{

namespace Atlas
{

/**
 @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 */
class SizeAdapter: public AdapterBase
{
public:
  SizeAdapter(const ::Atlas::Message::Element& element, CEGUI::Window* lowerXWindow, CEGUI::Window* lowerYWindow, CEGUI::Window* lowerZWindow, CEGUI::Window* upperXWindow, CEGUI::Window* upperYWindow, CEGUI::Window* upperZWindow, CEGUI::Slider* scaler, CEGUI::Window* infoWindow);

  virtual ~SizeAdapter();

  /**
   Updates the gui with new values.
   */
  virtual void updateGui(const ::Atlas::Message::Element& element);

protected:
  CEGUI::Window* mLowerXWindow;
  CEGUI::Window* mLowerYWindow;
  CEGUI::Window* mLowerZWindow;
  CEGUI::Window* mUpperXWindow;
  CEGUI::Window* mUpperYWindow;
  CEGUI::Window* mUpperZWindow;
  CEGUI::Slider* mScaler;
  CEGUI::Window* mInfoWindow;

  /**
   Updates the info window with measurement information.
   */
  void updateInfo();

  bool window_TextChanged(const CEGUI::EventArgs& e);
  bool slider_ValueChanged(const CEGUI::EventArgs& e);

  virtual void fillElementFromGui();
  virtual bool _hasChanges();
};

}

}

}

}

}

#endif
