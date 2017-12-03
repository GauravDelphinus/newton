/*****************************************************************************
* 
* This source file implements common utility routines
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

   Date         Updater          Comment           Revision
   28-Aug-2005  Gaurav Jain      Initial Version   -
   04-Sep-2005  Gaurav Jain      Numerous Updates  0.1
*****************************************************************************/
#include "Common.h"
#include "errno.h"

/*
 * Return the max days in a month for the
 * given year, taking into account the leap
 * year property.
 */
int max_days_in_month(int month, int year)
{
    switch (month)
    {
        case 1: 
            return 31; 
            break;
        case 2: 
            if (!(year % 4) && ((year % 100) || !(year % 400)))
                return 29;
            else
                return 28; 
            break;
        case 3: 
            return 31; 
            break;
        case 4: 
            return 30; 
            break;
        case 5: 
            return 31; 
            break;
        case 6: 
            return 30; 
            break;
        case 7: 
            return 31; 
            break;
        case 8: 
            return 31; 
            break;
        case 9: 
            return 30; 
            break;
        case 10: 
            return 31; 
            break;
        case 11: 
            return 30; 
            break;
        case 12: 
            return 31; 
            break;
    }
    return 0;
}

/*
 * Find the number of cumulative days
 * from the beginning of the year to the given
 * month.
 */
int cumulative_days(int month, int year)
{
    int leap_year = 0;
    int cumulative_days = 0;
    if (!(year % 4) && ((year % 100) || !(year % 400)) && (month > 1))
    {
        leap_year = 1;
    }
    cumulative_days = leap_year;

    switch (month)
    {
        case 1:
            cumulative_days += 31;
            break;
        case 2:
            cumulative_days += 31+28;
            break;
        case 3:
            cumulative_days += 31+28+31;
            break;
        case 4:
            cumulative_days += 31+28+31+30;
            break;
        case 5:
            cumulative_days += 31+28+31+30+31;
            break;
        case 6:
            cumulative_days += 31+28+31+30+31+30;
            break;
        case 7:
            cumulative_days += 31+28+31+30+31+30+31;
            break;
        case 8:
            cumulative_days += 31+28+31+30+31+30+31+31;
            break;
        case 9:
            cumulative_days += 31+28+31+30+31+30+31+31+30;
            break;
        case 10:
            cumulative_days += 31+28+31+30+31+30+31+31+30+31;
            break;
        case 11:
            cumulative_days += 31+28+31+30+31+30+31+31+30+31+30;
            break;
        case 12:
            cumulative_days += 31+28+31+30+31+30+31+31+30+31+30+31;
            break;
    }
    return cumulative_days;
}

/*
 * Construct a display string for the
 * given schedule
 */
void construct_schedule_display_string(char schedule_str[], Schedule schedule)
{
	char day_str[100];
	int no_of_days;
	int i;
	switch (schedule.type)
	{
		case DAILY_SCHEDULE:
			if (schedule.daily_schedule.type == DAILY_SCHEDULE_ALL_DAYS)
			{
				strcpy(schedule_str, "Every day, including all holidays.");
			}
			else if (schedule.daily_schedule.type == DAILY_SCHEDULE_ONLY_HOLIDAYS)
			{
				strcpy(schedule_str, "Every holiday.");
			}
			else if (schedule.daily_schedule.type == DAILY_SCHEDULE_ONLY_WORKING_DAYS)
			{
				strcpy(schedule_str, "Every working day.");
			}
			break;
		case WEEKLY_SCHEDULE:
			no_of_days = schedule.weekly_schedule.no_of_days;
			if (no_of_days == 0)
			{
				strcpy(schedule_str, "No Days Selected!");
			}		
			else
			{
				strcpy(schedule_str, "Every week on the following days: ");
				get_weekday_string(schedule.weekly_schedule.days[0], day_str);
				strcat(schedule_str, day_str);
				for (i = 1; i < no_of_days - 1; i++)
				{
					strcat(schedule_str, ", ");
					get_weekday_string(schedule.weekly_schedule.days[i], day_str);
					strcat(schedule_str, day_str);
				}
				if (no_of_days > 1)
				{
					strcat(schedule_str, " and ");
					get_weekday_string(schedule.weekly_schedule.days[no_of_days - 1], day_str);
					strcat(schedule_str, day_str);
				}
				strcat(schedule_str, ".");
			}
			break;
		case MONTHLY_SCHEDULE:
			no_of_days = schedule.monthly_schedule.no_of_days;
			if (no_of_days == 0)
			{
				strcpy(schedule_str, "No Days Selected!");
			}		
			else
			{
				strcpy(schedule_str, "Every month on the following days: ");
				get_monthday_string(schedule.monthly_schedule.days[0], day_str);
				strcat(schedule_str, day_str);
				for (i = 1; i < no_of_days - 1; i++)
				{
					strcat(schedule_str, ", ");
					get_monthday_string(schedule.monthly_schedule.days[i], day_str);
					strcat(schedule_str, day_str);
				}
				if (no_of_days > 1)
				{
					strcat(schedule_str, " and ");
					get_monthday_string(schedule.monthly_schedule.days[no_of_days - 1], day_str);
					strcat(schedule_str, day_str);
				}
				strcat(schedule_str, ".");
			}
			break;
		case YEARLY_SCHEDULE:
			no_of_days = schedule.yearly_schedule.no_of_dates;
			if (no_of_days == 0)
			{
				strcpy(schedule_str, "No Days Selected!");
			}		
			else
			{
				strcpy(schedule_str, "Every year on the following dates: ");
				get_yearday_string(schedule.yearly_schedule.dates[0], day_str);
				strcat(schedule_str, day_str);
				for (i = 1; i < no_of_days - 1; i++)
				{
					strcat(schedule_str, ", ");
					get_yearday_string(schedule.yearly_schedule.dates[i], day_str);
					strcat(schedule_str, day_str);
				}
				if (no_of_days > 1)
				{
					strcat(schedule_str, " and ");
					get_yearday_string(schedule.yearly_schedule.dates[no_of_days - 1], day_str);
					strcat(schedule_str, day_str);
				}
				strcat(schedule_str, ".");
			}
			break;
	}
}

