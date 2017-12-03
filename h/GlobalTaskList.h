/*****************************************************************************
* 
* This header file declares the various task list classes.
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

   Date         Updater          Comment              Revision
   21-Aug-2005  Gaurav Jain      Initial Version      -
   04-Sep-2005  Gaurav Jain      Numerous Updates     0.1
*****************************************************************************/
class GlobalTaskList
{
    private:
        map<Date, DayTasks> task_list;
        vector<RecurrentTask> recurrent_task_list;
    public:
        int loadTasks(void);
        int unloadTasks(void);
        void addTask(Date date, DayTasks day_tasks);
        void addRecurrentTask(RecurrentTask recurrent_task);
        DayTasks getTasks(Date date);
        RecurrentTask getRecurrentTask(int index);
        void deleteTask(Date date);
        //void deleteRecurrentTask(RecurrentTask recurrent_task);
        void deleteRecurrentTask(int index);
        void replaceRecurrentTask(int index, RecurrentTask recurrent_task);
        int parseLineForTask(char *line);
        int parseLineForRecurrentTask(char *line);
	vector<RecurrentTask> getRecurrentTaskList(void);
	int getRecurrentTaskCount(void);
};
