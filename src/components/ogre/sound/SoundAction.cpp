/*
    Copyright (C) 2008 Romulo Fernandes Machado (nightz)
    Copyright (C) 2008 Erik Hjortsberg <erik.hjortsberg@gmail.com>

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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "SoundAction.h"
#include "SoundEntity.h"
#include "SoundGroup.h"
#include "SoundDefinition.h"
#include "SoundGroupDefinition.h"
#include "SoundDefinitionManager.h"

#include "services/EmberServices.h"
#include "framework/LoggingInstance.h"

#include "services/sound/SoundService.h"
#include "services/sound/SoundInstance.h"
#include "services/sound/SoundSource.h"

#include <map>
#include <cstring>
#include <sstream>

using namespace Ember;

namespace Ember
{
namespace OgreView
{
	SoundAction::SoundAction(SoundEntity& soundEntity)
	: mSoundEntity(soundEntity), mGroup(0), mInstance(0), mIsLooping(false)
	{
	}
	
	SoundAction::~SoundAction()
	{
		if (mInstance) {
			EmberServices::getSingleton().getSoundService().destroyInstance(mInstance);
		}
	}

	SoundGroup* SoundAction::getGroup()
	{
		return mGroup;
	}

	SoundGroup* SoundAction::setGroup(const std::string& name)
	{
		if (mGroup) {
			return 0;
		}
	
		SoundGroupDefinition* groupModel = SoundDefinitionManager::getSingleton().getSoundGroupDefinition(name);

		if (!groupModel)
		{
			S_LOG_FAILURE("A template to the group " << name << " could not be found.");
			return 0;
		}

		SoundGroup* newGroup = new SoundGroup();

		const SoundGroupDefinition::SoundDefinitionStore& soundDefinitions = groupModel->getSoundDefinitions();
		for (SoundGroupDefinition::SoundDefinitionStore::const_iterator I; I != soundDefinitions.end(); I++)
		{
			// Register Individual samples
			const SoundDefinition& thisModel = *I;
			newGroup->addSound(thisModel);
		}

		mGroup = newGroup;
		return newGroup;
	}

	void SoundAction::play()
	{
		if (mGroup) {
			if (!mInstance) {
				mInstance = EmberServices::getSingleton().getSoundService().createInstance();
				if (!mInstance) {
					//The sound system seems to be disabled (could be for a valid reason) so just return without any fuss.
					return;
				}
				mInstance->setMotionProvider(this);
				mInstance->setIsLooping(mIsLooping);
				//If the sound is set not to loop, we need to listen for when it's done playing and remove the instance once it's done (to save on sound resources).
				if (!mIsLooping) {
					mInstance->EventPlayComplete.connect(sigc::mem_fun(*this, &SoundAction::SoundInstance_PlayComplete));
				}
				
				mGroup->bindToInstance(mInstance);
			}
			mInstance->play();
		}
	}

	void SoundAction::stop()
	{
		if (mInstance) {
			EmberServices::getSingleton().getSoundService().destroyInstance(mInstance);
			mInstance = 0;
		}
	}
	
	
	void SoundAction::SoundInstance_PlayComplete()
	{
		if (mInstance) {
			if (EmberServices::getSingleton().getSoundService().destroyInstance(mInstance)) {
				mInstance = 0;
			}
		} else {
			S_LOG_WARNING("Got a play complete signal while there's no sound instance registered. For some reason the sound instance must have already been removed.");
		}
	}
	
	SoundInstance* SoundAction::getInstance() const
	{
		return mInstance;
	}
	
	void SoundAction::update(SoundSource& soundSource)
	{
		soundSource.setPosition(mSoundEntity.getPosition());
// 		soundSource.setVelocity(mSoundEntity.getVelocity());
	}
	
	void SoundAction::setIsLooping(bool isLooping)
	{
		mIsLooping = isLooping;
	}

}
}

