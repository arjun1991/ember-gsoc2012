//
// C++ Implementation: EntityMappingManager
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

#include "EntityMappingManager.h"

#include "EntityMappingCreator.h"
namespace Ember {



namespace EntityMapping {

using namespace Definitions;

EntityMappingManager::EntityMappingManager()
: mTypeService(0)
{
}


EntityMappingManager::~EntityMappingManager()
{
	for (EntityMappingDefinitionStore::iterator I = mDefinitions.begin(); I != mDefinitions.end(); ++I) {
		delete I->second;
	}
}


std::vector<std::string> EntityMappingManager::splitString( const std::string& str, const std::string& delims, unsigned int maxSplits)
{
	// static unsigned dl;
	std::vector<std::string> ret;
	unsigned int numSplits = 0;

	// Use STL methods
	size_t start, pos;
	start = 0;
	do
	{
		pos = str.find_first_of(delims, start);
		if (pos == start)
		{
			// Do nothing
			start = pos + 1;
		}
		else if (pos == std::string::npos || (maxSplits && numSplits == maxSplits))
		{
			// Copy the rest of the string
			ret.push_back( str.substr(start) );
			break;
		}
		else
		{
			// Copy up to delimiter
			ret.push_back( str.substr(start, pos - start) );
			start = pos + 1;
		}
		// parse up to next real data
		start = str.find_first_not_of(delims, start);
		++numSplits;

	} while (pos != std::string::npos);



	return ret;
}

void EntityMappingManager::addDefinition(EntityMappingDefinition* definition)
{
	std::pair<EntityMappingDefinitionStore::iterator, bool> result = mDefinitions.insert(EntityMappingDefinitionStore::value_type(definition->getName(), definition));

	//If it was already added, delete the definition now.
	if (!result.second) {
		delete definition;
	} else {
		MatchDefinition::CaseStore::iterator endI = definition->getRoot().getCases().end();
		for (MatchDefinition::CaseStore::iterator I = definition->getRoot().getCases().begin(); I != endI; ++I) {
			for (CaseDefinition::ParameterStore::const_iterator J = I->getCaseParameters().begin(); J != I->getCaseParameters().end(); ++J) {
				if (J->first == "equals") {
					mEntityTypeMappings[J->second] = definition;
				}
			}
	/*		const std::string& entityName = I->getProperties()["equals"];
			std::vector<std::string> splitNames = splitString(entityName, "|", 100);
			for (std::vector<std::string>::const_iterator I = splitNames.begin(); I != splitNames.end(); ++I) {
				mEntityTypeMappings[*I] = definition;
			}*/
		}
	}
}

EntityMappingDefinition* EntityMappingManager::getDefinitionForType(Eris::TypeInfo* typeInfo) {
	bool noneThere = false;
	while (!noneThere) {
		std::map<std::string, EntityMappingDefinition*>::iterator I = mEntityTypeMappings.find(typeInfo->getName());
		if (I != mEntityTypeMappings.end()) {
			return I->second;
		} else {
			if (typeInfo->getParents().size() == 0) {
				noneThere = true;
			} else {
				typeInfo = *(typeInfo->getParents().begin());
			}
		}
	}
	return 0;
}

EntityMapping* EntityMappingManager::createMapping(Eris::Entity& entity, IActionCreator* actionCreator, Eris::View* view) {
	if (mTypeService) {
		Eris::TypeInfo* type = entity.getType();
		EntityMappingDefinition* definition = getDefinitionForType(type);
		if (definition) {
			EntityMappingCreator creator(*definition, entity, actionCreator, *mTypeService, view);
			return creator.create();
		}
	}
	return 0;
}

}

}
