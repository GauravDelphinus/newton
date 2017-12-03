/*****************************************************************************
* 
* This source file implements the various tasks.
*
*****************************************************************************/
/*****************************************************************************
    Copyright (C) 2005 Gaurav Jain

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
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*****************************************************************************/
/*****************************************************************************
   Revision History

   Date         Updater          Comment             Revision
   27-Aug-2005  Gaurav Jain      Initial Version     -
   03-Sep-2005  Gaurav Jain      Numerous Updates    0.1
*****************************************************************************/
#include "Common.h"

/*
 * create an empty task.
 */
Task::Task()
{
}

/*
 * create a new task with the given
 * name and status.
 */
Task::Task(string task_name, int task_status)
{
    this->task_name = task_name;
    this->task_status = task_status;
}

/*
 * copy a task.
 */
Task::Task(const Task& task)
{
	this->task_name = task.task_name;
	this->task_status = task.task_status;
}

/*
 * create a new default 
 * DayTasks object.
 */
DayTasks::DayTasks()
{
    /* This is set to false by default */
    isvalid = false;
    no_of_tasks = 0;
}

/*
 * create a new Daytasks object,
 * initializing it with the given date.
 */
DayTasks::DayTasks(int date_in, int month_in, int year_in)
{
    Date date_new = Date(date_in, month_in, year_in);
    DayTasks temp_day_tasks = g_task_list.getTasks(date_new);
    if (temp_day_tasks.isvalid == true)
    {
        /* Some change has happened to this day */
        *this = temp_day_tasks;
    }
    else
    {
        isvalid = false;
        no_of_tasks = 0;
        if ((date_new.day_of_week == DAY_SUNDAY) || (date_new.day_of_week ==
                DAY_SATURDAY))
        {
            isholiday = true;
        }
        else
        {
            isholiday = false;
        }
        date = date_new;
    }
}

/*
 * set up a new DayTasks object,
 * addign the tasks to it.
 */
DayTasks::DayTasks(bool isvalid_in, bool isholiday_in, Date date_in, 
        int no_of_tasks_in, vector<Task> tasks_in)
{
    isvalid = isvalid_in;
    isholiday = isholiday_in;
    date = date_in;
    no_of_tasks = no_of_tasks_in;
    tasks = tasks_in;
}

/*
 * return whether a task has
 * been modified by the user.
 */
bool DayTasks::isModified(void)
{
    if (no_of_tasks > 0)
        return true;
    if ((date.day_of_week == DAY_SUNDAY) || (date.day_of_week == DAY_SATURDAY))
    {
        if (isholiday == false)
        {
            return true;
        }
    }
    else 
    {
        if (isholiday == true)
        {
            return true;
        }
    }
    return false;
}

/*
 * initialize the WeeklySchedule
 * object.
 */
WeeklySchedule::WeeklySchedule(void)
{
	no_of_days = 0;
}

/*
 * initialize the object with
 * weekly schedule.
 */
WeeklySchedule::WeeklySchedule(int no_of_days, int days[])
{
	int i;
	this->no_of_days = no_of_days;
	for (i = 0; i < no_of_days; i++)
		this->days[i] = days[i];
}

/*
 * create default daily schedule.
 */
DailySchedule::DailySchedule()
{
	type = DAILY_SCHEDULE_ALL_DAYS;
}

/* create a daily scheudle
 * of the given type.
 */
DailySchedule::DailySchedule(int type)
{
	this->type = type;
}

/*
 * create a default monthly schedule.
 */
MonthlySchedule::MonthlySchedule()
{
	no_of_days = 0;
}

/*
 * create a monthly schedule
 * wth the given schedule.
 */
MonthlySchedule::MonthlySchedule(int no_of_days, int days[])
{
	int i;
	this->no_of_days = no_of_days;
	for (i = 0; i < no_of_days; i++)
		this->days[i] = days[i];
}

/*
 * create a default yearly schedule.
 */
YearlySchedule::YearlySchedule()
{
	no_of_dates = 0;
}

/* 
 * create a yearly schedule and
 * set up the schedule
 */
YearlySchedule::YearlySchedule(int no_of_dates, Date dates[])
{
	int i = 0;
	this->no_of_dates = no_of_dates;
	for (i = 0; i < no_of_dates; i++)
		this->dates[i] = dates[i];
}

/*
 * create empty schedule
 */
Schedule::Schedule()
{
}

