/*****************************************************************************
* 
* This source file implements the WeekScreen (weekly view).
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
 * create a week scree, initialize with
 * default values.
 */
WeekScreen::WeekScreen(Date& date) : Screen(SCREEN_TITLE,
        SCREEN_REVISION, SCREEN_COPYRIGHT)
{
    char curr_week_str[50];
    Date first_day = Date(date);
    Date last_day = Date(date);
    int i;

    for (i = 0; i < date.day_of_week; i++)
    {
        --first_day;
    }
    for (i = 0; i < (6 - date.day_of_week); i++)
    {
        ++last_day;
    }


    sprintf(curr_week_str, "Week of %.2d/%.2d/%d - %.2d/%.2d/%d", first_day.date,
            first_day.month, first_day.year, last_day.date, last_day.month,
            last_day.year);
    curr_week = string(curr_week_str);

    Date curr_day = first_day;

    for (int row = 0; row < WEEK_MAX_ROWS; row++)
    {
	    DayTasks day_tasks = DayTasks(curr_day.date, curr_day.month,
			    curr_day.year);

        day_box_array[row] = DayBox(day_tasks.generateAllTasks(), row, 3);
        if (row == 0)
        {
            day_box_array[row].first = true;
        }
        else if (row == 6)
        {
            day_box_array[row].last = true;
        }
        day_box_array[row].isvalid = true;
        day_box_array[row].date = curr_day.date;
        day_box_array[row].month = curr_day.month;
        day_box_array[row].year = curr_day.year;
        day_box_array[row].day_str = curr_day.day_of_week_str;
        day_box_array[row].row_min = WEEK_BOX_BASE_ROW + 1 + row * 2;
        if (curr_day == date)
        {
            sel_row = row;
        }
        ++curr_day;
    }
}

/*
 * display the week screen to the user.
 */
