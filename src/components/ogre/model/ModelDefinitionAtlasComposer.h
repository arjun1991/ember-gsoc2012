//
// C++ Interface: ModelDefinitionAtlasComposer
//
// Description: 
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2008
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
#ifndef EMBEROGRE_MODELMODELDEFINITIONATLASCOMPOSER_H
#define EMBEROGRE_MODELMODELDEFINITIONATLASCOMPOSER_H

#include <Atlas/Message/Element.h>

namespace Ember {
namespace OgreView {

namespace Model {

class Model;

/**
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 *
 * @brief Composes a skeleton Atlas representation based on a Model instance.
 *
 * This is useful when you already have a model (most often made up by a mesh) and want to create a server entity type for it.
 * The Atlas data created is pretty bare, mainly providing a correct bounding box which perfectly fits with the bounding box of the model.
 */
class ModelDefinitionAtlasComposer{
public:

	/**
	 * @brief Composes Atlas data from a supplied model.
	 *
	 * @param model The model for which we want Atlas data generated.
	 * @param typeName The name of the type which should be generated.
	 * @param parentTypeName The name of the parent of the new type (for example "thing" or "mobile").
	 * @param scale Any scale to apply to the bounding box which is generated.
	 * @return Atlas data describing a type.
	 */
    Atlas::Message::MapType compose(Model* model, const std::string& typeName, const std::string& parentTypeName, float scale);

    /**
     * @brief Composes Atlas data from a supplied model and exports it to a stream.
     *
     * @param outstream A stream to export to.
	 * @param model The model for which we want Atlas data generated.
	 * @param typeName The name of the type which should be generated.
	 * @param parentTypeName The name of the parent of the new type (for example "thing" or "mobile").
	 * @param scale Any scale to apply to the bounding box which is generated.
     */
    void composeToStream(std::iostream& outstream, Model* model, const std::string& typeName, const std::string& parentTypeName, float scale);

    /**
     * @brief Composes Atlas data from a supplied model and exports it to a file.
     *
	 * @param model The model for which we want Atlas data generated.
	 * @param typeName The name of the type which should be generated.
	 * @param parentTypeName The name of the parent of the new type (for example "thing" or "mobile").
	 * @param scale Any scale to apply to the bounding box which is generated.
     * @return The path of the file to which the Atlas data was exported. An empty string if the exporting failed.
     */
    std::string composeToFile(Model* model, const std::string& typeName, const std::string& parentTypeName, float scale);

};

}

}

}

#endif
