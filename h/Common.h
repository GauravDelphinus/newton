/*****************************************************************************
* 
* This header file defines all the common externs, macros, constants, etc.
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

   Date         Updater          Comment
   21-Aug-2005  Gaurav Jain      Initial Version
   04-Sep-2005  Gaurav Jain      Numerous Updates
*****************************************************************************/
#define MONTH_MAX_ROWS 6
#define MONTH_MAX_COLS 7

#define WEEK_MAX_ROWS 7

/* week days */
enum days
{
    DAY_SUNDAY = 0,
    DAY_MONDAY,
    DAY_TUESDAY,
    DAY_WEDNESDAY,
    DAY_THURSDAY,
    DAY_FRIDAY,
    DAY_SATURDAY
};

/* days max limits */
#define MAX_DAYS_IN_WEEK	7
#define MAX_DAYS_IN_MONTH	31	
#define MAX_DAYS_IN_YEAR	366

/* types of daily schedules */
#define DAILY_SCHEDULE_ALL_DAYS	1
#define DAILY_SCHEDULE_ONLY_HOLIDAYS	2
#define DAILY_SCHEDULE_ONLY_WORKING_DAYS	3

/* types of schedules */
#define DAILY_SCHEDULE	1
#define WEEKLY_SCHEDULE	2
#define MONTHLY_SCHEDULE	3
#define YEARLY_SCHEDULE	4

/* month box attributes */
#define MONTH_BOX_BASE_ROW 1
#define MONTH_BOX_BASE_COL 4
#define MONTH_BOX_ROW_HEIGHT 3
#define MONTH_BOX_COL_WIDTH 10

/* day box attributes */
#define DAY_BOX_BASE_ROW 1
#define DAY_BOX_BASE_COL 4

/* week box attributes */
#define WEEK_BOX_BASE_ROW 1
#define WEEK_BOX_BASE_COL 4

/* other attributes */
#define ADD_TASK_BASE_ROW 1

/* view ids */
#define RETURN_MONTH_VIEW 1
#define RETURN_WEEK_VIEW 2
#define RETURN_DAY_VIEW 3
#define RETURN_RECURRENT_VIEW 4
#define RETURN_QUIT 0

/* task status types */
#define TASK_STATUS_PENDING 1
#define TASK_STATUS_COMPLETED 2
#define TASK_STATUS_CANCELLED 3

/* other task attributes */
#define WEEK_BOX_MAX_TASK_SUMMARY_LEN 30
#define TASK_ONE_LINE_MAX_LEN 53
#define DAY_MAX_TASKS 6

/* screen attributes */
#define SCREEN_TITLE "Isaac Newton Organizer"
#define SCREEN_REVISION "Revision 0.2"
#define SCREEN_COPYRIGHT "Copyright (c) 2005 - 2006 Gaurav Jain"
#define SCREEN_HOMEPAGE "http://software.gauravjain.in/newton"

/* types of screens */
#define WELCOME_SCREEN	1
#define ABOUT_SCREEN	2
#define HELP_SCREEN	3
#define GOODBYE_SCREEN	4
#define WARRANTY_SCREEN	5

/* Colors */
#define HOLIDAY_TITLE_ATTR (COLOR_PAIR(1) | A_BOLD)
#define HOLIDAY_ATTR (COLOR_PAIR(1))
#define NON_HOLIDAY_TITLE_ATTR (COLOR_PAIR(3) | A_BOLD)
#define NON_HOLIDAY_ATTR (COLOR_PAIR(3))
#define GRID_ATTR COLOR_PAIR(7)
#define GRID_HEAD_ATTR COLOR_PAIR(7)
#define SELECTED_ATTR A_REVERSE 
#define SHORTCUT_STR_ATTR (COLOR_PAIR(6))
#define SHORTCUT_KEY_ATTR (COLOR_PAIR(6) | A_BOLD)
#define CURR_HEAD_ATTR (COLOR_PAIR(2) | A_BOLD)
#define PROGRAM_NAME_ATTR (COLOR_PAIR(5))
#define COPYRIGHT_ATTR (COLOR_PAIR(4))
#define TASK_COUNT_ATTR (COLOR_PAIR(7))
#define TASK_SUMMARY_ATTR (COLOR_PAIR(2))
#define WARNING_ATTR (COLOR_PAIR(1))
#define ENTER_STR_ATTR (COLOR_PAIR(6))
#define TASK_NUM_ATTR (COLOR_PAIR(3))
#define TASK_NAME_ATTR (COLOR_PAIR(2))
#define TASK_STATUS_PENDING_ATTR (COLOR_PAIR(3))
#define TASK_STATUS_COMPLETED_ATTR (COLOR_PAIR(4))
#define TASK_STATUS_CANCELLED_ATTR (COLOR_PAIR(1))
#define HIGHLIGHT_CHOICE_ATTR (COLOR_PAIR(6) | A_BOLD)
#define NORMAL_CHOICE_ATTR (COLOR_PAIR(6))
#define TASK_SCHEDULE_HEAD_ATTR (COLOR_PAIR(3))
#define TASK_SCHEDULE_ATTR (COLOR_PAIR(2))

/* Command lines */
#define MAX_COMMAND_LINE_LENGTH (4096 * 2)

/* common includes */
using namespace std;
#include <string>
#include <curses.h>
#include <time.h>
#include <vector>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include "Date.h"
#include "DayTasks.h"
#include "DayBox.h"
#include "Screen.h"
#include "MonthScreen.h"
#include "WeekScreen.h"
#include "DayScreen.h"
#include "RecurrentTasksScreen.h"
#include "AddTaskScreen.h"
#include "AddRecurrentTaskScreen.h"
#include "EditTaskScreen.h"
#include "SplashScreen.h"
#include "GlobalTaskList.h"
#include "CLIParser.h"

/* Prototypes of global functions */
int max_days_in_month(int month, int year);
int cumulative_days(int month, int year);
void construct_schedule_display_string(char schedule_str[], Schedule schedule);
void get_weekday_string(int index, char day_str[]);
void get_yearday_string(Date date, char day_str[]);
void get_monthday_string(int day, char day_str[]);
int valid_date(int date);
int valid_month(int month);
int valid_year(int year);
int my_atoi(char *str);
Date get_today(void);

/* Global variables */
extern GlobalTaskList g_task_list;
extern WINDOW *main_win;
