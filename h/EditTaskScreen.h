/*****************************************************************************
* 
* This header file declares the EditTaskScreen class.
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
class EditTaskScreen : public Screen
{
    private:
        string day_string;
        string orig_task_string;
    public:
        EditTaskScreen(Date& date);
        void display(void);
        string interact(void);
};