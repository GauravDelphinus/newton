/*****************************************************************************
* 
* This source file implements the File DB interface class.
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

   Date         Updater          Comment            Revision
   21-Aug-2005  Gaurav Jain      Initial Version    -
   03-Sep-2005  Gaurav Jain      Numerous Updates   0.1
*****************************************************************************/
#include "Common.h"

/*
 * read the task database from the
 * disk into memory.  Return 0 on
 * success, and -1 on failure.
 */
int GlobalTaskList::loadTasks(void)
{
    char input_file[100];
    char line[800];
    char *dir = getenv("NEWTON_BASE_DIR");
    FILE *p_output_file = NULL;
    int ret_val = 0;
    int retVal = 0;
    char copy_file_name[100];
    char copy_cmd_str[100];
    FILE *file_ptr = NULL;

    if (dir == NULL)
    {
        return -1;
    }

    strcpy(input_file, dir);
    strcat(input_file, "/tasks.db");

    p_output_file = fopen(input_file, "r");
    if (NULL == p_output_file)
    {
        return -1;
    }

    /* Create a backup of the file for safety for now! */
    strcpy(copy_file_name, "baks/tasks.db");
    while (1)
    {
        strcat(copy_file_name, ".bak");
        if ((file_ptr = fopen(copy_file_name, "r")) == NULL)
        {
            break;
        }
        fclose(file_ptr);
    }
    sprintf(copy_cmd_str, "cp -f %s %s", input_file, copy_file_name);
    system(copy_cmd_str);

    while (1)
    {
        ret_val = fscanf(p_output_file, " %[^\n]", line);
        if (ret_val == EOF)
        {
            break;
        }
        
	if (strncmp(line, "recurrent", strlen("recurrent")) == 0)
		retVal = parseLineForRecurrentTask(line);
	else
		retVal = parseLineForTask(line);
    }
    fclose(p_output_file);

    return retVal;
}

/*
 * parse the given line for a regular daily
 * task. return -1 in case of error, otherwise
 * 0.
 */
int GlobalTaskList::parseLineForTask(char *line)
{
	bool isvalid;
	Date date;
	vector<Task> tasks;
	int no_of_tasks;
	int next_task_status;
	char *p_date = NULL, *p_month = NULL, *p_year = NULL, *p_is_holiday = NULL;
	int date_int = 0, month_int = 0, year_int = 0;
	char *p_no_of_tasks = NULL, *p_next_task_name = NULL, *p_next_task_status =
		NULL;
	int isholiday = 0;
	string next_task_name; 
	p_date = line;
	p_month = strchr(line, '\t') + 1;
	p_year = strchr(p_month, '\t') + 1;
	p_is_holiday = strchr(p_year, '\t') + 1;

	p_date[p_month - p_date - 1] = '\0';
	date_int = atoi(p_date);

	p_month[p_year - p_month - 1] = '\0';
	month_int = atoi(p_month);

	p_year[p_is_holiday - p_year - 1] = '\0';
	year_int = atoi(p_year);

	date = Date(date_int, month_int, year_int);

	p_no_of_tasks = strchr(p_is_holiday, '\t') + 1;

	p_is_holiday[p_no_of_tasks - p_is_holiday - 1] = '\0';
	isholiday = atoi(p_is_holiday);

	p_next_task_name = strchr(p_no_of_tasks, '\t');
	if (NULL == p_next_task_name)
	{
		no_of_tasks = 0;
	}
	else
	{
		p_next_task_name ++;
		p_no_of_tasks[p_next_task_name - p_no_of_tasks - 1] = '\0';
		no_of_tasks = atoi(p_no_of_tasks);
		while (1)
		{
			p_next_task_status = strchr(p_next_task_name, '\t') + 1;
			p_next_task_name[p_next_task_status - p_next_task_name - 1] = '\0';
			next_task_name = p_next_task_name;

			p_next_task_name = strchr(p_next_task_status, '\t');
			if (NULL == p_next_task_name)
			{
				next_task_status = atoi(p_next_task_status);
				tasks.push_back(Task(next_task_name, next_task_status));
				break;
			}
			p_next_task_name++;
			p_next_task_status[p_next_task_name - p_next_task_status - 1] =
				'\0';
			next_task_status = atoi(p_next_task_status);
			tasks.push_back(Task(next_task_name, next_task_status));
		}
	}
	/* Set as valid */
	isvalid = true;
	DayTasks day_tasks = DayTasks(isvalid, isholiday, date, no_of_tasks,
			tasks);
	if (day_tasks.isModified())
	{
		task_list[date] = day_tasks;
	}
	return 0;
}

