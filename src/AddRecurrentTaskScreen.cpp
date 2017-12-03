/*****************************************************************************
* 
* This source file is the main file of the system, and the entry point.
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
   27-Aug-2005  Gaurav Jain      Initial Version    -
   03-Sep-2005  Gaurav Jain      Numerous Updates   0.1
*****************************************************************************/
#include "Common.h"

/*
 * Empty constructor - do nothing new.
 */
AddRecurrentTaskScreen::AddRecurrentTaskScreen() : Screen(SCREEN_TITLE,
        SCREEN_REVISION, SCREEN_COPYRIGHT)
{
}

/*
 * Display the AddRecurrentTask screen view.
 */
void AddRecurrentTaskScreen::display(void)
{
    char title_str[50] = "Recurrent Tasks";

    Screen::display();

    attron(CURR_HEAD_ATTR);
    mvprintw(ADD_TASK_BASE_ROW, 39 - (strlen(title_str)/2), title_str);
    attroff(CURR_HEAD_ATTR);
    attron(WARNING_ATTR);
    mvprintw(ADD_TASK_BASE_ROW + 5, 0, "------ Do not cross this line -----");
    attroff(WARNING_ATTR);
    attron(ENTER_STR_ATTR);
    mvprintw(ADD_TASK_BASE_ROW + 2, 0, "Enter Task: \n");
    attroff(ENTER_STR_ATTR);
}

/*
 * Interact for inputs from the user in the
 * AddRecurrentTask screen view.
 */
