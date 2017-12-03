/*****************************************************************************
* 
* This source file is the main file of the system.
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

GlobalTaskList g_task_list;
WINDOW *main_win = NULL;

/*****************************************************************************
* 
* Main routine for the software (entry point)
*
*****************************************************************************/
int main(int argc, char *argv[])
{
    int i;
    if (argc > 1)
    {
		CLIParser cliParser = CLIParser(argc - 1, &argv[1]);
		if (cliParser.parse())
		{
			if (cliParser.execute())
				cliParser.successMessage();
			else
				cliParser.errorMessage();
		}
		else
			cliParser.printUsage();
		return 0;
    }

    /* Initialize curses screen */
    main_win = initscr();
    keypad(main_win, TRUE);
    start_color();

    /* Initialize color pairs */
    for (i = 1; i < COLORS; i++)
    {
        init_pair(i, i, COLOR_BLACK);
    }

    SplashScreen splashScreen = SplashScreen(WELCOME_SCREEN);
    splashScreen.display();

    /* Read tasks from disk */
    if (-1 == g_task_list.loadTasks())
    {
        endwin();
        exit(1);
    }

    /* Get current date */
    time_t time_now = time(NULL);
    struct tm *ptm = localtime(&time_now);
    int this_year = ptm->tm_year+1900;
    int this_month = ptm->tm_mon+1;
    int this_day = ptm->tm_mday;
    int sel_task = 0;
    int sel_recurrent_task = 0;
    int first_task = 0;
    int first_recurrent_task = 0;

    Date date = Date(this_day, this_month, this_year);
    Date old_date;
    int choice = RETURN_MONTH_VIEW;
    int new_choice;
    bool clear_scr_flag = false;
    int clr_scr = 0;

    MonthScreen monthScreen = MonthScreen(date);;
    WeekScreen weekScreen = WeekScreen(date);;
    DayScreen dayScreen = DayScreen(date, sel_task);;
    RecurrentTasksScreen recurrentTasksScreen = RecurrentTasksScreen(sel_recurrent_task);;

    while (1)
    {
        old_date = date;
        if (choice == RETURN_MONTH_VIEW)
        {
            monthScreen = MonthScreen(date);
            new_choice = monthScreen.interact(date);
            if (date.month != old_date.month)
            {
                clear_scr_flag = true;
            }
            sel_task = 0;
	    first_task = 0;
        }
        else if (choice == RETURN_WEEK_VIEW)
        {
            weekScreen = WeekScreen(date);
            new_choice = weekScreen.interact(date);
            sel_task = 0;
	    first_task = 0;
        }
        else if (choice == RETURN_DAY_VIEW)
        {
            dayScreen = DayScreen(date, sel_task);
            new_choice = dayScreen.interact(date, first_task, sel_task, clr_scr);
            if ((date.date != old_date.date) || (clr_scr == 1))
            {
                clear_scr_flag = true;
                clr_scr = 0;
                sel_task = 0;
		first_task = 0;
            }
        }
        else if (choice == RETURN_RECURRENT_VIEW)
        {
            recurrentTasksScreen = RecurrentTasksScreen(sel_recurrent_task);
            new_choice = recurrentTasksScreen.interact(first_recurrent_task, sel_recurrent_task, clr_scr);
            if (clr_scr == 1)
            {
                clear_scr_flag = true;
                clr_scr = 0;
                sel_recurrent_task = 0;
		first_recurrent_task = 0;
            }
        }
        else if (choice == RETURN_QUIT)
        {
            break;
        }
        if (choice != new_choice)
        {
            clear_scr_flag = true;
            choice = new_choice;
        }
        if (clear_scr_flag == true)
        {
            clear();
            clear_scr_flag = false;
        }
    }

    /* Write tasks to disk */
    if (-1 == g_task_list.unloadTasks())
    {
        endwin();
        exit(1);
    }
    splashScreen = SplashScreen(GOODBYE_SCREEN);
    splashScreen.display();

    //getch();
    endwin();
    return 0;
}
