//
// C++ Interface: Case
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
#ifndef EMBEROGRE_MODEL_MAPPING_CASESCASE_H
#define EMBEROGRE_MODEL_MAPPING_CASESCASE_H

#include "CaseBase.h"
namespace Ember {



namespace EntityMapping {

namespace Cases {

/**
	Base class for all Cases that has a parent Match.
	@author Erik Hjortsberg <erik.hjortsberg@gmail.com>
*/
template <class TMatch>
class Case : public CaseBase
{
public:

	Case()
	: mParentMatch(0)
	{}

	virtual ~Case()
	{}

	/**
	Sets the parent Match instance.
	*/
 	void setParentMatch(TMatch* aMatch);


protected:

 	TMatch* mParentMatch;

};

template <class TMatch>
inline void Case<TMatch>::setParentMatch(TMatch* aMatch)
{
	mParentMatch = aMatch;
}

}

}

}

#endif
