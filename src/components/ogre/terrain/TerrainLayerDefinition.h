//
// C++ Interface: TerrainLayerDefinition
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
#ifndef EMBEROGRE_TERRAINTERRAINLAYERDEFINITION_H
#define EMBEROGRE_TERRAINTERRAINLAYERDEFINITION_H

#include <string>
#include <map>
#include <vector>


namespace Ember {
namespace OgreView {

namespace Terrain {

class TerrainFoliageDefinition;

/**
	@author Erik Hjortsberg <erik.hjortsberg@gmail.com>
*/
class TerrainLayerDefinition {
public:
	typedef std::map<std::string, std::string> StringParamStore;
	typedef std::vector<TerrainFoliageDefinition> TerrainFoliageDefinitionStore;
    
    TerrainLayerDefinition();

    ~TerrainLayerDefinition();
    
    /**
     * @brief Sets a descriptive name for the layer.
     * @param name A descriptive name.
     */
    void setName(const std::string& name);
    
    /**
     * @brief Gets the descriptive name for the layer.
     * @return The descriptive name.
     */
    const std::string& getName() const;
    
    void setAreaId(unsigned int areaId);
    unsigned int getAreaId() const;
    
    void setDiffuseTextureName(const std::string& textureName);
    const std::string& getDiffuseTextureName() const;
    
    void setNormalMapTextureName(const std::string& textureName);
    const std::string& getNormalMapTextureName() const;
    
    void setShaderName(const std::string& shaderName);
    const std::string& getShaderName() const;
    
    void setTileSize(float tileSize);
    float getTileSize() const;

	const TerrainFoliageDefinitionStore& getFoliages() const;
	TerrainFoliageDefinitionStore& getFoliages();
	

protected:

	unsigned int mAreaId;
	std::string mName;
	std::string mDiffuseTextureName;
	std::string mNormalMapTextureName;
	std::string mShaderName;
	float mTileSize;
	
	TerrainFoliageDefinitionStore mFoliages;

};

class TerrainFoliageDefinition
{
public:
	const TerrainLayerDefinition::StringParamStore& getParameters() const;
	TerrainLayerDefinition::StringParamStore& getParameters();
	const std::string& getParameter(const std::string& key) const;
	bool hasParameter(const std::string& key) const;

	void setPlantType(const std::string& theValue);
	const std::string& getPlantType() const;

	void setPopulationTechnique (const std::string& theValue);
	const std::string& getPopulationTechnique() const;
	
	void setRenderTechnique (const std::string& theValue);
	const std::string& getRenderTechnique() const;
	
protected:
	TerrainLayerDefinition::StringParamStore mParameters;
	std::string mPlantType;
	std::string mPopulationTechnique;
	std::string mRenderTechnique;
};

}

}

}

#endif