/*
 * initialize a schedule that
 * encapsulates a daily schedule.
 */
Schedule::Schedule(int schedule_type, DailySchedule schedule)
{
	type = schedule_type;
	daily_schedule = schedule;
}

/*
 * initialize a schedule that
 * encapsulates a weekly schedule.
 */
Schedule::Schedule(int schedule_type, WeeklySchedule schedule)
{
	type = schedule_type;
	weekly_schedule = schedule;
}

/*
 * initialize a schedule that
 * encapsulates a monthly schedule.
 */
Schedule::Schedule(int schedule_type, MonthlySchedule schedule)
{
	type = schedule_type;
	monthly_schedule = schedule;
}

/*
 * initialize a schedule that
 * encapsulates a yearly schedule.
 */
Schedule::Schedule(int schedule_type, YearlySchedule schedule)
{
	type = schedule_type;
	yearly_schedule = schedule;
}

/*
 * create an empty recurrent task.
 */
RecurrentTask::RecurrentTask()
{
}

/*
 * create a recurrent task
 * with the givn schedule.
 */
RecurrentTask::RecurrentTask(Task task, Schedule schedule)
{
	this->task = task;
	this->schedule = schedule;
}

/*
 * combine the day tasks, and the recurrent
 * tasks to create an "all tasks" object,
 * so that this can be used to show to the
 * user.
 */
DayTasks DayTasks::generateAllTasks(void)
{
	vector<RecurrentTask> applicableList;
	int i, j;
	DayTasks all_tasks;

	for (i = 0; i < g_task_list.getRecurrentTaskCount(); i++)
	{
		RecurrentTask recurrentTask = g_task_list.getRecurrentTask(i);
		if (matchRecurrentTask(recurrentTask))
		{
			applicableList.push_back(recurrentTask);
		}
	}

	for (i = 0; i < no_of_tasks; i++)
	{
		for (j = 0; j < (int)applicableList.size(); j++)
		{
			if (strcmp(tasks[i].task_name.c_str(), applicableList[j].task.task_name.c_str()) == 0)
			{
				/* match occurred, remove from applicable list */
				applicableList.erase(applicableList.begin() + j);
				break;
			}
		}
	}

	all_tasks = *this;
	all_tasks.no_of_day_tasks = no_of_tasks;
	for (i = 0; i < (int)applicableList.size(); i++)
	{
		all_tasks.tasks.push_back(applicableList[i].task);
		all_tasks.no_of_tasks++;
	}

	return all_tasks;
}

/*
 * match the given recurrent tas to the
 * current date's tasks, to see if it
 * applies to the curren date.
 */
int DayTasks::matchRecurrentTask(RecurrentTask recurrentTask)
{
	int i;
	
	if (recurrentTask.schedule.type == DAILY_SCHEDULE)
	{
		if (recurrentTask.schedule.daily_schedule.type == DAILY_SCHEDULE_ALL_DAYS)
		{
			return 1;
		}
		else if (recurrentTask.schedule.daily_schedule.type == DAILY_SCHEDULE_ONLY_HOLIDAYS)
		{
			if (isholiday)
				return 1;
		}
		else if (recurrentTask.schedule.daily_schedule.type == DAILY_SCHEDULE_ONLY_WORKING_DAYS)
		{
			if (!isholiday)
				return 1;
		}
	}
	else if (recurrentTask.schedule.type == WEEKLY_SCHEDULE)
	{
		for (i = 0; i < recurrentTask.schedule.weekly_schedule.no_of_days; i++)
		{
			if (recurrentTask.schedule.weekly_schedule.days[i] == date.day_of_week)
				return 1;
		}
	}
	else if (recurrentTask.schedule.type == MONTHLY_SCHEDULE)
	{
		for (i = 0; i < recurrentTask.schedule.monthly_schedule.no_of_days; i++)
		{
			if (recurrentTask.schedule.monthly_schedule.days[i] == date.date)
				return 1;
			
		}
	}
	else if (recurrentTask.schedule.type == YEARLY_SCHEDULE)
	{
		for (i = 0; i < recurrentTask.schedule.yearly_schedule.no_of_dates; i++)
		{
			if ((recurrentTask.schedule.yearly_schedule.dates[i].date == date.date) && 
				(recurrentTask.schedule.yearly_schedule.dates[i].month == date.month))
				return 1;
			
		}
	}

	return 0;
}
