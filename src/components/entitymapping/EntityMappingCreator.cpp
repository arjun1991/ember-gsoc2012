//
// C++ Implementation: EntityMappingCreator
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

#include "EntityMappingCreator.h"
#include "EntityMapping.h"
#include "EntityMappingManager.h"

#include "Cases/OutfitCase.h"
#include "Cases/AttributeCase.h"
#include "Cases/EntityTypeCase.h"

#include "Cases/AttributeComparers/AttributeComparerWrapper.h"
#include "Cases/AttributeComparers/HeightComparerWrapper.h"
#include "Cases/AttributeComparers/NumericComparer.h"
#include "Cases/AttributeComparers/NumericComparerWrapper.h"
#include "Cases/AttributeComparers/NumericEqualsComparer.h"
#include "Cases/AttributeComparers/NumericEqualsOrGreaterComparer.h"
#include "Cases/AttributeComparers/NumericEqualsOrLesserComparer.h"
#include "Cases/AttributeComparers/NumericGreaterComparer.h"
#include "Cases/AttributeComparers/NumericLesserComparer.h"
#include "Cases/AttributeComparers/NumericRangeComparer.h"
#include "Cases/AttributeComparers/NumericValueHolder.h"
#include "Cases/AttributeComparers/StringComparer.h"
#include "Cases/AttributeComparers/StringComparerWrapper.h"


#include "Matches/OutfitMatch.h"
#include "Matches/AttributeMatch.h"
#include "Matches/EntityTypeMatch.h"
#include "Matches/Observers/AttributeObserver.h"
#include "Matches/Observers/EntityCreationObserver.h"

#include "IActionCreator.h"

