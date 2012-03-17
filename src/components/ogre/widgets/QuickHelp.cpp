//
// C++ Implementation: QuickHelp
//
// Description:
//
//
// Author: Tiberiu Paunescu <tpa12@sfu.ca>, (C) 2010
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

#include "QuickHelp.h"

template<> Ember::OgreView::Gui::QuickHelp* Ember::Singleton<Ember::OgreView::Gui::QuickHelp>::ms_Singleton = 0;

using namespace Ember;
namespace Ember
{
namespace OgreView
{

namespace Gui
{

QuickHelp::QuickHelp()
{

}

QuickHelp::~QuickHelp()
{
	mTutorialText.clear();
}

const std::list<HelpMessage>::const_iterator QuickHelp::getEnd() const
{
	return mTutorialText.end();
}

const std::list<HelpMessage>::const_iterator QuickHelp::getBeginning() const
{
	return mTutorialText.begin();
}

const std::list<HelpMessage>::const_iterator QuickHelp::insertAtEnd(const HelpMessage& message)
{
	mTutorialText.push_back(message);
	EventHelpMessageLocationChanged.emit(getSize());
	return --(mTutorialText.end());
}

const std::list<HelpMessage>::const_iterator QuickHelp::messagePosition(const HelpMessage& message)
{
	//If the message doesn't have an optional id, we can just insert.
	if (!message.hasId())
	{
		return insertAtEnd(message);
	}

	//Does the Id exist? If it does, return the position.
	int location = 1;
	for (std::list<HelpMessage>::const_iterator list_iterator = mTutorialText.begin(); list_iterator != mTutorialText.end(); list_iterator++)
	{

		if (list_iterator->getId() == message.getId())
		{
			EventHelpMessageLocationChanged.emit(location);
			return list_iterator;
		}
		location++;
	}

	//Message has a unique id, and isn't inserted.
	return insertAtEnd(message);
}

void QuickHelp::updateText(const HelpMessage& message)
{
	if (mTutorialText.size() == MAXTUTORIALS)
		mTutorialText.pop_front();

	EventHelpMessageAdded.emit(messagePosition(message));
}

const int QuickHelp::getSize() const
{
	return mTutorialText.size();
}

void QuickHelp::showWidget() const
{
	EventToggleWidgetVisibility.emit();
}

}
}
}
