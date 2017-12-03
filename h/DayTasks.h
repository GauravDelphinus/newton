/*****************************************************************************
* 
* This header file declares the various Task classes.
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
   21-Aug-2005  Gaurav Jain      Initial Version     -
   04-Sep-2005  Gaurav Jain      Numerous Updates    0.1
*****************************************************************************/
class Task
{
    public:
        string task_name;
        int task_status;
        Task();
        Task(string task_name, int task_status);
        Task(const Task& task);
};

class RecurrentTask;
class DayTasks
{
    public:
        bool isvalid;
        bool isholiday;
        Date date;
        int no_of_tasks;
        int no_of_day_tasks;
        vector<Task> tasks;
        DayTasks();
        DayTasks(int date, int month, int year);
        DayTasks(bool isvalid, bool isholiday, Date date, int no_of_tasks,
                vector<Task> tasks);
        bool isModified(void);
	DayTasks generateAllTasks(void);
	int matchRecurrentTask(RecurrentTask recurrentTask);
};


class WeeklySchedule
{
	public:
		int no_of_days;
		int days[MAX_DAYS_IN_WEEK];
		WeeklySchedule();
		WeeklySchedule(int no_of_days, int days[]);
};

class DailySchedule
{
	public:
		int type;
		DailySchedule();
		DailySchedule(int type);
};
class MonthlySchedule
{
	public:
		int no_of_days;
		int days[MAX_DAYS_IN_MONTH];
		MonthlySchedule();
		MonthlySchedule(int no_of_days, int days[]);
};

class YearlySchedule
{
	public:
		int no_of_dates;
		Date dates[MAX_DAYS_IN_YEAR];
		YearlySchedule();
		YearlySchedule(int no_of_dates, Date dates[]);
};

class Schedule
{
	public:
		int type;
		DailySchedule daily_schedule;
		WeeklySchedule weekly_schedule;
		MonthlySchedule monthly_schedule;
		YearlySchedule yearly_schedule;
		Schedule();
		Schedule(int schedule_type, DailySchedule schedule);
		Schedule(int schedule_type, WeeklySchedule schedule);
		Schedule(int schedule_type, MonthlySchedule schedule);
		Schedule(int schedule_type, YearlySchedule schedule);
};

class RecurrentTask
{
	public:
		Task task;
		Schedule schedule;
		RecurrentTask();
		RecurrentTask(Task task, Schedule schedule);
};
