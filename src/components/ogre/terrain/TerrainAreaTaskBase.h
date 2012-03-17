/*
 Copyright (C) 2009 Erik Hjortsberg <erik.hjortsberg@gmail.com>

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

#ifndef EMBEROGRETERRAINTERRAINAREATASKBASE_H_
#define EMBEROGRETERRAINTERRAINAREATASKBASE_H_

#include "framework/tasks/TemplateNamedTask.h"
#include <sigc++/slot.h>

namespace Mercator {

	class Terrain;
	class Area;

}

namespace WFMath {
	template <int> class AxisBox;
}
namespace Ember
{
namespace OgreView
{

namespace Terrain
{

class TerrainArea;
class TerrainShader;

/**
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 * @brief Common base class for terrain area related tasks.
 */
class TerrainAreaTaskBase: public Tasks::TemplateNamedTask<TerrainAreaTaskBase>
{
public:
	typedef sigc::slot<void, const TerrainShader*, const WFMath::AxisBox<2>&> ShaderUpdateSlotType;

	TerrainAreaTaskBase(Mercator::Terrain& terrain, Mercator::Area* area, ShaderUpdateSlotType shaderUpdateSlot);
	virtual ~TerrainAreaTaskBase();

protected:

	/**
	 * @brief The terrain.
	 */
	Mercator::Terrain& mTerrain;

	/**
	 * @brief The terrain area.
	 */
	Mercator::Area* mArea;

	ShaderUpdateSlotType mShaderUpdateSlot;

};

}
}

}

#endif /* EMBEROGRETERRAINTERRAINAREATASKBASE_H_ */