namespace Ember {



namespace EntityMapping {

using namespace Definitions;
using namespace Matches;
using namespace Observers;
using namespace Cases;
using namespace AttributeComparers;

static const CaseDefinition::ParameterEntry* findCaseParameter(const CaseDefinition::ParameterStore& parameters, const std::string& type)
{
	for (CaseDefinition::ParameterStore::const_iterator I = parameters.begin(); I != parameters.end(); ++I) {
		if (I->first == type) {
			return &(*I);
		}
	}
	return 0;
}

EntityMappingCreator::EntityMappingCreator(EntityMappingDefinition& definition, Eris::Entity& entity, IActionCreator* actionCreator, Eris::TypeService& typeService, Eris::View* view)
: mActionCreator(actionCreator), mEntity(entity), mModelMap(0), mDefinition(definition), mTypeService(typeService), mView(view)
{
}


EntityMappingCreator::~EntityMappingCreator()
{
}

EntityMapping* EntityMappingCreator::create()
{
	return createMapping();
}


EntityMapping* EntityMappingCreator::createMapping() {
	mModelMap = new EntityMapping(mEntity);
	addEntityTypeCases(&mModelMap->getRootEntityMatch(), mDefinition.getRoot());

	//since we already have the entity, we can perform a check right away
	mModelMap->getRootEntityMatch().setEntity(&mEntity);
// 	mModelMap->getRootEntityMatch().testEntity(mEntity);
	return mModelMap;
}

void EntityMappingCreator::addEntityTypeCases(EntityTypeMatch* entityTypeMatch, MatchDefinition& matchDefinition) {
	MatchDefinition::CaseStore::iterator endI = matchDefinition.getCases().end();
	for (MatchDefinition::CaseStore::iterator I = matchDefinition.getCases().begin(); I != endI; ++I) {
		EntityTypeCase* aCase = new EntityTypeCase();

		for (CaseDefinition::ParameterStore::iterator J = I->getCaseParameters().begin(); J != I->getCaseParameters().end(); ++J) {
			if (J->first == "equals") {
				aCase->addEntityType(mTypeService.getTypeByName(J->second));
			}
		}

/*			const std::string& entityName = I->getProperties()["equals"];
		std::vector<std::string> splitNames = EntityMappingManager::splitString(entityName, "|", 100);
		for (std::vector<std::string>::const_iterator J = splitNames.begin(); J != splitNames.end(); ++J) {
			aCase->addEntityType(mTypeService.getTypeByName(*J));
		}*/
		if (mActionCreator) {
			mActionCreator->createActions(*mModelMap, aCase, *I);
		}

		CaseDefinition::MatchStore::iterator endJ = I->getMatches().end();
		for (CaseDefinition::MatchStore::iterator J = I->getMatches().begin(); J != endJ; ++J) {
			addMatch(aCase, *J);
		}
		entityTypeMatch->addCase( aCase);
		aCase->setParentMatch( entityTypeMatch);
	}
}

void EntityMappingCreator::addOutfitCases(OutfitMatch* match, MatchDefinition& matchDefinition)
{
	MatchDefinition::CaseStore::iterator endI = matchDefinition.getCases().end();
	for (MatchDefinition::CaseStore::iterator I = matchDefinition.getCases().begin(); I != endI; ++I) {
		OutfitCase* aCase = new OutfitCase();

		for (CaseDefinition::ParameterStore::iterator J = I->getCaseParameters().begin(); J != I->getCaseParameters().end(); ++J) {
			if (J->first == "equals") {
				aCase->addEntityType(mTypeService.getTypeByName(J->second));
			}
		}
/*			const std::string& entityName = I->getProperties()["equals"];
		std::vector<std::string> splitNames = EntityMappingManager::splitString(entityName, "|", 100);
		for (std::vector<std::string>::const_iterator J = splitNames.begin(); J != splitNames.end(); ++J) {
			aCase->addEntityType(mTypeService.getTypeByName(*J));
		}*/
		if (mActionCreator) {
			mActionCreator->createActions(*mModelMap, aCase, *I);
		}

		CaseDefinition::MatchStore::iterator endJ = I->getMatches().end();
		for (CaseDefinition::MatchStore::iterator J = I->getMatches().begin(); J != endJ; ++J) {
			addMatch(aCase, *J);
		}
		match->addCase( aCase);
		aCase->setParentMatch( match);
	}
}


Cases::AttributeComparers::AttributeComparerWrapper* EntityMappingCreator::getAttributeCaseComparer(AttributeMatch* match, MatchDefinition& matchDefinition, CaseDefinition& caseDefinition)
{
	const std::string& matchType = matchDefinition.getProperties()["type"];

	if ((matchType == "") || (matchType == "string")) {
		//default is string comparison
		if (const CaseDefinition::ParameterEntry* param = findCaseParameter(caseDefinition.getCaseParameters(), "equals")) {
			return new AttributeComparers::StringComparerWrapper(new AttributeComparers::StringComparer(param->second));
		} else {
			return new AttributeComparers::StringComparerWrapper(new AttributeComparers::StringComparer(""));
		}
/*
		const std::string& attributeValue = caseDefinition.getProperties()["equals"];
		return new AttributeComparers::StringComparerWrapper(new AttributeComparers::StringComparer(attributeValue));*/
	} else if (matchType == "numeric") {
		return new AttributeComparers::NumericComparerWrapper(createNumericComparer(caseDefinition));
	} else if (matchType == "function") {
		if (match->getAttributeName() == "height") {
			return new AttributeComparers::HeightComparerWrapper(createNumericComparer(caseDefinition), mEntity);
		}
	}
	return 0;

}

AttributeComparers::NumericComparer* EntityMappingCreator::createNumericComparer(CaseDefinition& caseDefinition)
{
	const CaseDefinition::ParameterEntry* param(0);

// 	DefinitionBase::PropertiesMap::const_iterator value;
// 	DefinitionBase::PropertiesMap::const_iterator end = caseDefinition.getProperties().end();
// 	value = caseDefinition.getProperties().find("equals");

	if ((param = findCaseParameter(caseDefinition.getCaseParameters(), "equals"))) {
		return new AttributeComparers::NumericEqualsComparer(atof(param->second.c_str()));
	}

	//If both a min and max value is set, it's a range comparer
	AttributeComparers::NumericComparer *mMin(0), *mMax(0);
	if ((param = findCaseParameter(caseDefinition.getCaseParameters(), "lesser"))) {
		mMin = new AttributeComparers::NumericLesserComparer(atof(param->second.c_str()));
	} else if ((param = findCaseParameter(caseDefinition.getCaseParameters(), "lesserequals"))) {
		mMin = new AttributeComparers::NumericEqualsOrLesserComparer(atof(param->second.c_str()));
	}

	if ((param = findCaseParameter(caseDefinition.getCaseParameters(), "greater"))) {
		mMax = new AttributeComparers::NumericGreaterComparer(atof(param->second.c_str()));
	} else if ((param = findCaseParameter(caseDefinition.getCaseParameters(), "greaterequals"))) {
		mMax = new AttributeComparers::NumericEqualsOrGreaterComparer(atof(param->second.c_str()));
	}

	//check if we have both min and max set, and if so we should use a range comparer
	if (mMin && mMax) {
		return new AttributeComparers::NumericRangeComparer(mMin, mMax);
	} else if (!mMax && mMin) {
		return mMin;
	} else if (mMax && !mMin) {
		return mMax;
	}
	//invalid, could not find anything to compare against
	return 0;
}


void EntityMappingCreator::addAttributeCases(AttributeMatch* match, MatchDefinition& matchDefinition) {
	MatchDefinition::CaseStore::iterator endI = matchDefinition.getCases().end();
	for (MatchDefinition::CaseStore::iterator I = matchDefinition.getCases().begin(); I != endI; ++I) {
		Cases::AttributeComparers::AttributeComparerWrapper* wrapper = getAttributeCaseComparer(match, matchDefinition, *I);
		if (wrapper) {
			AttributeCase* aCase = new AttributeCase(wrapper);

			if (mActionCreator) {
				mActionCreator->createActions(*mModelMap, aCase, *I);
			}

			CaseDefinition::MatchStore::iterator endJ = I->getMatches().end();
			for (CaseDefinition::MatchStore::iterator J = I->getMatches().begin(); J != endJ; ++J) {
				addMatch(aCase, *J);
			}
			match->addCase( aCase);
			aCase->setParentMatch( match);
		}
	}

}

void EntityMappingCreator::addMatch(CaseBase* aCase, MatchDefinition& matchDefinition) {
	if (matchDefinition.getType() == "attribute") {
		addAttributeMatch(aCase, matchDefinition);
	} else if (matchDefinition.getType() == "entitytype") {
		addEntityTypeMatch(aCase, matchDefinition);
	} else if (matchDefinition.getType() == "outfit") {
		addOutfitMatch(aCase, matchDefinition);
	}
}

void EntityMappingCreator::addAttributeMatch(CaseBase* aCase, MatchDefinition& matchDefinition) {
	const std::string& attributeName = matchDefinition.getProperties()["attribute"];

	std::string internalAttributeName("");
	const std::string& matchType = matchDefinition.getProperties()["type"];
	//TODO: make this check better
	if (matchType == "function") {
		if (attributeName == "height") {
			internalAttributeName = "bbox";
		}
	}
	if (internalAttributeName == "") {
		internalAttributeName = attributeName;
	}

	AttributeMatch* match = new AttributeMatch(attributeName, internalAttributeName);
	aCase->addMatch( match);

	AttributeObserver* observer = new AttributeObserver(match, internalAttributeName);
	match->setAttributeObserver(observer);

	addAttributeCases(match, matchDefinition);

}

void EntityMappingCreator::addEntityTypeMatch(CaseBase* aCase, MatchDefinition& matchDefinition) {
	EntityTypeMatch* match = new EntityTypeMatch();
	aCase->addMatch( match);
	addEntityTypeCases(match, matchDefinition);

	//since we already have the entity, we can perform a check right away
// 	match->testEntity(mEntity);
}

void EntityMappingCreator::addOutfitMatch(CaseBase* aCase, MatchDefinition& matchDefinition)
{
	if (mView) {
		const std::string& attachmentName = matchDefinition.getProperties()["attachment"];
		OutfitMatch* match = new OutfitMatch(attachmentName, mView);
		aCase->addMatch( match);

		addOutfitCases(match, matchDefinition);


		//observe the attribute by the use of an AttributeObserver
		AttributeObserver* observer= new AttributeObserver(match, "outfit");
		match->setAttributeObserver(observer);

		EntityCreationObserver* entityObserver = new EntityCreationObserver(*match);
		match->setEntityCreationObserver(entityObserver);
	}

}

}

}
