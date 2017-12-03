/*****************************************************************************
* 
* This source file implements the MonthScreen (monthly view).
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
 * initialize month screen with the
 * attributes of the given date/month.
 * select the today's date.
 */
MonthScreen::MonthScreen(Date& date) : Screen(SCREEN_TITLE,
        SCREEN_REVISION, SCREEN_COPYRIGHT)
{
    char curr_month_str[20];
    int max_days = 0;
    bool started = false;
    int curr_date = 0;
    switch (date.month)
    {
        case 1:
                sprintf(curr_month_str, "January %d", date.year);
                break;
        case 2:
                sprintf(curr_month_str, "February %d", date.year);
                break;
        case 3:
                sprintf(curr_month_str, "March %d", date.year);
                break;
        case 4:
                sprintf(curr_month_str, "April %d", date.year);
                break;
        case 5:
                sprintf(curr_month_str, "May %d", date.year);
                break;
        case 6:
                sprintf(curr_month_str, "June %d", date.year);
                break;
        case 7:
                sprintf(curr_month_str, "July %d", date.year);
                break;
        case 8:
                sprintf(curr_month_str, "August %d", date.year);
                break;
        case 9:
                sprintf(curr_month_str, "September %d", date.year);
                break;
        case 10:
                sprintf(curr_month_str, "October %d", date.year);
                break;
        case 11:
                sprintf(curr_month_str, "November %d", date.year);
                break;
        case 12:
                sprintf(curr_month_str, "December %d", date.year);
                break;
    }
    curr_month = string(curr_month_str);
    Date first_day = Date(1, date.month, date.year);
    max_days = max_days_in_month(date.month, date.year);

    for (int row = 0; row < MONTH_MAX_ROWS; row++)
    {
        for (int col = 0; col < MONTH_MAX_COLS; col++)
        {
            if ((started == false) && (row == 0) && 
                    (col == first_day.day_of_week))
            {
                /* First day of month */
                curr_date = 1;
                day_box_matrix[row][col] = DayBox(DayTasks(curr_date, date.month,
                            date.year), row, col);
                day_box_matrix[row][col].first = true;
                day_box_matrix[row][col].isvalid = true;
                day_box_matrix[row][col].date = curr_date;
                if (curr_date == date.date)
                {
                    sel_row = row;
                    sel_col = col;
                }
                curr_date++;
                started = true;
            }
            else if (started == true)
            {
                day_box_matrix[row][col] = DayBox(DayTasks(curr_date, date.month,
                            date.year), row, col);
                day_box_matrix[row][col].isvalid = true;
                day_box_matrix[row][col].date = curr_date;
                if (curr_date == max_days)
                {
                    /* Last day of month */
                    day_box_matrix[row][col].last = true;
                    started = false;
                }
                if (curr_date == date.date)
                {
                    sel_row = row;
                    sel_col = col;
                }
                curr_date++;
            }
            else
            {
                /* Invalid box */
                day_box_matrix[row][col].isvalid = false;
            }
        }
    }
}

/*
 * display the month screen to the user.
 */
