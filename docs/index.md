![Welcome Screen](/images/screenshot_welcome.jpg?raw=true "Welcome Screen")

# Summary of Features
Following are listed the important features of this version of Newton:

1. Newton is primarily a Time/Task management software for Unix users.
2. It provides support for multiple displays, such as Daily View, Weekly View, Monthly View in an easily identifiable, colored view.
3. New tasks can be added, and existing tasks can be edited, deleted, or their status can be changed to Completed, Pending or Cancelled. Thus you can very easily track how you progress through the most important tasks that you need to perform.
4. Holidays and working days can be kept track of, and any day can be easily marked as holiday or unmarked. Saturdays and Sundays default to holidays, but can easily be marked as working days.
5. Recurrent tasks can be added, which means, that you can set up &quot;rules&quot; for different tasks. For example, you can set up tasks to be executed every Sunday, or on the 4th and 6th of every month, or even on the 8th october of every year. You can even set up daily tasks, and set up tasks to be executed on every holiday or on every working day.
6. Navigation among and between the different views is extremely user friendly and keyboard shortcuts make this very easy. You can use the arrow keys to move between different entries, and can also use the vi style keyboard navigation shortcuts, like 'h', 'j', 'k', 'l' for those who find that more comfortable.
7. <img src="images/new.gif" alt="" height="40" width="40" border="0">Print selective tasks to PDF&nbsp;format, for easy printing to paper.  Check out a sample output <a href="software/plan.pdf">here</a>.


## Daily View

1. The daily view displays the tasks that have been scheduled for a particular day.
2. You can add/edit/delete tasks for that particular day by using the keyboard shortcuts available at the bottom of the screen.
3. You can also change the status of tasks, such as "Completed", "Pending", "Cancelled". By default, when a new task is added, its status is set to "Pending". Once you have finished performing the task, you can mark it as "Completed". If, for some reason, you decide not to perform that task any longer, you can simply mark it as "Cancelled".
4. In addition to the tasks set specifically for this day, any "recurrent" tasks that have been set, and which apply for this day, are also shown in the daily view. For more information on recurrent tasks, refer the section on Recurrent Tasks below.
5. You can navigate to the next day and previous day by using the keyboard shortcuts available at the bottom of the screen.
6. You can also navigate to the Weekly View, Monthly View or the Recurrent Tasks by using the shortcuts available.

![Daily View](/images/screenshot_day.jpg?raw=true "Daily View")

## Weekly View

1. The weekly view displays the number of tasks, and a brief description of the tasks that have been set for the days in that particular week.
2. Saturday and Sunday are assumed to be "holidays" by default. You can also mark other days as holidays, or unmark a holiday, by using the shortcuts available. The holidays and working days are shown with different colors for easier reference.
3. You can navigate to the next week or the previous week by using the keyboard shortcuts available at the bottom of the screen.
4. One day is always shown as highlighted with a yellow background in the weekly view, and you can easily go directly to that day's daily view, by simply pressing ENTER when that day is selected.
5. You can also navigate to the daily view, monthly view or recurrent tasks view by using the available shortcuts.

![Weekly View](/images/screenshot_week.jpg?raw=true "Weekly View")

## Monthly View

1. The monthly view displays the days of the selected month, in a calender style view.
2. You can easily navigate around the different days of the month by using the arrow keys, or the 'h', 'j', 'k', 'l' vi style shortcuts.
3. At any time, one day is selected in the month with a hightlighted background, and you can easily navigate to that day by pressing ENTER.
4. The Weekly view for the selected day can be switched to by using the shortcut available at the bottom of the screen.
5. You can also move to the next or previous monthly view by using the available shortcuts.
6. The default view when Newton begins is the Monthly view, and the day that is selected by default is Today. This helps you locate what tasks you had set up for today, and for upcoming days.

![Monthly View](/images/screenshot_month.jpg?raw=true "Monthly View")

## Recurrent Tasks

1. Recurrent tasks are those tasks that have an associated "rule" which maps these tasks to multiple days.
2. Recurrent tasks can be set with daily schedule, in which you can specify whether you want the task to be set for all days, for only holidays, or for only working days.
3. You can also set a weekly schedule, in which one or a combination of more than one days of the week can be chosen for this task. For example, you can set a task that need to be done every Sunday and Tuesday.
4. Monthly schedules can also be set up. For example, you can set a recurrent task to be done on the 2nd and 4th of every month.
5. The last kind of schedule is yearly, in which on particular dates of every year, a task can be scheduled (e.g., on 4th September of every year).

![Recurrent Tasks](/images/screenshot_recurrent.jpg?raw=true "Recurrent Tasks")

## Printing Tasks to PDF

Starting with Newton 0.2, you can choose to print your tasks that are recorded in the database to a PDF document using the command line.

## Usage

newton
* `-o <filename.pdf>` specify output file name (must end if .pdf) this is the output file to which the task list will be written
* `-f <date>` specify start date (dd/mm/yyyy or today or tomorrow) this is the start date from which to enumerate tasks
* `-t <date>` specify end date (dd/mm/yyyy or today or tomorrow) this is the end date until which to enumerate tasks
* `-d <no. of days>` specify number of days this is the number of days for which to enumerate tasks
* `-w` specify whole week following the start date if you specify this, the from date is taken as beginning of week
* `--today` print task list for today
* `--tomorrow` print task list for tomorrow
* `--help` print this usage

### Examples
* To print tasks from 12/09/2005 to 03/01/2006 to ./output.pdf, do: `newton -o ./output.pdf -f 12/09/2005 -t 03/01/2006`
* To print tasks for 12 days starting 12/09/2005 to ./output.pdf, do: `newton -o ./output.pdf -f 12/09/2005 -d 12`
* To print tasks for the week starting 12/09/2005 to ./output.pdf, do: `newton -o ./output.pdf -f 12/09/2005 -w`
* To print tasks for today to ./output.pdf, do: `newton -o ./output.pdf --today`
* To print tasks for 8 days starting from tomorrow to ./output.pdf, do: `newton -o ./output.pdf -f tomorrow -d 8`

![Command Line Usage](/images/screenshot_command_line_usage.jpg?raw=true "Command Line Usage")

## FAQs

Q) I'm not able to run Newton on my system. When I run it, it doesn't display anything on the screen!
A) Probably your system does not support the screen based displays. Newton requires screen based display support. This is present in most modern X-window based unix systems.

Q) I have observed a crash in the program. What do I do?
A) That is not surprising, since I have written this in such a hurry. If you can give me the exact situation in which you observed the fault, please do write to me with the details, and I will try to provide a fix asap.

Q) I have a few suggestions for improvement of Newton.
A) Please mail me those valuable suggestions at the contact information given on the homepage of Newton, and I will try to analyze them. Thanks.

Q) I would like to modify some part of Newton. Can I do that?
A) Newton is free software, so you can modify and redistribute it. But it is protected by GNU General Public License, so you MUST comply to the license agreements before doing any modifications. Please go through the license (it is available with Newton as well) carefully, and do write to me if you still have any queries.