/*
 * parse the given line for a recurrent task.
 * return 0 for success, -1 for failure.
 */
int GlobalTaskList::parseLineForRecurrentTask(char *line)
{
	int schedule_type, daily_subtype, no_of_days, no_of_dates, task_status;
	int next_day, next_month;
	char *p_recurrent_tag = NULL, *p_schedule_type = NULL, *p_task_status = NULL, *p_task_name = NULL, *p_next = NULL, *p_subtype = NULL, *p_no_of_days = NULL, *p_next_day = NULL, *p_next_month = NULL;
	int weekly_days[MAX_DAYS_IN_WEEK];
	int monthly_days[MAX_DAYS_IN_MONTH];
	Date yearly_dates[MAX_DAYS_IN_YEAR];
	string task_name; 
	Schedule schedule;

	p_recurrent_tag = line;
	p_task_status = strchr(line, '\t') + 1;
	p_task_name = strchr(p_task_status, '\t') + 1;
	p_task_status[p_task_name - p_task_status - 1] = '\0';
	task_status = atoi(p_task_status);

	p_schedule_type = strchr(p_task_name, '\t') + 1;
	p_task_name[p_schedule_type - p_task_name - 1] = '\0';

	p_next = strchr(p_schedule_type, '\t') + 1;
	p_schedule_type[p_next - p_schedule_type - 1] = '\0';

	schedule_type = atoi(p_schedule_type);

	if (schedule_type == DAILY_SCHEDULE)
	{
		/* <status>	1	<type>*/
		p_subtype = p_next;
		daily_subtype = atoi(p_subtype);
		schedule = Schedule(schedule_type, DailySchedule(daily_subtype));
	}
	else if (schedule_type == WEEKLY_SCHEDULE)
	{
		/* <status>	2	<no_of_days>	<day_1>	<day_2>... */
		p_no_of_days = p_next;
		p_next = strchr(p_no_of_days, '\t');
		if (p_next == NULL)
			no_of_days = 0;
		else
		{
			p_next_day = p_next + 1;
			p_no_of_days[p_next_day - p_no_of_days - 1] = '\0';
			no_of_days = atoi(p_no_of_days);
			int j = 0;
			while (1)
			{
				p_next = strchr(p_next_day, '\t');
				if (p_next == NULL)
				{
					weekly_days[j] = atoi(p_next_day);
					break;
				}
				else
				{
					p_next = p_next + 1;
					p_next_day[p_next - p_next_day - 1] = '\0';
					weekly_days[j] = atoi(p_next_day);
				}
				j++;
				p_next_day = p_next;
			}
			j++;
			if (j < no_of_days)
				return -1;
		}
		schedule = Schedule(schedule_type, WeeklySchedule(no_of_days, weekly_days));
	}
	else if (schedule_type == MONTHLY_SCHEDULE)
	{
		/* <status>	3	<no_of_days>	<day_1>	<day_2>... */
		p_no_of_days = p_next;
		p_next = strchr(p_no_of_days, '\t');
		if (p_next == NULL)
			no_of_days = 0;
		else
		{
			p_next_day = p_next + 1;
			p_no_of_days[p_next_day - p_no_of_days - 1] = '\0';
			no_of_days = atoi(p_no_of_days);
			int j = 0;
			while (1)
			{
				p_next = strchr(p_next_day, '\t');
				if (p_next == NULL)
				{
					monthly_days[j] = atoi(p_next_day);
					break;
				}
				else
				{
					p_next = p_next + 1;
					p_next_day[p_next - p_next_day - 1] = '\0';
					monthly_days[j] = atoi(p_next_day);
				}
				j++;
				p_next_day = p_next;
			}
			j++;
			if (j < no_of_days)
				return -1;
		}
		schedule = Schedule(schedule_type, MonthlySchedule(no_of_days, monthly_days));
	}
	else if (schedule_type == YEARLY_SCHEDULE)
	{
		/* <status>	4	<no_of_dates>	<day_1>	<mont_1> <year_1> <day_2> ... */
		p_no_of_days = p_next;
		p_next = strchr(p_no_of_days, '\t');
		if (p_next == NULL)
			no_of_dates = 0;
		else
		{
			p_next_day = p_next + 1;
			p_no_of_days[p_next_day - p_no_of_days - 1] = '\0';
			no_of_dates = atoi(p_no_of_days);
			int j = 0;
			while (1)
			{
				p_next_month = strchr(p_next_day, '\t') + 1;
				p_next_day[p_next_month - p_next_day - 1] = '\0';
				next_day = atoi(p_next_day);
				p_next = strchr(p_next_month, '\t');
				if (p_next == NULL)
				{
					next_month = atoi(p_next_month);
					yearly_dates[j] = Date(next_day, next_month, 0);
					break;
				}
				else
				{
					p_next = p_next + 1;
					p_next_month[p_next - p_next_month - 1] = '\0';
					next_month = atoi(p_next_month);
					yearly_dates[j] = Date(next_day, next_month, 0);
				}
				j++;
				p_next_day = p_next;
			}
			j++;
			if (j < no_of_dates)
				return -1;
		}
		schedule = Schedule(schedule_type, YearlySchedule(no_of_dates, yearly_dates));
	}

	task_name = p_task_name;
	RecurrentTask recurrent_task = RecurrentTask(Task(task_name, task_status), schedule);
	recurrent_task_list.push_back(recurrent_task);
	return 0;
}