/*
 * Return the string version of the weekday,
 * given its ID.
 */
void get_weekday_string(int index, char day_str[])
{
	switch (index)
	{
		case DAY_SUNDAY:
			strcpy(day_str, "Sunday");
			break;
		case DAY_MONDAY:
			strcpy(day_str, "Monday");
			break;
		case DAY_TUESDAY:
			strcpy(day_str, "Tuesday");
			break;
		case DAY_WEDNESDAY:
			strcpy(day_str, "Wednesday");
			break;
		case DAY_THURSDAY:
			strcpy(day_str, "Thursday");
			break;
		case DAY_FRIDAY:
			strcpy(day_str, "Friday");
			break;
		case DAY_SATURDAY:
			strcpy(day_str, "Saturday");
			break;
	}
}

/*
 * Return the long format for the given
 * date of the year.
 */
void get_yearday_string(Date date, char day_str[])
{
	char month_str[50];
	switch (date.month)
	{
		case 1:
			strcpy(month_str, "January");
			break;
		case 2:
			strcpy(month_str, "February");
			break;
		case 3:
			strcpy(month_str, "March");
			break;
		case 4:
			strcpy(month_str, "April");
			break;
		case 5:
			strcpy(month_str, "May");
			break;
		case 6:
			strcpy(month_str, "June");
			break;
		case 7:
			strcpy(month_str, "July");
			break;
		case 8:
			strcpy(month_str, "August");
			break;
		case 9:
			strcpy(month_str, "September");
			break;
		case 10:
			strcpy(month_str, "October");
			break;
		case 11:
			strcpy(month_str, "November");
			break;
		case 12:
			strcpy(month_str, "December");
			break;
	}

	get_monthday_string(date.date, day_str);
	strcat(day_str, " ");
	strcat(day_str, month_str);
}

/*
 * Return the date of the month by
 * appending the "th" suffix according
 * to the number.
 */
void get_monthday_string(int day, char day_str[])
{
	sprintf(day_str, "%d", day);

	if ((day % 10) == 1)
	{
		strcat(day_str, "st");
	}
	else if ((day % 10) == 2)
	{
		strcat(day_str, "nd");
	}
	else if ((day % 10) == 3)
	{
		strcat(day_str, "rd");
	}
	else
	{
		strcat(day_str, "th");
	}
}

/*
 * Return 1 in case the given date is
 * valid, otherwise 0
 */
int valid_date(int date)
{
	return (date >= 1 && date <= 31);
}

/*
 * Returns 1 if the given month value is
 * valid, 0 otherwise
 */
int valid_month(int month)
{
	return (month >= 1 && month <= 12);
}

/*
 * Returns 1 if the given year value is
 * valid, 0 otherwise
 */
int valid_year(int year)
{
	return (year >= 1900 && year <= 9999);
}

/*
 * my version of atoi(), which checks for
 * errors, and returns -1 incase an error
 * occured. (note: "-1" as an input string is
 * an invalid value for this function).
 */
int my_atoi(char *str)
{
	int retval = strtol(str, (char **)NULL, 10);
	if (errno != 0)
		return -1;
	else
		return retval;
}

/*
 * return a new Date object representing
 * today's date.
 */
Date get_today(void)
{
	time_t time_now = time(NULL);
	struct tm *ptm = localtime(&time_now);
	int this_year = ptm->tm_year+1900;
	int this_month = ptm->tm_mon+1;
	int this_day = ptm->tm_mday;

	Date today = Date(this_day, this_month, this_year);
	return today;
}
