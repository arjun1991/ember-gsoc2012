/*-----------------------------------------------------------------------------
 This source file is part of OGRE
 (Object-oriented Graphics Rendering Engine)
 For the latest info, see http://www.ogre3d.org/

 Copyright � 2000-2004 The OGRE Team
 Also see acknowledgements in Readme.html
 
 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License along with
 this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 Place - Suite 330, Boston, MA 02111-1307, USA, or go to
 http://www.gnu.org/copyleft/lesser.txt.
 -----------------------------------------------------------------------------*/

#ifndef __PagingLandScapePageSourceListener_H__
#define __PagingLandScapePageSourceListener_H__

namespace Ogre
{
/** Abstract class which classes can override to receive notifications
 * when a page is ready to be added to the terrain manager.
 *
 * \todo mafm: not really used by anyone
 */
class PagingLandScapeListener
{

public:
  PagingLandScapeListener()
  {
  }
  virtual ~PagingLandScapeListener()
  {
  }
  /** Listener method called when a new page is about to be constructed. 
   @param pagex, pagez The index of the page being constructed
   @param heightData Array of normalised height data (0..1). The size of
   this buffer will conform to the scene manager page size. The listener
   may modify the data if it wishes.
   */
  virtual void pagePreloaded(size_t pagex, size_t pagez, const Real* heightData, const AxisAlignedBox& Bbox)
  {
  }
  virtual void pageLoaded(size_t pagex, size_t pagez, const Real* heightData, const AxisAlignedBox& Bbox)
  {
  }
  virtual void pageUnloaded(size_t pagex, size_t pagez, const Real* heightData, const AxisAlignedBox& Bbox)
  {
  }
  virtual void pagePostunloaded(size_t pagex, size_t pagez)
  {
  }
  virtual void pageShow(size_t pagex, size_t pagez, const Real* heightData, const AxisAlignedBox& Bbox)
  {
  }
  virtual void pageHide(size_t pagex, size_t pagez, const Real* heightData, const AxisAlignedBox& Bbox)
  {
  }
  virtual void tileLoaded(size_t pagex, size_t pagez, size_t tilex, size_t tilez, const AxisAlignedBox& Bbox)
  {
  }
  virtual void tileUnloaded(size_t pagex, size_t pagez, size_t tilex, size_t tilez, const AxisAlignedBox& Bbox)
  {
  }
  virtual void tileDeformed(size_t pagex, size_t pagez, size_t tilex, size_t tilez, const AxisAlignedBox& Bbox)
  {
  }
  virtual void tileShow(size_t pagex, size_t pagez, size_t tilex, size_t tilez, const AxisAlignedBox& Bbox)
  {
  }
  virtual void tileHide(size_t pagex, size_t pagez, size_t tilex, size_t tilez, const AxisAlignedBox& Bbox)
  {
  }
  virtual void terrainReady()
  {
  }

};
}

#endif //__PagingLandScapePageSourceListener_H__