void WeekScreen::display(void)
{
    char day_str_short[10]="";
    bool more_flag = false;
    unsigned int copy_len = 0, remaining_len = 0, task_no_str_len = 0;
    char task_summary_str[100]="";
    int i;
    char task_no_str[10];

    int lastrow, lastcol;
    getmaxyx(stdscr, lastrow, lastcol);

    time_t time_now = time(NULL);
    struct tm *ptm = localtime(&time_now);
    int this_year = ptm->tm_year+1900;
    int this_month = ptm->tm_mon+1;
    int this_day = ptm->tm_mday;

    Date today_date = Date(this_day, this_month, this_year);

    /* Display the top screen information */
    Screen::display();

    char curr_week_str[50];
    strcpy(curr_week_str, curr_week.c_str());

    attron(SHORTCUT_STR_ATTR);
    mvprintw(WEEK_BOX_BASE_ROW, 4, "<< [");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("P");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("]revious Week");
    attroff(SHORTCUT_STR_ATTR);
    attron(CURR_HEAD_ATTR);
    mvprintw(WEEK_BOX_BASE_ROW, 39 - (strlen(curr_week_str)/2), curr_week_str);
    attroff(CURR_HEAD_ATTR);
    attron(SHORTCUT_STR_ATTR);
    mvprintw(WEEK_BOX_BASE_ROW, 60, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("N");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("]ext Week >>");
    attroff(SHORTCUT_STR_ATTR);
    for (int row = 0; row < WEEK_MAX_ROWS; row++)
    {
        if (day_box_array[row].isvalid == true)
        {
            strncpy(day_str_short, day_box_array[row].day_str.c_str(), 3);
            /* Print day and date */
            attron(GRID_ATTR);
            mvprintw(day_box_array[row].row_min,
                    WEEK_BOX_BASE_COL, "|----------------");
            mvprintw(day_box_array[row].row_min+1,
                    WEEK_BOX_BASE_COL, "|");
            attroff(GRID_ATTR);
            if (today_date == day_box_array[row].day_tasks.date)
            {
                attron(COLOR_PAIR(3) | A_BOLD);
                mvprintw(day_box_array[row].row_min + 1, 0, "[T]");
                attroff(COLOR_PAIR(3) | A_BOLD);
                attron(A_BOLD);
            }
            else
            {
                mvprintw(day_box_array[row].row_min + 1, 0, "   ");
            }
            if (day_box_array[row].day_tasks.isholiday == true)
            {
                attron(HOLIDAY_ATTR);
            }
            else
            {
                attron(NON_HOLIDAY_ATTR);
            }
            if (row == sel_row)
            {
                attron(SELECTED_ATTR);
            }
            mvprintw(day_box_array[row].row_min+1, WEEK_BOX_BASE_COL + 1, 
                    " %3s %.2d/%.2d/%d ",
                    day_str_short, day_box_array[row].date,
                    day_box_array[row].month, day_box_array[row].year);
            if (today_date == day_box_array[row].day_tasks.date)
            {
                attroff(A_BOLD);
            }
            if (row == sel_row)
            {
                attroff(SELECTED_ATTR);
            }
            if (day_box_array[row].day_tasks.isholiday == true)
            {
                attron(HOLIDAY_ATTR);
            }
            else
            {
                attron(NON_HOLIDAY_ATTR);
            }
            attron(GRID_ATTR);
            mvprintw(day_box_array[row].row_min+2,
                    WEEK_BOX_BASE_COL, "|----------------",
                    day_box_array[row].date);
            attroff(GRID_ATTR);

            /* Print task column */
            attron(TASK_COUNT_ATTR);
            mvprintw(day_box_array[row].row_min + 1,
                    WEEK_BOX_BASE_COL + 19, "%d Tasks",
                    day_box_array[row].day_tasks.no_of_tasks);
            attroff(TASK_COUNT_ATTR);

            /* Print capture summary of tasks */
            if (day_box_array[row].day_tasks.no_of_tasks > 0)
            {
                more_flag = false;
                task_summary_str[0] = '\0';
                char task_str[300] = "";

                remaining_len = WEEK_BOX_MAX_TASK_SUMMARY_LEN;
                for (i = 0; i < day_box_array[row].day_tasks.no_of_tasks; i++)
                {
                    strcpy(task_str,
                            day_box_array[row].day_tasks.tasks[i].task_name.c_str());
                    sprintf(task_no_str, " [%d] ", i+1);
                    task_no_str_len = strlen(task_no_str);
                    strcat(task_summary_str, task_no_str);
                    remaining_len -= task_no_str_len;

                    if (strlen(task_str) < remaining_len)
                    {
                        copy_len = strlen(task_str) ;
                    }
                    else
                    {
                        copy_len = remaining_len;
                        more_flag = true;
                    }
                    strncat(task_summary_str, task_str, copy_len);
                    remaining_len -= copy_len;

                    if (remaining_len < 5)
                    {
                        break;
                    }

                }
                if (i < day_box_array[row].day_tasks.no_of_tasks)
                {
                    more_flag = true;
                }

                if (more_flag == true)
                {
                    strcat(task_summary_str, " (more...)");
                }
                attron(TASK_SUMMARY_ATTR);
                mvprintw(day_box_array[row].row_min+1, WEEK_BOX_BASE_COL +
                        28, task_summary_str);
                attroff(TASK_SUMMARY_ATTR);
            }
            else
            {
                /* Print blank for quick refresh */
                mvprintw(day_box_array[row].row_min+1, WEEK_BOX_BASE_COL +
                        28, "\n");
            }
            /* Print block */
            attron(GRID_ATTR);
            mvprintw(day_box_array[row].row_min, WEEK_BOX_BASE_COL,
                    "|----------------|---------|-----------------------------------------|");
            mvprintw(day_box_array[row].row_min + 1, WEEK_BOX_BASE_COL, "|");
            mvprintw(day_box_array[row].row_min + 1, WEEK_BOX_BASE_COL + 17, "|");
            mvprintw(day_box_array[row].row_min + 1, WEEK_BOX_BASE_COL + 27, "|");
            mvprintw(day_box_array[row].row_min + 1, WEEK_BOX_BASE_COL+69, "|");
            mvprintw(day_box_array[row].row_min + 2, WEEK_BOX_BASE_COL,
                    "|----------------|---------|-----------------------------------------|");
            attroff(GRID_ATTR);
        }
    }

    attron(SHORTCUT_STR_ATTR);
    mvprintw(lastrow - 3, 5, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("N");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Next Week\n");
    mvprintw(lastrow - 2, 5, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("P");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Preview Week\n");
    mvprintw(lastrow - 1, 5, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("o");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    if (day_box_array[sel_row].day_tasks.isholiday == false)
    {
        printw("] Mark as Holiday\n");
    }
    else
    {
        printw("] Unmark as Holiday\n");
    }
    mvprintw(lastrow - 3, 35, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("d");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Daily View\n");
    mvprintw(lastrow - 2, 35, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("m");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Monthly View\n");
    mvprintw(lastrow - 1, 35, "[");
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
 * interact with the user, and 
 * respond to user inputs.
 */
int WeekScreen::interact(Date& date)
{
    int choice;
    int i;
    char file_name[200];
    char cmd_str[300];
    display();

    choice = wgetch(main_win);
    switch (choice)
    {
        case 'd':
        case 10:
            return RETURN_DAY_VIEW;
        case 'r':
            return RETURN_RECURRENT_VIEW;
        case 'q':
            return RETURN_QUIT;
        case 'm':
            /* Return 0, means, go back to monthly screen */
            return RETURN_MONTH_VIEW;
        case 'j':
        case KEY_DOWN:
            /* Down */
            ++date;
            break;
        case 'k':
        case KEY_UP:
            /* Up */
            --date;
            break;
        case 'N':
            /* Next Week */
            for (i = 0; i < 7; i++)
            {
                ++date;
            }
            break;
        case 'P':
            /* Previous Week */
            for (i = 0; i < 7; i++)
            {
                --date;
            }
            break;
        case 'o':
            /* Mark/Unmark as holiday */
            if (day_box_array[sel_row].day_tasks.isholiday == false)
            {
                day_box_array[sel_row].day_tasks.isholiday = true;
            }
            else
            {
                day_box_array[sel_row].day_tasks.isholiday = false;
            }
            if (day_box_array[sel_row].day_tasks.isModified() == true)
            {
                day_box_array[sel_row].day_tasks.isvalid = true;
                g_task_list.addTask(date, 
                        day_box_array[sel_row].day_tasks);
            }
            else
            {
                day_box_array[sel_row].day_tasks.isvalid = false;
                g_task_list.deleteTask(date);
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
    return RETURN_WEEK_VIEW;
}
