/*****************************************************************************
* 
* This source file implements the Date class.
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
   28-Aug-2005  Gaurav Jain      Initial Version    -
   04-Sep-2005  Gaurav Jain      Numerous Updates   0.1
*****************************************************************************/
#include "Common.h"

/*
 * construct a new date, for the current
 * local time
 */
Date::Date()
{
    time_t time_now = time(NULL);
    struct tm *ptm = localtime(&time_now);
    year = ptm->tm_year+1900;
    month = ptm->tm_mon+1;
    date = ptm->tm_mday;
    day_of_week = ptm->tm_wday;
    switch (day_of_week)
    {
        case DAY_SUNDAY:
            day_of_week_str = "Sunday";
            break;
        case DAY_MONDAY:
            day_of_week_str = "Monday";
            break;
        case DAY_TUESDAY:
            day_of_week_str = "Tuesday";
            break;
        case DAY_WEDNESDAY:
            day_of_week_str = "Wednesday";
            break;
        case DAY_THURSDAY:
            day_of_week_str = "Thursday";
            break;
        case DAY_FRIDAY:
            day_of_week_str = "Friday";
            break;
        case DAY_SATURDAY:
            day_of_week_str = "Saturday";
            break;
    }
}

/*
 * construct a new date given the
 * date, month and year in the 
 * arguments.
 */
Date::Date(int date, int month, int year)
{
    int no_of_years = 0;
    int i, no_of_days = 0;
    int cumulative_day_count = 0;
    int no_of_leap_years = 0;

    this->year = year;
    this->month = month;
    this->date = date;

    no_of_years = year - 1900;
    for (i = 1900; i < year; i++)
    {
        if (!(i % 4) && ((i % 100) || !(i % 400)))
        {
            no_of_leap_years++;
        }
    }
    cumulative_day_count = cumulative_days(month-1, year);

    no_of_days = no_of_years*365 + no_of_leap_years + cumulative_day_count
        + date - 1;

    switch(no_of_days%7)
    {
        case 0:
            day_of_week = DAY_MONDAY;
            day_of_week_str = "Monday";
            break;
        case 1:
            day_of_week = DAY_TUESDAY;
            day_of_week_str = "Tuesday";
            break;
        case 2:
            day_of_week = DAY_WEDNESDAY;
            day_of_week_str = "Wednesday";
            break;
        case 3:
            day_of_week = DAY_THURSDAY;
            day_of_week_str = "Thursday";
            break;
        case 4:
            day_of_week = DAY_FRIDAY;
            day_of_week_str = "Friday";
            break;
        case 5:
            day_of_week = DAY_SATURDAY;
            day_of_week_str = "Saturday";
            break;
        case 6:
            day_of_week = DAY_SUNDAY;
            day_of_week_str = "Sunday";
            break;
    }
}

/*
 * create a new date object by parsing the date
 * string
 */
Date::Date(string datestr)
{
	//date format is dd/mm/yyyy
	int date = -1, month = -1, year = -1;
	sscanf(datestr.c_str(), "%d/%d/%d", &date, &month, &year);
	*this = Date(date, month, year);
}

/*
 * increment a date, accounting for
 * month and year boundaries.
 */
Date Date::operator ++()
{
    int new_date, new_month, new_year;

    if (date + 1 > max_days_in_month(month, year))
    {
        if (month == 12)
        {
            new_date = 1;
            new_month = 1;
            new_year = year + 1;
        }
        else
        {
            new_date = 1;
            new_month = month + 1;
            new_year = year;
        }
    }
    else
    {
        new_date = date + 1;
        new_month = month;
        new_year = year;
    }

    Date new_day = Date(new_date, new_month, new_year);
    *this = new_day;
    return new_day;
}

/*
 * decrement a date, accounting for
 * month and year boundaries.
 */
Date Date::operator --()
{
    int new_date, new_month, new_year;

    if (date == 1)
    {
        if (month == 1)
        {
            new_date = max_days_in_month(12, year - 1);
            new_month = 12;
            new_year = year - 1;
        }
        else
        {
            new_date = max_days_in_month(month - 1, year);
            new_month = month - 1;
            new_year = year;
        }
    }
    else
    {
        new_date = date - 1;
        new_month = month;
        new_year = year;
    }

    Date new_day = Date(new_date, new_month, new_year);
    *this = new_day;
    return new_day;
}

/*
 * compare two date objects, keeping the date,
 * month and year into account
 */
bool Date::operator < (const Date& date_in) const
{
    if (year == date_in.year)
    {
        if (month == date_in.month)
        {
            return (date < date_in.date);
        }
        else
        {
            return (month < date_in.month);
        }
    }
    else
    {
        return (year < date_in.year);
    }
}

/*
 * compare two date objects, keeping the date,
 * month and year into account
 */
bool Date::operator <= (const Date& date_in) const
{
    if (year == date_in.year)
    {
        if (month == date_in.month)
        {
            return (date <= date_in.date);
        }
        else
        {
            return (month <= date_in.month);
        }
    }
    else
    {
        return (year <= date_in.year);
    }
}

/*
 * compare two dates for equality
 */
bool Date::operator == (const Date& date_in) const
{
    return ((year == date_in.year) && (month == date_in.month) && (date ==
                date_in.date));
}

/*
 * validate a given date, keeping into 
 * account the days in a month, and
 * accouting for leap years.
 */
bool Date::is_valid(void)
{
	int day_count;
	if (year < 1900 || year > 9999)
		return false;

	if (month < 1 || month > 12)
		return false;

	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (date < 1 || date > 31) 
				return false;
			break;
		case 2:
			day_count = 28;
			if (!(year % 4) && ((year % 100) || !(year % 400)) && (month > 1))
			{
				/* leap year */
				day_count = 29;
			}
			if (date < 1 || date > day_count)
				return false;
			break;
		default:
			if (date < 1 || date > 30) 
				return false;
			break;
	}
	return true;
}
