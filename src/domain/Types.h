//
// C++ Interface: Types
//
// Description: Common types for EmberOgre.
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2009
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
#ifndef EMBER_DOMAIN_TYPES_H
#define EMBER_DOMAIN_TYPES_H

namespace std
{
template <typename, typename> class pair;
}

namespace WFMath
{
template<int> class Point;
}

namespace Ember {
namespace Domain {

/**
 * @brief A 2d position in the world.
 */
typedef WFMath::Point<2> TerrainPosition;

/**
 * @brief A 2d index in the world.
 */
typedef std::pair<int, int> TerrainIndex;

}
}
#endif //EMBER_DOMAIN_TYPES_H
