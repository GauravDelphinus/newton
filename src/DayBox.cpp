/*****************************************************************************
* 
* This source file implements the DayBox class.
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
   28-Aug-2005  Gaurav Jain      Initial Version   0.1
*****************************************************************************/
#include "Common.h"

/*
 * create an empty DayBox
 */
DayBox::DayBox(void)
{
    // TBD
}

/*
 * Create a new DayBox with the given 
 * DayTasks, and the given row/col
 * numbers associated with it.
 */
DayBox::DayBox(DayTasks day_tasks_in, int row, int col)
{
    day_tasks = day_tasks_in;
    row_min = MONTH_BOX_BASE_ROW + 3 + row * MONTH_BOX_ROW_HEIGHT;
    row_max = row_min + MONTH_BOX_ROW_HEIGHT;
    col_min = MONTH_BOX_BASE_COL + col * MONTH_BOX_COL_WIDTH;
    col_max = col_min + MONTH_BOX_COL_WIDTH;
}
