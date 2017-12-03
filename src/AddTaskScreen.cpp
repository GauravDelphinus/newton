/*****************************************************************************
* 
* This source file implements the AddTasks screen.
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
 * Create a new Screen for adding tasks.
 */
AddTaskScreen::AddTaskScreen(Date& date) : Screen(SCREEN_TITLE,
        SCREEN_REVISION, SCREEN_COPYRIGHT)
{
    char day_str[50];
    char day_of_week_str[30];
    strcpy(day_of_week_str, date.day_of_week_str.c_str());
    sprintf(day_str, "%s - %.2d/%.2d/%d", day_of_week_str, date.date,
            date.month, date.year);
    day_string = string(day_str);
}

/* 
 * Display the AddTask screen view.
 */
void AddTaskScreen::display(void)
{
    char curr_day_str[50];

    Screen::display();

    strcpy(curr_day_str, day_string.c_str());
    attron(CURR_HEAD_ATTR);
    mvprintw(ADD_TASK_BASE_ROW, 39 - (strlen(curr_day_str)/2), curr_day_str);
    attroff(CURR_HEAD_ATTR);
    attron(WARNING_ATTR);
    mvprintw(ADD_TASK_BASE_ROW + 5, 0, "------ Do not cross this line -----");
    attroff(WARNING_ATTR);
    attron(ENTER_STR_ATTR);
    mvprintw(ADD_TASK_BASE_ROW + 2, 0, "Enter Task: \n");
    attroff(ENTER_STR_ATTR);
}

/*
 * Interact with the user in the Add
 * Task Screen view.
 */
string AddTaskScreen::interact(void)
{
    char task_str[300];
    display();

    scanw(" %[^\n]", task_str);
    string task_string = string(task_str);

    return task_string;
}
