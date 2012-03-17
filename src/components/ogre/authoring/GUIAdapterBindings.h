/*
 Copyright (C) 2008  Alexey Torkhov <atorkhov@gmail.com>

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

#ifndef EMBEROGRE_GUIADAPTERBINDINGS_H
#define EMBEROGRE_GUIADAPTERBINDINGS_H

#include "components/ogre/EmberOgrePrerequisites.h"
#include "framework/tinyxml/tinyxml.h"
#include <Atlas/Message/Element.h>

namespace Ember
{
namespace OgreView
{
namespace Authoring
{
/**
 * Contains bindings of one placeholder to many GUI adapters.
 */
class GUIAdapterBindings
{
public:
	/**
	 * Constructor.
	 */
	GUIAdapterBindings();

	/**
	 * Destructor.
	 */
	virtual ~GUIAdapterBindings();

	/**
	 * Returns bound function
	 */
	const std::string& getFunc();

	/**
	 * Sets bound function
	 */
	void setFunc(std::string func);

	/**
	 * Add bound adapter
	 */
	void addAdapter(std::string adapterName);

	/**
	 * Return adapters list
	 */
	std::vector<std::string>& getAdapters();

	/**
	 * Associates this bindings with XML element
	 */
	void associateXmlElement(TiXmlNode& element);

	/**
	 * Sets value to associated element
	 */
	void setValue(Atlas::Message::Element& val);

	/**
	 * Helper function, converting Atlas node into TinyXml node
	 */
	static TiXmlNode* convertAtlasToXml(Atlas::Message::Element& val);

protected:
	/**
	 * Bound function name
	 */
	std::string mFunc;

	/**
	 * List of bound adapters.
	 */
	std::vector<std::string> mAdapters;

	/**
	 * Associated XML element
	 */
	TiXmlNode* mElement;
};

}
}
}
#endif
