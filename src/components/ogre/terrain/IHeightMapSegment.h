/*
 Copyright (C) 2010 Erik Hjortsberg <erik.hjortsberg@gmail.com>

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

#ifndef EMBEROGRETERRAINIHEIGHTMAPSEGMENT_H_
#define EMBEROGRETERRAINIHEIGHTMAPSEGMENT_H_

#include "Types.h"

namespace WFMath
{
template<int> class Vector;
}

namespace Ember
{
namespace OgreView
{
namespace Terrain
{

/**
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 * @brief Represents one segment (mapped to a Mercator::Segment) in the height map.
 */
class IHeightMapSegment
{
public:

  virtual ~IHeightMapSegment()
  {
  }

  /**
   * @brief Gets the height at the specified location.
   * This is a crude and fast lookup method which won't take into account slopes.
   * @see getHeightAndNormal()
   * @param x The x location, in world units.
   * @param y The y location, in world units.
   * @returns The height at the location.
   */
  virtual float getHeight(int x, int y) const = 0;

  /**
   * @brief Gets the height and normal at the location.
   * This calculates slopes and provides a precise height. It's therefore more time consuming than getHeight().
   * @param x The x location, in world units.
   * @param y The y location, in world units.
   * @param height The height will be stored here.
   * @param normal The normal will be stored here.
   */
  virtual void getHeightAndNormal(float x, float y, float& height, WFMath::Vector<3>& normal) const = 0;
};
}
}

}

#endif /* EMBEROGRETERRAINIHEIGHTMAPSEGMENT_H_ */
