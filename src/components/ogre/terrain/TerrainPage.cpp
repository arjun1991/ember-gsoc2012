//
// C++ Implementation: TerrainPage
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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "TerrainPage.h"

#include "TerrainPageGeometry.h"
#include "TerrainShader.h"
#include "TerrainPageSurfaceLayer.h"

#include "../EmberOgre.h"
#include "../Convert.h"

#include "TerrainInfo.h"
#include "TerrainPageSurfaceLayer.h"
#include "TerrainPageSurface.h"
#include "TerrainLayerDefinition.h"
#include "ISceneManagerAdapter.h"

#include "framework/LoggingInstance.h"
#include "services/config/ConfigService.h"

#include "framework/osdir.h"

#include <wfmath/axisbox.h>
#include <wfmath/vector.h>

#include <Mercator/Segment.h>
#include <Mercator/Shader.h>

namespace Ember
{
namespace OgreView
{
namespace Terrain
{

TerrainPage::TerrainPage(const Domain::TerrainIndex& index, int pageSize, ICompilerTechniqueProvider& compilerTechniqueProvider) :
	mIndex(index), mPageSize(pageSize), mPosition(index.first, index.second), mTerrainSurface(new TerrainPageSurface(*this, compilerTechniqueProvider)),  mExtent(WFMath::Point<2>(mPosition.x() * (getPageSize() - 1), (mPosition.y() - 1) * (getPageSize() - 1)), WFMath::Point<2>((mPosition.x() + 1) * (getPageSize() - 1), (mPosition.y()) * (getPageSize() - 1)))
{

	S_LOG_VERBOSE("Creating TerrainPage at position " << index.first << ":" << index.second);
}

TerrainPage::~TerrainPage()
{
}

int TerrainPage::getPageSize() const
{
	return mPageSize;
}

int TerrainPage::getVerticeCount() const
{
	return (getPageSize() * getPageSize());
}

int TerrainPage::getNumberOfSegmentsPerAxis() const
{
	return (getPageSize() - 1) / 64;
}

const Domain::TerrainPosition& TerrainPage::getWFPosition() const
{
	return mPosition;
}

const Domain::TerrainIndex& TerrainPage::getWFIndex() const
{
	return mIndex;
}


const Ogre::MaterialPtr TerrainPage::getMaterial() const
{
	return mTerrainSurface->getMaterial();
}

unsigned int TerrainPage::getAlphaMapScale() const
{
	ConfigService& configSrv = EmberServices::getSingleton().getConfigService();
	if (configSrv.itemExists("terrain", "scalealphamap")) {
		int value = (int)configSrv.getValue("terrain", "scalealphamap");
		//make sure it can't go below 1
		return std::max<int>(1, value);
	} else {
		return 1;
	}
}

const WFMath::AxisBox<2>& TerrainPage::getWorldExtent() const
{
	return mExtent;
}

const TerrainPageSurface* TerrainPage::getSurface() const
{
	return mTerrainSurface.get();
}

TerrainPageSurfaceLayer* TerrainPage::addShader(const TerrainShader* shader)
{
	TerrainPageSurfaceLayer* layer = mTerrainSurface->createSurfaceLayer(shader->getLayerDefinition(), shader->getTerrainIndex(), shader->getShader());
	layer->setDiffuseTextureName(shader->getLayerDefinition().getDiffuseTextureName());
	layer->setNormalTextureName(shader->getLayerDefinition().getNormalMapTextureName());
	//get the scale by dividing the total size of the page with the size of each tile
	float scale = getAlphaTextureSize() / shader->getLayerDefinition().getTileSize();
	layer->setScale(scale);
	return layer;
}

void TerrainPage::updateAllShaderTextures(TerrainPageGeometry& geometry, bool repopulate)
{
	TerrainPageSurface::TerrainPageSurfaceLayerStore::const_iterator I = mTerrainSurface->getLayers().begin();
	for (; I != mTerrainSurface->getLayers().end(); ++I) {
		mTerrainSurface->updateLayer(geometry, I->second->getSurfaceIndex(), repopulate);
	}
}

TerrainPageSurfaceLayer* TerrainPage::updateShaderTexture(const TerrainShader* shader, TerrainPageGeometry& geometry, bool repopulate)
{
	TerrainPageSurfaceLayer* layer;
	TerrainPageSurface::TerrainPageSurfaceLayerStore::const_iterator I = mTerrainSurface->getLayers().find(shader->getTerrainIndex());
	if (I == mTerrainSurface->getLayers().end()) {
		layer = addShader(shader);
	} else {
		layer = I->second;
	}
	mTerrainSurface->updateLayer(geometry, shader->getTerrainIndex(), repopulate);

	return layer;
}


}
}
}
