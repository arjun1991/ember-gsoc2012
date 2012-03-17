/*
 Copyright (C) 2009 Erik Hjortsberg

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

#ifndef TASKEXECUTIONLISTENER_H_
#define TASKEXECUTIONLISTENER_H_

#include "framework/Exception.h"

namespace Ember
{

namespace Tasks
{

/**
 * @author Erik Hjortsberg <erik.hjortsberg@gmail.com>
 * @brief A listener for tasks being executed.
 */
class ITaskExecutionListener
{
public:
	/**
	 * @brief Dtor.
	 */
	virtual ~ITaskExecutionListener()
	{
	}
	;

	/**
	 * @brief Called when execution has started.
	 */
	virtual void executionStarted() = 0;

	/**
	 * @brief Called when execution has ended.
	 */
	virtual void executionEnded() = 0;

	/**
	 * @brief Called when an error occurred during execution.
	 * @param exception Describes the error.
	 */
	virtual void executionError(const Exception& exception) = 0;
};

}

}

#endif /* TASKEXECUTIONLISTENER_H_ */
