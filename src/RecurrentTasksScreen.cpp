/*****************************************************************************
* 
* This source file implements the RecurrentTasks Screen (recurrent view).
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
   03-Sep-2005  Gaurav Jain      Initial Version    -
   04-Sep-2005  Gaurav Jain      Numerous Updates   0.1
*****************************************************************************/
#include "Common.h"

/*
 * create an empty recurrent task screen.
 */
RecurrentTasksScreen::RecurrentTasksScreen(int& sel_task) : Screen(SCREEN_TITLE, SCREEN_REVISION, SCREEN_COPYRIGHT)
{
}

/*
 * display the recurrent task screen
 * to the user.
 */
void RecurrentTasksScreen::display(int &first_task, int& sel_task)
{
    char first_line_str[100]="";
    char second_line_str[100]="";
    char complete_task_str[200]="";
    char task_status_str[30]="";
    char complete_schedule_str[300];
    char first_schedule_str[100]="";
    char second_schedule_str[100]="";
    char schedule_head_str[100]="";
    int task_status_attr = 0;
    int i = 0;

    int lastrow, lastcol;
    getmaxyx(stdscr, lastrow, lastcol);
    int max_visible_tasks = (lastrow - 5 - 1)/6;
    int no_of_tasks = g_task_list.getRecurrentTaskCount();

    /* Display the top screen information */
    Screen::display();

    char title_str[50];
    strcpy(title_str, "Recurrent Tasks");

    attron(CURR_HEAD_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW, (39 - ((5 + strlen(title_str))/2)) + 6, title_str);
    attroff(CURR_HEAD_ATTR);
    if (no_of_tasks > 0)
    {
        if (sel_task < no_of_tasks)
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
    if (no_of_tasks == 0)
    {
        mvprintw(DAY_BOX_BASE_ROW +  2,
                DAY_BOX_BASE_COL + 3, "No Tasks!");
    }
    else
    {
	    for (int row = 0; row < max_visible_tasks; row++)
	    {
		    first_line_str[0] = '\0';
		    second_line_str[0] = '\0';
		    if (row < no_of_tasks)
		    {
			    RecurrentTask recurrent_task = g_task_list.getRecurrentTask(row + first_task);
			    switch (recurrent_task.task.task_status)
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
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 2,
					    DAY_BOX_BASE_COL+1, "%3d", row + first_task + 1);
			    if (sel_row == row)
			    {
				    attroff(SELECTED_ATTR);
			    }
			    attroff(TASK_NUM_ATTR);

			    /* Construct the first and second line of each task */
			    strcpy(complete_task_str, recurrent_task.task.task_name.c_str());
			    second_line_str[0] = '\0';
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

			    /* construct the schedule heading, and first and second line */
			    construct_schedule_display_string(complete_schedule_str, recurrent_task.schedule);
			    second_schedule_str[0] = '\0';
			    if (strlen(complete_schedule_str) > TASK_ONE_LINE_MAX_LEN)
			    {
				    for (i = TASK_ONE_LINE_MAX_LEN - 1; i > 0; i--)
				    {
					    if (complete_schedule_str[i] == ' ')
					    {
						    break;
					    }
				    }
				    complete_schedule_str[i] = '\0';
				    strcpy(second_schedule_str, complete_schedule_str + i + 1);
			    }
			    strcpy(first_schedule_str, complete_schedule_str);

			    len = strlen(first_schedule_str);
			    for (i = 0; i < TASK_ONE_LINE_MAX_LEN - len; i++)
				    strcat(first_schedule_str, " ");

			    len = strlen(second_schedule_str);
			    for (i = 0; i < TASK_ONE_LINE_MAX_LEN - len; i++)
				    strcat(second_schedule_str, " ");

			    first_schedule_str[TASK_ONE_LINE_MAX_LEN - 1] = '\0';
			    second_schedule_str[TASK_ONE_LINE_MAX_LEN - 1] = '\0';

			    strcpy(schedule_head_str, "Schedule:");
			    len = strlen(schedule_head_str);
			    for (i = 0; i < TASK_ONE_LINE_MAX_LEN - len; i++)
				    strcat(schedule_head_str, " ");


			    /* draw the task info */
			    attron(TASK_NAME_ATTR);
			    mvprintw(DAY_BOX_BASE_ROW +  row * 6 + 2,
					    DAY_BOX_BASE_COL + 6, first_line_str);
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 3,
					    DAY_BOX_BASE_COL + 6, second_line_str);
			    attroff(TASK_NAME_ATTR);
			    attron(task_status_attr);
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 2,
					    DAY_BOX_BASE_COL + 6 + TASK_ONE_LINE_MAX_LEN, 
					    "%s\n", task_status_str);
			    attroff(task_status_attr);

			    /* draw the schedule info */
			    attron(TASK_SCHEDULE_HEAD_ATTR);
			    mvprintw(DAY_BOX_BASE_ROW +  row * 6 + 4,
					    DAY_BOX_BASE_COL + 6, schedule_head_str);
			    attroff(TASK_SCHEDULE_HEAD_ATTR);
			    attron(TASK_SCHEDULE_ATTR);
			    mvprintw(DAY_BOX_BASE_ROW +  row * 6 + 5,
					    DAY_BOX_BASE_COL + 6, first_schedule_str);
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 6,
					    DAY_BOX_BASE_COL + 6, second_schedule_str);
			    attroff(TASK_SCHEDULE_ATTR);

			    /* Draw box */
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 1, DAY_BOX_BASE_COL,
					    "|---|----------------------------------------------------|-----------|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 2, DAY_BOX_BASE_COL, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 2, DAY_BOX_BASE_COL + 4, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 2, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 2, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN + 12, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 3, DAY_BOX_BASE_COL, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 3, DAY_BOX_BASE_COL + 4, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 3, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 3, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN + 12, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 4, DAY_BOX_BASE_COL, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 4, DAY_BOX_BASE_COL + 4, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 4, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 4, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN + 12, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 5, DAY_BOX_BASE_COL, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 5, DAY_BOX_BASE_COL + 4, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 5, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 5, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN + 12, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 6, DAY_BOX_BASE_COL, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 6, DAY_BOX_BASE_COL + 4, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 6, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 6, DAY_BOX_BASE_COL + 4 +
					    TASK_ONE_LINE_MAX_LEN + 12, "|");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 7, DAY_BOX_BASE_COL,
					    "|---|----------------------------------------------------|-----------|");
		    }
		    else
		    {
			    if (row == 0)
			    {
				    mvprintw(DAY_BOX_BASE_ROW +  row * 6 + 1,
						    0, "\n");
			    }
			    mvprintw(DAY_BOX_BASE_ROW +  row * 6 + 2,
					    0, "\n");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 3,
					    0, "\n");
			    mvprintw(DAY_BOX_BASE_ROW + row * 6 + 4,
					    0, "\n");
		    }
	    }
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
    printw("d");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Daily View");
    mvprintw(lastrow - 2, 45, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("w");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Weekly View");
    mvprintw(lastrow - 1, 45, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("m");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Monthly View\n");
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
 * interact with the user, and respond
 * to user inputs.
 */
int RecurrentTasksScreen::interact(int& first_task, int& sel_task, int& clr_scr)
{
    int choice;
    display(first_task, sel_task);

    int lastrow, lastcol;
    getmaxyx(stdscr, lastrow, lastcol);
    int max_visible_tasks = (lastrow - 5 - 1)/6;
    int no_of_tasks = g_task_list.getRecurrentTaskCount();
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
        case 'd':
            /* Daily view */
            return RETURN_DAY_VIEW;
        case 'q':
            /* Return 0, means, go back to weekly screen */
            return RETURN_QUIT;
        case 'j':
        case KEY_DOWN:
            /* Down */
            if (no_of_tasks > 0)
            {
		if (sel_task + 1 == no_of_tasks)
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
            if (no_of_tasks > 0)
            {
		if (sel_task == 0)
		{
			/* go back down */
			sel_task = no_of_tasks - 1;
			if (no_of_tasks > max_visible_tasks)
			{
				sel_row = max_visible_tasks - 1;
				first_task = sel_task - max_visible_tasks + 1;
			}
			else
			{
				sel_row = no_of_tasks - 1;
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
        case 'a':
            /* Add tasks */
            //if (no_of_tasks < max_visible_tasks)
            {
                clear();
                AddRecurrentTaskScreen addRecurrentTaskScreen = AddRecurrentTaskScreen();
                g_task_list.addRecurrentTask(addRecurrentTaskScreen.interact());
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
            if (no_of_tasks > 0)
            {
                clear();
                AddRecurrentTaskScreen editRecurrentTaskScreen = AddRecurrentTaskScreen();
                g_task_list.replaceRecurrentTask(sel_row + first_task, editRecurrentTaskScreen.interact());
                clr_scr = 1;
            }
            break;
        case 'x':
            /* Delete tasks */
            if (no_of_tasks > 0)
            {
		int orig_no_of_tasks = no_of_tasks;
		g_task_list.deleteRecurrentTask(sel_row + first_task);

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
                clr_scr = 1;
            }
            break;
        case 'c':
            /* Mark as completed */
            if (no_of_tasks > 0)
            {
		RecurrentTask recurrent_task = g_task_list.getRecurrentTask(sel_row + first_task);
		recurrent_task.task.task_status = TASK_STATUS_COMPLETED;
                g_task_list.replaceRecurrentTask(sel_row + first_task, recurrent_task);
            }
            break;
        case 'p':
            /* Mark as pending */
            if (no_of_tasks > 0)
            {
		RecurrentTask recurrent_task = g_task_list.getRecurrentTask(sel_row + first_task);
		recurrent_task.task.task_status = TASK_STATUS_PENDING;
                g_task_list.replaceRecurrentTask(sel_row + first_task, recurrent_task);
            }
            break;
        case 'l':
            /* Mark as cancelled */
            if (no_of_tasks > 0)
            {
		RecurrentTask recurrent_task = g_task_list.getRecurrentTask(sel_row + first_task);
		recurrent_task.task.task_status = TASK_STATUS_CANCELLED;
                g_task_list.replaceRecurrentTask(sel_row + first_task, recurrent_task);
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
    return RETURN_RECURRENT_VIEW;
}