/*
 * unload the loaded tasks, from memory
 * into the disk db.
 */
int GlobalTaskList::unloadTasks(void)
{
	char input_file[100];
	char *dir = getenv("NEWTON_BASE_DIR");
	FILE *p_output_file = NULL;
	Date date;
	vector<Task> tasks;
	map<Date, DayTasks>::iterator iter;
	vector<RecurrentTask>::iterator recurrent_iter;
	char task_name_str[300];
	int i;

	if (dir == NULL)
	{
		return -1;
	}

	strcpy(input_file, dir);
	strcat(input_file, "/tasks.db");

	p_output_file = fopen(input_file, "w");
	if (NULL == p_output_file)
	{
		return -1;
	}

	/* write the recurrent tasks first */
	for (recurrent_iter = recurrent_task_list.begin(); recurrent_iter != recurrent_task_list.end(); recurrent_iter++)
	{
		fprintf(p_output_file, "%s\t%d\t%s\t%d", 
				"recurrent", 
				(*recurrent_iter).task.task_status, 
				(*recurrent_iter).task.task_name.c_str(),
				(*recurrent_iter).schedule.type);
		if ((*recurrent_iter).schedule.type == DAILY_SCHEDULE)
		{
			fprintf(p_output_file, "\t%d", 
					(*recurrent_iter).schedule.daily_schedule.type);
		}
		else if ((*recurrent_iter).schedule.type == WEEKLY_SCHEDULE)
		{
			int i;
			int no_of_days = (*recurrent_iter).schedule.weekly_schedule.no_of_days;
			fprintf(p_output_file, "\t%d", no_of_days);
			for (i = 0; i < no_of_days; i++)
			{
				fprintf(p_output_file, "\t%d", 
						(*recurrent_iter).schedule.weekly_schedule.days[i]);
			}
		}
		else if ((*recurrent_iter).schedule.type == MONTHLY_SCHEDULE)
		{
			int i;
			int no_of_days = (*recurrent_iter).schedule.monthly_schedule.no_of_days;
			fprintf(p_output_file, "\t%d", no_of_days);
			for (i = 0; i < no_of_days; i++)
			{
				fprintf(p_output_file, "\t%d", 
						(*recurrent_iter).schedule.monthly_schedule.days[i]);
			}
		}
		else if ((*recurrent_iter).schedule.type == YEARLY_SCHEDULE)
		{
			int i;
			int no_of_dates = (*recurrent_iter).schedule.yearly_schedule.no_of_dates;
			fprintf(p_output_file, "\t%d", no_of_dates);
			for (i = 0; i < no_of_dates; i++)
			{
				fprintf(p_output_file, "\t%d\t%d", 
						(*recurrent_iter).schedule.yearly_schedule.dates[i].date,
						(*recurrent_iter).schedule.yearly_schedule.dates[i].month);
			}
		}

		fprintf(p_output_file, "\n");
	}

	/* now write the day tasks */
	for (iter = task_list.begin(); iter != task_list.end(); iter++)
	{
		if ((*iter).second.isModified() == true)
		{
			fprintf(p_output_file, "%d\t%d\t%d\t%d\t%d", (*iter).second.date.date,
					(*iter).second.date.month, (*iter).second.date.year,
					(*iter).second.isholiday, (*iter).second.no_of_tasks);

			for (i = 0; i < (*iter).second.no_of_tasks; i++)
			{
				strcpy(task_name_str, (*iter).second.tasks[i].task_name.c_str());
				fprintf(p_output_file, "\t%s\t%d", 
						task_name_str,
						(*iter).second.tasks[i].task_status);
			}
			fprintf(p_output_file, "\n");
		}
	}
	fclose(p_output_file);

	return 0;
}

