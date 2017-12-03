/*****************************************************************************
* 
* This source file implements the DayScreen (daily view).
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
 * Creata a new DayScreen object, initializing
 * it with the given date, and selecting the
 * task number given by default.
 */
DayScreen::DayScreen(Date& date, int& sel_task) : Screen(SCREEN_TITLE,
        SCREEN_REVISION, SCREEN_COPYRIGHT)
{
    char curr_day_str[50];
    char day_of_week_str[30];
    strcpy(day_of_week_str, date.day_of_week_str.c_str());
    
    sprintf(curr_day_str, "%s - %.2d/%.2d/%d", day_of_week_str, date.date,
            date.month, date.year);
    curr_day = string(curr_day_str);

    day_tasks = DayTasks(date.date, date.month, date.year);
    all_tasks = day_tasks.generateAllTasks();
}

/*
 * display the DayScreen to the user
 */
void DayScreen::display(int &first_task, int& sel_task)
{
    char first_line_str[100]="";
    char second_line_str[100]="";
    char complete_task_str[200]="";
    char task_status_str[30]="";
    int task_status_attr = 0;
    int i = 0;

    int lastrow, lastcol;
    getmaxyx(stdscr, lastrow, lastcol);
    int max_visible_tasks = (lastrow - 5 - 1)/3;

    time_t time_now = time(NULL);
    struct tm *ptm = localtime(&time_now);
    int this_year = ptm->tm_year+1900;
    int this_month = ptm->tm_mon+1;
    int this_day = ptm->tm_mday;

    Date today_date = Date(this_day, this_month, this_year);

    /* Display the top screen information */
    Screen::display();

    char curr_day_str[50];
    strcpy(curr_day_str, curr_day.c_str());

    if (today_date == day_tasks.date)
    {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(MONTH_BOX_BASE_ROW, 39 - ((5 + strlen(curr_day_str))/2), "TODAY\n");
        attroff(COLOR_PAIR(3) | A_BOLD);
    }
    else
    {
        mvprintw(MONTH_BOX_BASE_ROW + 1, 36, "\n");
    }

    attron(SHORTCUT_STR_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW, 4, "<< [");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("P");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("]revious Day");
    attroff(SHORTCUT_STR_ATTR);
    attron(CURR_HEAD_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW, (39 - ((5 + strlen(curr_day_str))/2)) + 6, curr_day_str);
    attroff(CURR_HEAD_ATTR);
    attron(SHORTCUT_STR_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW, 61, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("N");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("]ext Day >>");
    attroff(SHORTCUT_STR_ATTR);
    if (all_tasks.no_of_tasks > 0)
    {
        if (sel_task < all_tasks.no_of_tasks)
        {
		if (sel_task >= first_task)
			sel_row = sel_task - first_task;
		else
			sel_row = 0;
        }
        else
        {
            sel_row = 0;
        }
    }
    else
    {
        sel_row = -1;
    }
    for (int row = 0; row < max_visible_tasks; row++)
    {
        first_line_str[0] = '\0';
        second_line_str[0] = '\0';
        if (row < all_tasks.no_of_tasks)
        {
            switch (all_tasks.tasks[row + first_task].task_status)
            {
                case TASK_STATUS_PENDING:
                    strcpy(task_status_str, "Pending");
                    task_status_attr = TASK_STATUS_PENDING_ATTR;
                    break;
                case TASK_STATUS_COMPLETED:
                    strcpy(task_status_str, "Completed");
                    task_status_attr = TASK_STATUS_COMPLETED_ATTR;
                    break;
                case TASK_STATUS_CANCELLED:
                    strcpy(task_status_str, "Cancelled");
                    task_status_attr = TASK_STATUS_CANCELLED_ATTR;
                    break;
            }
            attron(TASK_NUM_ATTR);
            if (sel_row == row)
            {
                attron(SELECTED_ATTR);
            }
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 2,
                    DAY_BOX_BASE_COL+1, "%3d", row + first_task + 1);
            if (sel_row == row)
            {
                attroff(SELECTED_ATTR);
            }
            attroff(TASK_NUM_ATTR);
            /* Construct the first and second line of each task */
            strcpy(complete_task_str, all_tasks.tasks[row + first_task].task_name.c_str());
            if (strlen(complete_task_str) > TASK_ONE_LINE_MAX_LEN)
            {
                for (i = TASK_ONE_LINE_MAX_LEN - 1; i > 0; i--)
                {
                    if (complete_task_str[i] == ' ')
                    {
                        break;
                    }
                }
                complete_task_str[i] = '\0';
                strcpy(second_line_str, complete_task_str + i + 1);
            }
            strcpy(first_line_str, complete_task_str);

	    int len = strlen(first_line_str);
	    for (i = 0; i < TASK_ONE_LINE_MAX_LEN - len; i++)
		    strcat(first_line_str, " ");

	    len = strlen(second_line_str);
	    for (i = 0; i < TASK_ONE_LINE_MAX_LEN - len; i++)
		    strcat(second_line_str, " ");

	    first_line_str[TASK_ONE_LINE_MAX_LEN - 1] = '\0';
	    second_line_str[TASK_ONE_LINE_MAX_LEN - 1] = '\0';

            attron(TASK_NAME_ATTR);
            mvprintw(DAY_BOX_BASE_ROW +  row * 3 + 2,
                    DAY_BOX_BASE_COL + 6, first_line_str);
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 3,
                    DAY_BOX_BASE_COL + 6, second_line_str);
            attroff(TASK_NAME_ATTR);
            attron(task_status_attr);
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 2,
                    DAY_BOX_BASE_COL + 6 + TASK_ONE_LINE_MAX_LEN, 
                    "%s\n", task_status_str);
            attroff(task_status_attr);

            /* Draw box */
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 1, DAY_BOX_BASE_COL,
                    "|---|----------------------------------------------------|-----------|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 2, DAY_BOX_BASE_COL, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 2, DAY_BOX_BASE_COL + 4, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 2, DAY_BOX_BASE_COL + 4 +
                    TASK_ONE_LINE_MAX_LEN, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 2, DAY_BOX_BASE_COL + 4 +
                    TASK_ONE_LINE_MAX_LEN + 12, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 3, DAY_BOX_BASE_COL, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 3, DAY_BOX_BASE_COL + 4, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 3, DAY_BOX_BASE_COL + 4 +
                    TASK_ONE_LINE_MAX_LEN, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 3, DAY_BOX_BASE_COL + 4 +
                    TASK_ONE_LINE_MAX_LEN + 12, "|");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 4, DAY_BOX_BASE_COL,
                    "|---|----------------------------------------------------|-----------|");
        }
        else
        {
            if (row == 0)
            {
                mvprintw(DAY_BOX_BASE_ROW +  row * 3 + 1,
                        0, "\n");
            }
            mvprintw(DAY_BOX_BASE_ROW +  row * 3 + 2,
                    0, "\n");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 3,
                    0, "\n");
            mvprintw(DAY_BOX_BASE_ROW + row * 3 + 4,
                    0, "\n");
        }
    }
    if (all_tasks.no_of_tasks == 0)
    {
        mvprintw(DAY_BOX_BASE_ROW +  2,
                DAY_BOX_BASE_COL + 3, "No Tasks!");
    }

    /* Display the input options at bottom of screen */
    attron(SHORTCUT_STR_ATTR);
    mvprintw(lastrow - 3, 4, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("a");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Add Tasks");
    mvprintw(lastrow - 2, 4, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("e");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Edit Tasks");
    mvprintw(lastrow - 1, 4, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("x");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Delete Tasks");
    mvprintw(lastrow - 3, 22, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("c");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Mark as Completed");
    mvprintw(lastrow - 2, 22, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("p");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Mark as Pending");
    mvprintw(lastrow - 1, 22, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("l");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Mark as Cancelled");
    mvprintw(lastrow - 3, 45, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("w");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Weekly View");
    mvprintw(lastrow - 2, 45, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("m");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Monthly View");
    mvprintw(lastrow - 1, 45, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("r");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Recurrent Tasks\n");
    mvprintw(lastrow - 3, 65, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("A");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] About\n");
    mvprintw(lastrow - 2, 65, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("H");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Help\n");
    mvprintw(lastrow - 1, 65, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("q");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Quit\n");
    attroff(SHORTCUT_STR_ATTR);
}

/*
 * Interact with the user in the DayScreen,
 * and handle user inputs.
 */
int DayScreen::interact(Date& date, int& first_task, int& sel_task, int& clr_scr)
{
    int choice;
    display(first_task, sel_task);

    int lastrow, lastcol;
    getmaxyx(stdscr, lastrow, lastcol);
    int max_visible_tasks = (lastrow - 5 - 1)/3;
    char file_name[200];
    char cmd_str[300];

    choice = wgetch(main_win);
    switch (choice)
    {
        case 'm':
            /* Monthly view */
            return RETURN_MONTH_VIEW;
        case 'w':
            /* Weekly view */
            return RETURN_WEEK_VIEW;
        case 'r':
            /* Recurrent Tasks view */
            return RETURN_RECURRENT_VIEW;
        case 'q':
            /* Return 0, means, go back to weekly screen */
            return RETURN_QUIT;
        case 'j':
        case KEY_DOWN:
            /* Down */
            if (all_tasks.no_of_tasks > 0)
            {
		if (sel_task + 1 == all_tasks.no_of_tasks)
		{
			/* go back up */
			sel_row = 0;
			first_task = 0;
			sel_task = 0;
		}
		else if (sel_row + 1 == max_visible_tasks)
		{
			/* scroll down */
			sel_task++;
			first_task++;
		}
		else
		{
			/* simply move one down */
			sel_row++;
			sel_task++;
		}
            }
            break;
        case 'k':
        case KEY_UP:
            /* Up */
            if (all_tasks.no_of_tasks > 0)
            {
		if (sel_task == 0)
		{
			/* go back down */
			sel_task = all_tasks.no_of_tasks - 1;
			if (all_tasks.no_of_tasks > max_visible_tasks)
			{
				sel_row = max_visible_tasks - 1;
				first_task = sel_task - max_visible_tasks + 1;
			}
			else
			{
				sel_row = all_tasks.no_of_tasks - 1;
				first_task = 0;
			}
		}
		else if (sel_task == first_task)
		{
			/* scroll up */
			sel_task--;
			first_task--;
		}
		else
		{
			/* simply move up */
			sel_row--;
			sel_task--;
		}
            }
            break;
        case 'N':
            /* Next Day */
            ++date;
            break;
        case 'P':
            /* Previous Day */
            --date;
            break;
        case 'a':
            /* Add tasks */
            //if (day_tasks.no_of_tasks < max_visible_tasks)
            {
                clear();
                AddTaskScreen addTaskScreen = AddTaskScreen(date);
                day_tasks.tasks.push_back(Task(addTaskScreen.interact(),
                            TASK_STATUS_PENDING));
                day_tasks.no_of_tasks++;
                day_tasks.isvalid = true;
                g_task_list.addTask(date, day_tasks);
		all_tasks = day_tasks.generateAllTasks();
                clr_scr = 1;

                if (sel_row < 0)
                {
                    sel_row = 0;
                    sel_task = 0;
	 	    first_task = 0;
                }
            }
            break;
        case 'e':
            /* Edit tasks */
            if ((day_tasks.no_of_tasks > 0) && (sel_row + first_task < day_tasks.no_of_tasks))
            {
                clear();
                EditTaskScreen editTaskScreen = EditTaskScreen(date);
                day_tasks.tasks[sel_row + first_task] = Task(editTaskScreen.interact(),
                        day_tasks.tasks[sel_row + first_task].task_status);
                g_task_list.addTask(date, day_tasks);
		all_tasks = day_tasks.generateAllTasks();
                clr_scr = 1;
            }
            break;
        case 'x':
            /* Delete tasks */
            if ((day_tasks.no_of_tasks > 0) && (sel_row + first_task < day_tasks.no_of_tasks))
            {
		int orig_no_of_tasks = day_tasks.no_of_tasks;
                day_tasks.tasks.erase(day_tasks.tasks.begin() + sel_row + first_task);
                day_tasks.no_of_tasks--;
                if (day_tasks.isModified() == false)
                {
                    day_tasks.isvalid = false;
                    g_task_list.deleteTask(date);
                }
                else
                {
                    g_task_list.addTask(date, day_tasks);
                }

                if (orig_no_of_tasks <= max_visible_tasks)
                {
			if (sel_task + 1 == orig_no_of_tasks)
			{
				sel_row--;
				sel_task--;
			}
                }
		else if (orig_no_of_tasks - first_task > max_visible_tasks)
		{
			; //do nothing
		}
		else if (first_task > 0)
		{
			first_task--;
			sel_task--;
		}
		all_tasks = day_tasks.generateAllTasks();
                clr_scr = 1;
            }
            break;
        case 'c':
            /* Mark as completed */
            if (all_tasks.no_of_tasks > 0)
            {
		    if (sel_row + first_task < day_tasks.no_of_tasks)
		    {
			    day_tasks.tasks[sel_row + first_task].task_status = TASK_STATUS_COMPLETED;
			    g_task_list.addTask(date, day_tasks);
		    }
		    else
		    {
			    all_tasks.tasks[sel_row + first_task].task_status = TASK_STATUS_COMPLETED;
			    day_tasks.tasks.push_back(all_tasks.tasks[sel_row + first_task]);
			    day_tasks.no_of_tasks++;
			    day_tasks.isvalid = true;
			    g_task_list.addTask(date, day_tasks);
			    all_tasks = day_tasks.generateAllTasks();
			    clr_scr = 1;
		    }
            }
            break;
        case 'p':
            /* Mark as pending */
            if (all_tasks.no_of_tasks > 0)
            {
		    if (sel_row + first_task < day_tasks.no_of_tasks)
		    {
			    day_tasks.tasks[sel_row + first_task].task_status = TASK_STATUS_PENDING;
			    g_task_list.addTask(date, day_tasks);
		    }
		    else
		    {
			    all_tasks.tasks[sel_row + first_task].task_status = TASK_STATUS_PENDING;
			    day_tasks.tasks.push_back(all_tasks.tasks[sel_row + first_task]);
			    day_tasks.no_of_tasks++;
			    day_tasks.isvalid = true;
			    g_task_list.addTask(date, day_tasks);
			    all_tasks = day_tasks.generateAllTasks();
			    clr_scr = 1;
		    }
            }
            break;
        case 'l':
            /* Mark as cancelled */
            if (all_tasks.no_of_tasks > 0)
            {
		    if (sel_row + first_task < day_tasks.no_of_tasks)
		    {
			    day_tasks.tasks[sel_row + first_task].task_status = TASK_STATUS_CANCELLED;
			    g_task_list.addTask(date, day_tasks);
		    }
		    else
		    {
			    all_tasks.tasks[sel_row + first_task].task_status = TASK_STATUS_CANCELLED;
			    day_tasks.tasks.push_back(all_tasks.tasks[sel_row + first_task]);
			    day_tasks.no_of_tasks++;
			    day_tasks.isvalid = true;
			    g_task_list.addTask(date, day_tasks);
			    all_tasks = day_tasks.generateAllTasks();
			    clr_scr = 1;
		    }
            }
            break;
	case 'A':
	    {
		    SplashScreen aboutScreen = SplashScreen(ABOUT_SCREEN);
		    aboutScreen.display();
		    strcpy(file_name, getenv("NEWTON_BASE_DIR"));
		    sprintf(cmd_str, "vi %s/readme.txt 2> %s/.tmp", file_name,
				    file_name);
		    system(cmd_str);
	    }
	    break;
	case 'H':
	    {
		    SplashScreen helpScreen = SplashScreen(HELP_SCREEN);
		    helpScreen.display();
		    strcpy(file_name, getenv("NEWTON_BASE_DIR"));
		    sprintf(cmd_str, "vi %s/help.txt 2> %s/.tmp", file_name,
				    file_name);
		    system(cmd_str);
	    }
	    break;
    }

    /* Return 1, means, CONTINUE! */
    return RETURN_DAY_VIEW;
}

