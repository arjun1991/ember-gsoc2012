//
// C++ Implementation: TerrainPageSurfaceCompiler
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

#include "TerrainPageSurfaceCompiler.h"
#include "TerrainPageShadow.h"
#include "TerrainPageSurfaceLayer.h"
#include "ICompilerTechniqueProvider.h"
#include "TerrainPageGeometry.h"
#include "../ShaderManager.h"
#include "../EmberOgre.h"

namespace Ember
{
namespace OgreView
{
namespace Terrain
{

TerrainPageSurfaceCompiler::TerrainPageSurfaceCompiler(ICompilerTechniqueProvider& compilerTechniqueProvider) :
    mCompilerTechniqueProvider(compilerTechniqueProvider)
{
}

TerrainPageSurfaceCompiler::~TerrainPageSurfaceCompiler()
{
}

TerrainPageSurfaceCompilationInstance* TerrainPageSurfaceCompiler::createCompilationInstance(const TerrainPageGeometryPtr& geometry, const SurfaceLayerStore& terrainPageSurfaces, const TerrainPageShadow* terrainPageShadow) const
{
  return new TerrainPageSurfaceCompilationInstance(mCompilerTechniqueProvider.createTechnique(geometry, terrainPageSurfaces, terrainPageShadow));

}

TerrainPageSurfaceCompilationInstance::TerrainPageSurfaceCompilationInstance(TerrainPageSurfaceCompilerTechnique* technique) :
    mTechnique(technique)
{

}

TerrainPageSurfaceCompilationInstance::~TerrainPageSurfaceCompilationInstance()
{
  delete mTechnique;
}

bool TerrainPageSurfaceCompilationInstance::prepare()
{
  return mTechnique->prepareMaterial();
}

bool TerrainPageSurfaceCompilationInstance::compile(Ogre::MaterialPtr material)
{
  return mTechnique->compileMaterial(material);
}

}
}
}
