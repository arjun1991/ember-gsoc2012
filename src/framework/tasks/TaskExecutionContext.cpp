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

#include "TaskExecutionContext.h"
#include "TaskExecutor.h"
#include "TaskUnit.h"
#include "ITask.h"

namespace Ember
{
namespace Tasks
{
TaskExecutionContext::TaskExecutionContext(TaskExecutor& executor, TaskUnit& taskUnit) :
	mExecutor(executor), mTaskUnit(taskUnit)
{

}

TaskExecutionContext::~TaskExecutionContext()
{
}

const TaskExecutor& TaskExecutionContext::getExecutor() const
{
	return mExecutor;
}

void TaskExecutionContext::executeTask(ITask* task, ITaskExecutionListener* listener)
{
	TaskUnit* taskUnit = mTaskUnit.addSubtask(task, listener);
	TaskExecutionContext subtaskContext(mExecutor, *taskUnit);
	taskUnit->executeInBackgroundThread(subtaskContext);
}

void TaskExecutionContext::executeTasks(std::vector<ITask*> tasks)
{
	for (std::vector<ITask*>::const_iterator I = tasks.begin(); I != tasks.end(); ++I) {
		executeTask(*I);
	}
}

}
}
