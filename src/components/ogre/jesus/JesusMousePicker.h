//
// C++ Interface: JesusMousePicker
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
#ifndef EMBEROGREJESUSMOUSEPICKER_H
#define EMBEROGREJESUSMOUSEPICKER_H

#include "../EmberOgrePrerequisites.h"
#include "../MousePicker.h"

namespace Ember
{
namespace OgreView
{

class ModelBlock;
class AttachPointNode;

/**
 @author Erik Hjortsberg
 */
class JesusMousePicker: public MousePicker
{
public:
  JesusMousePicker();

  virtual ~JesusMousePicker();

  virtual void doMousePicking(const Ogre::Real x, const Ogre::Real y, const MousePickerArgs& args);
  virtual void initializePickingContext();
  /**
   Called when the picking is over, either because one of the processPickResult calls set continuePicking to false, or because there are no more objects to pick.
   */
  virtual void endPickingContext(const MousePickerArgs& mousePickerArgs)
  {
  }

  sigc::signal<void, ModelBlock*, const MousePickerArgs&> EventPickedModelBlock;
  sigc::signal<void, AttachPointNode*, const MousePickerArgs&> EventPickedAttachPointNode;

protected:

  virtual void onEventPickedModelBlock(ModelBlock* modelBlock, const MousePickerArgs& args);
  virtual void onEventPickedAttachPointNode(AttachPointNode* node, const MousePickerArgs& args);

};
}

}

#endif
