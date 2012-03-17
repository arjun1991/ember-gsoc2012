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

#ifndef EMBEROGRETERRAINTECHNIQUESSHADERPASS_H_
#define EMBEROGRETERRAINTECHNIQUESSHADERPASS_H_

#include "components/ogre/OgreIncludes.h"
#include <wfmath/point.h>
#include <vector>
#include <string>

namespace Ember
{
namespace OgreView
{

namespace Terrain
{
class TerrainPage;
class TerrainPageSurfaceLayer;
class TerrainPageGeometry;
class TerrainPageShadow;

namespace Techniques
{

class ShaderPassCoverageBatch;

typedef std::vector<const TerrainPageSurfaceLayer*> LayerStore;

class ShaderPass
{
public:
  friend class ShaderPassCoverageBatch;
  ShaderPass(Ogre::SceneManager& sceneManager, int coveragePixelWidth, const WFMath::Point<2>& position);
  virtual ~ShaderPass();

  virtual void addLayer(const TerrainPageGeometry& geometry, const TerrainPageSurfaceLayer* layer);
  virtual void setBaseLayer(const TerrainPageSurfaceLayer* layer);
  void addShadowLayer(const TerrainPageShadow* terrainPageShadow);

  virtual bool hasRoomForLayer(const TerrainPageSurfaceLayer* layer);

  /**
   * @brief Creates the combined final coverage textures and sets the shader params. Be sure to call this before you load the material.
   * @param useShadows Whether to use shadows or not in the pass.
   * @param shaderSuffix A suffix to add to the shader name. This allows you to make it use a somewhat different shader depending on graphics level etc.
   * @return True if the creation of the pass was successful.
   */
  virtual bool finalize(Ogre::Pass& pass, bool useShadows = true, const std::string shaderSuffix = "") const;

  LayerStore& getLayers();

protected:
  typedef std::vector<ShaderPassCoverageBatch*> CoverageBatchStore;

  void assignCombinedCoverageTexture();
  ShaderPassCoverageBatch* getCurrentBatch();
  virtual ShaderPassCoverageBatch* createNewBatch();

  unsigned int getCoveragePixelWidth() const;
  Ogre::TexturePtr getCombinedCoverageTexture(size_t passIndex, size_t batchIndex) const;

  float mScales[16];
  CoverageBatchStore mCoverageBatches;
  LayerStore mLayers;
  const TerrainPageSurfaceLayer* mBaseLayer;
  Ogre::SceneManager& mSceneManager;
  int mCoveragePixelWidth;
  WFMath::Point<2> mPosition;

  unsigned int mShadowLayers;
};
}

}

}

}

#endif /* EMBEROGRETERRAINTECHNIQUESSHADERPASS_H_ */