RecurrentTask AddRecurrentTaskScreen::interact(void)
{
    char task_str[300];
    RecurrentTask recurrentTask;
    Schedule schedule;
    int no_of_days;
    int daily_type, i, j;
    int week_days[MAX_DAYS_IN_WEEK];
    int weekly_days[MAX_DAYS_IN_WEEK];
    int monthly_days[MAX_DAYS_IN_MONTH];
    Date yearly_dates[MAX_DAYS_IN_YEAR];
    int date, month;
    int day;
    int choice, sub_choice;
    char line[500];
    char *p_next = NULL, *p_next_token = NULL;

    display();

    scanw(" %[^\n]", task_str);
    string task_name = string(task_str);

    attron(ENTER_STR_ATTR);
    mvprintw(ADD_TASK_BASE_ROW + 5, 0, "Schedule type:\n");
    attroff(ENTER_STR_ATTR);
    mvprintw(ADD_TASK_BASE_ROW + 6, 0, "1) Daily:\n");
    mvprintw(ADD_TASK_BASE_ROW + 7, 0, "2) Weekly:\n");
    mvprintw(ADD_TASK_BASE_ROW + 8, 0, "3) Monthly:\n");
    mvprintw(ADD_TASK_BASE_ROW + 9, 0, "4) Yearly:\n");
    choice = getch() - '0';
    switch (choice)
    {
	    case 1:
	    default:
		    /* Daily */
		    attron(ENTER_STR_ATTR);
		    mvprintw(ADD_TASK_BASE_ROW + 12, 0, "Select type of daily schedule:\n");
		    attroff(ENTER_STR_ATTR);
		    mvprintw(ADD_TASK_BASE_ROW + 13, 0, "1) All Days\n");
		    mvprintw(ADD_TASK_BASE_ROW + 14, 0, "2) All Holidays\n");
		    mvprintw(ADD_TASK_BASE_ROW + 15, 0, "3) All Working Days\n");
		    sub_choice = getch() - '0';
		    if (sub_choice == 2)
			    daily_type = DAILY_SCHEDULE_ONLY_HOLIDAYS;
		    else if (sub_choice == 3)
			    daily_type = DAILY_SCHEDULE_ONLY_WORKING_DAYS;
		    else
			    daily_type = DAILY_SCHEDULE_ALL_DAYS;
		    schedule = Schedule(DAILY_SCHEDULE, DailySchedule(daily_type));
		    break;
	    case 2:
		    /* Weekly */
		    for (i = 0; i < MAX_DAYS_IN_WEEK; i++)
			    week_days[i] = 0;
		    no_of_days = 0;
		    attron(ENTER_STR_ATTR);
		    mvprintw(ADD_TASK_BASE_ROW + 12, 0, "Select days of week (press 0 when done)\n");
		    attroff(ENTER_STR_ATTR);
		    while (1)
		    {
			    if (week_days[DAY_SUNDAY])
				    attron(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attron(NORMAL_CHOICE_ATTR);
			    mvprintw(ADD_TASK_BASE_ROW + 13, 0, "1) Sunday\n");
			    if (week_days[DAY_SUNDAY])
				    attroff(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attroff(NORMAL_CHOICE_ATTR);

			    if (week_days[DAY_MONDAY])
				    attron(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attron(NORMAL_CHOICE_ATTR);
			    mvprintw(ADD_TASK_BASE_ROW + 14, 0, "2) Monday\n");
			    if (week_days[DAY_MONDAY])
				    attroff(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attroff(NORMAL_CHOICE_ATTR);

			    if (week_days[DAY_TUESDAY])
				    attron(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attron(NORMAL_CHOICE_ATTR);
			    mvprintw(ADD_TASK_BASE_ROW + 15, 0, "3) Tuesday\n");
			    if (week_days[DAY_TUESDAY])
				    attroff(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attroff(NORMAL_CHOICE_ATTR);

			    if (week_days[DAY_WEDNESDAY])
				    attron(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attron(NORMAL_CHOICE_ATTR);
			    mvprintw(ADD_TASK_BASE_ROW + 16, 0, "4) Wednesday\n");
			    if (week_days[DAY_WEDNESDAY])
				    attroff(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attroff(NORMAL_CHOICE_ATTR);

			    if (week_days[DAY_THURSDAY])
				    attron(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attron(NORMAL_CHOICE_ATTR);
			    mvprintw(ADD_TASK_BASE_ROW + 17, 0, "5) Thursday\n");
			    if (week_days[DAY_THURSDAY])
				    attroff(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attroff(NORMAL_CHOICE_ATTR);

			    if (week_days[DAY_FRIDAY])
				    attron(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attron(NORMAL_CHOICE_ATTR);
			    mvprintw(ADD_TASK_BASE_ROW + 18, 0, "6) Friday\n");
			    if (week_days[DAY_FRIDAY])
				    attroff(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attroff(NORMAL_CHOICE_ATTR);

			    if (week_days[DAY_SATURDAY])
				    attron(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attron(NORMAL_CHOICE_ATTR);
			    mvprintw(ADD_TASK_BASE_ROW + 19, 0, "7) Saturday\n");
			    if (week_days[DAY_SATURDAY])
				    attroff(HIGHLIGHT_CHOICE_ATTR);
			    else
				    attroff(NORMAL_CHOICE_ATTR);

			    sub_choice = getch() - '0';
			    if (sub_choice >= 1 && sub_choice <= 7)
			    {
				    if (week_days[sub_choice - 1])
					    week_days[sub_choice - 1] = 0;
				    else
					    week_days[sub_choice - 1] = 1;
			    }
			    else
				    break;
		    }
		    j = 0;
		    for (i = 0; i < MAX_DAYS_IN_WEEK; i++)
		    {
			    if (week_days[i])
			    {
				    weekly_days[j] = i;
				    j++;
			    }
		    }
		    no_of_days = j;
		    schedule = Schedule(WEEKLY_SCHEDULE, WeeklySchedule(no_of_days, weekly_days));
		    break;
	    case 3:
		    /* Monthly */
		    no_of_days = 0;
		    attron(ENTER_STR_ATTR);
		    mvprintw(ADD_TASK_BASE_ROW + 12, 0, "Enter list of days of month, separated by commas (e.g., 1,8,9)\n");
		    attroff(ENTER_STR_ATTR);
		    scanw(" %[^\n]", line);
		    p_next = line;
		    j = 0;
		    while (1)
		    {
			    p_next_token = strchr(p_next, ',');
			    if (p_next_token == NULL)
			    {
				    day = my_atoi(p_next);
				    if (day != -1)
				    {
					    monthly_days[j] = day;
					    j++;
				    }
				    break;
			    }
			    p_next_token = p_next_token + 1;
			    p_next[p_next_token - p_next - 1] = '\0';
			    day = my_atoi(p_next);
			    if (day != -1)
			    {
				    monthly_days[j] = day;
				    j++;
			    }
			    p_next = p_next_token;

		    }
		    no_of_days = j;
		    schedule = Schedule(MONTHLY_SCHEDULE, MonthlySchedule(no_of_days, monthly_days));
		    break;
	    case 4:
		    /* Yearly */
		    no_of_days = 0;
		    attron(ENTER_STR_ATTR);
		    mvprintw(ADD_TASK_BASE_ROW + 12, 0, "Enter list of days of year, separated by commas (e.g., 08-10,09-04)\n");
		    attroff(ENTER_STR_ATTR);
		    scanw(" %[^\n]", line);
		    p_next = line;
		    j = 0;
		    while (1)
		    {
			    p_next_token = strchr(p_next, ',');
			    if (p_next_token == NULL)
			    {
				    sscanf(p_next, "%d-%d", &date, &month);
				    if (valid_date(date) && valid_month(month))
				    {
					    yearly_dates[j] = Date(date, month, 0);
					    j++;
				    }
				    break;
			    }
			    p_next_token = p_next_token + 1;
			    p_next[p_next_token - p_next - 1] = '\0';
			    sscanf(p_next, "%d-%d", &date, &month);
			    if (valid_date(date) && valid_month(month))
			    {
				    yearly_dates[j] = Date(date, month, 0);
				    j++;
			    }
			    p_next = p_next_token;

		    }
		    no_of_days = j;
		    schedule = Schedule(YEARLY_SCHEDULE, YearlySchedule(no_of_days, yearly_dates));
		    break;

    }
    
    return RecurrentTask(Task(task_name, TASK_STATUS_PENDING), schedule);
}