/*
 * add the daily task to the
 * global database.
 */
void GlobalTaskList::addTask(Date date, DayTasks day_tasks)
{
    task_list[date] = day_tasks;
}

/*
 * add the recurrent task to the
 * global database.
 */
void GlobalTaskList::addRecurrentTask(RecurrentTask recurrent_task)
{
	recurrent_task_list.push_back(recurrent_task);
}

/*
 * return the DayTasks for a given
 * date.
 */
DayTasks GlobalTaskList::getTasks(Date date)
{
    DayTasks temp_day_tasks = task_list[date];
    if (temp_day_tasks.isvalid == false)
    {
        deleteTask(date);
    }
    return temp_day_tasks;
}

/*
 * delete the DayTaks for the given
 * date from the global database.
 */
void GlobalTaskList::deleteTask(Date date)
{
    task_list.erase(task_list.find(date));
}

#if 0
void GlobalTaskList::deleteRecurrentTask(RecurrentTask recurrent_task)
{
	vector<RecurrentTask>::iterator recurrent_iter;
	for (recurrent_iter = recurrent_task_list.begin(); recurrent_iter != recurrent_task_list.end(); recurrent_iter++)
	{
		if (strcmp((*recurrent_iter).task.task_name.c_str(), recurrent_task.task.task_name.c_str()) == 0)
		{
			delete (*recurrent_iter);
		}
	}
}
#endif

/*
 * delete the recurrent task at the given
 * index from the global database.
 */
void GlobalTaskList::deleteRecurrentTask(int index)
{
	recurrent_task_list.erase(recurrent_task_list.begin() + index);
}

/*
 * replace the recurrent task at the given
 * index, with the recurrent task provided.
 */
void GlobalTaskList::replaceRecurrentTask(int index, RecurrentTask recurrent_task)
{
	recurrent_task_list[index] = recurrent_task;
}

/*
 * return the recurrent task at the
 * given index in the global database.
 */
RecurrentTask GlobalTaskList::getRecurrentTask(int index)
{
	return recurrent_task_list[index];
}

/*
 * return the total number of recurrent
 * tasks in the global database.
 */
int GlobalTaskList::getRecurrentTaskCount(void)
{
	return recurrent_task_list.size();
}