void MonthScreen::display(void)
{
    char task_char = ' ';

    time_t time_now = time(NULL);
    struct tm *ptm = localtime(&time_now);
    int this_year = ptm->tm_year+1900;
    int this_month = ptm->tm_mon+1;
    int this_day = ptm->tm_mday;
    bool today_flag = false;
    int today_row = -1, today_col = -1;
    char today_str[10];

    int lastrow, lastcol;
    getmaxyx(stdscr, lastrow, lastcol);

    Date today_date = Date(this_day, this_month, this_year);

    /* Display the top screen information */
    Screen::display();

    char curr_month_str[20];
    strcpy(curr_month_str, curr_month.c_str());

    attron(SHORTCUT_STR_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW, 4, "<< [");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("P");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("]revious Month");
    attroff(SHORTCUT_STR_ATTR);
    attron(CURR_HEAD_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW, 39 - (strlen(curr_month_str)/2), curr_month_str);
    attroff(CURR_HEAD_ATTR);
    attron(SHORTCUT_STR_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW, 60, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("N");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("]ext Month >>");
    attroff(SHORTCUT_STR_ATTR);
    attron(GRID_HEAD_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW + 1, 4,
            "_/=======\\_/=======\\_/=======\\_/=======\\_/=======\\_/=======\\_/=======\\_");
    attroff(GRID_HEAD_ATTR);
    attron(GRID_ATTR);
    mvprintw(MONTH_BOX_BASE_ROW + 2, 4, "|   ");
    attroff(GRID_ATTR);
    attron(HOLIDAY_TITLE_ATTR);
    printw("Sun   ");
    attroff(HOLIDAY_TITLE_ATTR);
    attron(GRID_ATTR);
    printw("|   ");
    attroff(GRID_ATTR);
    attron(NON_HOLIDAY_TITLE_ATTR);
    printw("Mon   ");
    attroff(NON_HOLIDAY_TITLE_ATTR);
    attron(GRID_ATTR);
    printw("|   ");
    attroff(GRID_ATTR);
    attron(NON_HOLIDAY_TITLE_ATTR);
    printw("Tue   ");
    attroff(NON_HOLIDAY_TITLE_ATTR);
    attron(GRID_ATTR);
    printw("|   ");
    attroff(GRID_ATTR);
    attron(NON_HOLIDAY_TITLE_ATTR);
    printw("Wed   ");
    attroff(NON_HOLIDAY_TITLE_ATTR);
    attron(GRID_ATTR);
    printw("|   ");
    attroff(GRID_ATTR);
    attron(NON_HOLIDAY_TITLE_ATTR);
    printw("Thu   ");
    attroff(NON_HOLIDAY_TITLE_ATTR);
    attron(GRID_ATTR);
    printw("|   ");
    attroff(GRID_ATTR);
    attron(NON_HOLIDAY_TITLE_ATTR);
    printw("Fri   ");
    attroff(NON_HOLIDAY_TITLE_ATTR);
    attron(GRID_ATTR);
    printw("|   ");
    attroff(GRID_ATTR);
    attron(HOLIDAY_TITLE_ATTR);
    printw("Sat   ");
    attroff(HOLIDAY_TITLE_ATTR);
    attron(GRID_ATTR);
    printw("|");
    mvprintw(MONTH_BOX_BASE_ROW + 3, 4,
   "|_________|_________|_________|_________|_________|_________|_________|");
    attroff(GRID_ATTR);

    for (int row = 0; row < MONTH_MAX_ROWS; row++)
    {
        for (int col = 0; col < MONTH_MAX_COLS; col++)
        {
            if (day_box_matrix[row][col].isvalid == true)
            {
                today_flag = false;
                strcpy(today_str, "     ");
                if (day_box_matrix[row][col].day_tasks.date == today_date)
                {
                    today_row = row;
                    today_col = col;
                    strcpy(today_str, "TODAY");
                    today_flag = true;
                }

                attron(GRID_ATTR);
                mvprintw(day_box_matrix[row][col].row_min,
                        day_box_matrix[row][col].col_min+1, "_________");
                mvprintw(day_box_matrix[row][col].row_min+1,
                        day_box_matrix[row][col].col_min, "|");
                attroff(GRID_ATTR);
                if (day_box_matrix[row][col].day_tasks.isholiday == true)
                {
                    attron(HOLIDAY_ATTR);
                }
                else
                {
                    attron(NON_HOLIDAY_ATTR);
                }
                if (today_flag == true)
                {
                    attron(A_BOLD);
                }
                printw("  %s  ", today_str);
                if (today_flag == true)
                {
                    attroff(A_BOLD);
                }
                if (day_box_matrix[row][col].day_tasks.isholiday == true)
                {
                    attroff(HOLIDAY_ATTR);
                }
                else
                {
                    attroff(NON_HOLIDAY_ATTR);
                }
                attron(GRID_ATTR);
                printw("|");
                mvprintw(day_box_matrix[row][col].row_min+2,
                        day_box_matrix[row][col].col_min, "|");
                attroff(GRID_ATTR);
                if (day_box_matrix[row][col].day_tasks.isholiday == true)
                {
                    attron(HOLIDAY_ATTR);
                }
                else
                {
                    attron(NON_HOLIDAY_ATTR);
                }
                if (today_flag == true)
                {
                    attron(A_BOLD);
                }
                if (day_box_matrix[row][col].day_tasks.no_of_tasks > 0)
                {
                    task_char = '§';
                }
                else
                {
                    task_char = ' ';
                }
                printw("   %2d  %c ", day_box_matrix[row][col].date, task_char);
                if (today_flag == true)
                {
                    attroff(A_BOLD);
                }
                if (day_box_matrix[row][col].day_tasks.isholiday == true)
                {
                    attroff(HOLIDAY_ATTR);
                }
                else
                {
                    attroff(NON_HOLIDAY_ATTR);
                }
                attron(GRID_ATTR);
                printw("|");
                mvprintw(day_box_matrix[row][col].row_min+3,
                        day_box_matrix[row][col].col_min, "|");
                printw("_________");
                printw("|");
                attroff(GRID_ATTR);
            }
        }
    }
    
    /* Print selected box */
    if (day_box_matrix[sel_row][sel_col].day_tasks.isholiday == true)
    {
        attron(HOLIDAY_ATTR);
    }
    else
    {
        attron(NON_HOLIDAY_ATTR);
    }
    attron(SELECTED_ATTR);
    if ((today_row == sel_row) && (today_col == sel_col))
    {
        strcpy(today_str, "TODAY");
        attron(A_BOLD);
    }
    else
    {
        strcpy(today_str, "     ");
    }
    mvprintw(day_box_matrix[sel_row][sel_col].row_min+1,
            day_box_matrix[sel_row][sel_col].col_min+1, "  %s  ", today_str);
    if (day_box_matrix[sel_row][sel_col].day_tasks.no_of_tasks > 0)
    {
        task_char = '§';
    }
    else
    {
        task_char = ' ';
    }
    mvprintw(day_box_matrix[sel_row][sel_col].row_min+2,
            day_box_matrix[sel_row][sel_col].col_min+1, "   %2d  %c ", 
            day_box_matrix[sel_row][sel_col].date, task_char);
    mvprintw(day_box_matrix[sel_row][sel_col].row_min+3,
            day_box_matrix[sel_row][sel_col].col_min+1, "         ");
    if ((today_row == sel_row) && (today_col == sel_col))
    {
        attroff(A_BOLD);
    }
    attroff(SELECTED_ATTR);
    if (day_box_matrix[sel_row][sel_col].day_tasks.isholiday == true)
    {
        attroff(HOLIDAY_ATTR);
    }
    else
    {
        attroff(NON_HOLIDAY_ATTR);
    }

    /* Display the input options at bottom of screen */
    attron(SHORTCUT_STR_ATTR);
    mvprintw(lastrow - 3, 5, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("N");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Next Month\n");
    mvprintw(lastrow - 2, 5, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("P");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Preview Month\n");
    mvprintw(lastrow - 1, 5, "[");
    attroff(SHORTCUT_STR_ATTR);
    attron(SHORTCUT_KEY_ATTR);
    printw("o");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    if (day_box_matrix[sel_row][sel_col].day_tasks.isholiday == false)
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
    printw("w");
    attroff(SHORTCUT_KEY_ATTR);
    attron(SHORTCUT_STR_ATTR);
    printw("] Weekly View\n");
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
 * interact with the user to read
 * user inputs, and respond to the
 * inputs.
 */
int MonthScreen::interact(Date& date)
{
    int choice;
    display();
    char file_name[200];
    char cmd_str[300];

    choice = wgetch(main_win);
    switch (choice)
    {
        case 'w':
            return RETURN_WEEK_VIEW;
        case 'r':
            return RETURN_RECURRENT_VIEW;
        case 'd':
        case 10:
            return RETURN_DAY_VIEW;
        case 'q':
            /* Return 0, means, STOP! */
            return RETURN_QUIT;
        case 'j':
        case KEY_DOWN:
            /* Down */
            if ((sel_row + 1 < MONTH_MAX_ROWS) && 
                    (day_box_matrix[sel_row + 1][sel_col].isvalid == true))
            {
                /* Move to new date */
                date = Date(day_box_matrix[sel_row + 1][sel_col].date,
                        date.month, date.year);
            }
            break;
        case 'k':
        case KEY_UP:
            /* Up */
            if ((sel_row > 0) && 
                    (day_box_matrix[sel_row - 1][sel_col].isvalid == true))
            {
                /* Move to new date */
                date = Date(day_box_matrix[sel_row - 1][sel_col].date,
                        date.month, date.year);
            }
            break;
        case 'l':
        case KEY_RIGHT:
            /* Right */
            if ((sel_col + 1 < MONTH_MAX_COLS) && 
                    (day_box_matrix[sel_row][sel_col + 1].isvalid == true))
            {
                /* Move to new date */
                date = Date(day_box_matrix[sel_row][sel_col + 1].date,
                        date.month, date.year);
            }
            else
            {
                /* last day of month, move to next month! */
                ++date;
            }
            break;
        case 'h':
        case KEY_LEFT:
            /* Left */
            if ((sel_col > 0) && 
                    (day_box_matrix[sel_row][sel_col - 1].isvalid == true))
            {
                /* Move to new date */
                date = Date(day_box_matrix[sel_row][sel_col - 1].date,
                        date.month, date.year);
            }
            else
            {
                /* first day of month, Move to previous month! */
                --date;
            }
            break;
        case 'N':
            /* Next Month */
            if (date.month < 12)
            {
                date = Date(date.date, date.month + 1, date.year);
            }
            else
            {
                date = Date(date.date, 1, date.year + 1);
            }
            break;
        case 'P':
            /* Previous Month */
            if (date.month > 1)
            {
                date = Date(date.date, date.month - 1, date.year);
            }
            else
            {
                date = Date(date.date, 12, date.year - 1);
            }
            break;
        case 'o':
            /* Mark/Unmark as holiday */
            if (day_box_matrix[sel_row][sel_col].day_tasks.isholiday == false)
            {
                day_box_matrix[sel_row][sel_col].day_tasks.isholiday = true;
            }
            else
            {
                day_box_matrix[sel_row][sel_col].day_tasks.isholiday = false;
            }
            if (day_box_matrix[sel_row][sel_col].day_tasks.isModified() == true)
            {
                day_box_matrix[sel_row][sel_col].day_tasks.isvalid = true;
                g_task_list.addTask(date, 
                        day_box_matrix[sel_row][sel_col].day_tasks);
            }
            else
            {
                day_box_matrix[sel_row][sel_col].day_tasks.isvalid = false;
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
		    break;
	    }
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
    return RETURN_MONTH_VIEW;
}
