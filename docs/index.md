

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

<ol>
<li>The daily view displays the tasks that have been scheduled for a particular day.</li>
<li>You can add/edit/delete tasks for that particular day by using the keyboard shortcuts available at the bottom of the screen.</li>
<li>You can also change the status of tasks, such as "Completed", "Pending", "Cancelled". By default, when a new task is added, its status is set to "Pending". Once you have finished performing the task, you can mark it as "Completed". If, for some reason, you decide not to perform that task any longer, you can simply mark it as "Cancelled".</li>
<li>In addition to the tasks set specifically for this day, any "recurrent" tasks that have been set, and which apply for this day, are also shown in the daily view. For more information on recurrent tasks, refer the section on Recurrent Tasks below.</li>
<li>You can navigate to the next day and previous day by using the keyboard shortcuts available at the bottom of the screen.</li>
<li>You can also navigate to the Weekly View, Monthly View or the Recurrent Tasks by using the shortcuts available.</li>
</ol>
<hr>
<div class="section-heading" align="center">Weekly View</div>

<ol>
<li>The weekly view displays the number of tasks, and a brief description of the tasks that have been set for the days in that particular week.</li>
<li>Saturday and Sunday are assumed to be "holidays" by default. You can also mark other days as holidays, or unmark a holiday, by using the shortcuts available. The holidays and working days are shown with different colors for easier reference.</li>
<li>You can navigate to the next week or the previous week by using the keyboard shortcuts available at the bottom of the screen.</li>
<li>One day is always shown as highlighted with a yellow background in the weekly view, and you can easily go directly to that day's daily view, by simply pressing ENTER when that day is selected.</li>
<li>You can also navigate to the daily view, monthly view or recurrent tasks view by using the available shortcuts.</li>
</ol>
<hr>
<div class="section-heading" align="center">Monthly View</div>

<ol>
<li>The monthly view displays the days of the selected month, in a calender style view.</li>
<li>You can easily navigate around the different days of the month by using the arrow keys, or the 'h', 'j', 'k', 'l' vi style shortcuts.</li>
<li>At any time, one day is selected in the month with a hightlighted background, and you can easily navigate to that day by pressing ENTER.</li>
<li>The Weekly view for the selected day can be switched to by using the shortcut available at the bottom of the screen.</li>
<li>You can also move to the next or previous monthly view by using the available shortcuts.</li>
<li>The default view when Newton begins is the Monthly view, and the day that is selected by default is Today. This helps you locate what tasks you had set up for today, and for upcoming days.</li>
</ol>
<hr>
<div class="section-heading" align="center">Recurrent Tasks</div>

<ol>
<li>Recurrent tasks are those tasks that have an associated "rule" which maps these tasks to multiple days.</li>
<li>Recurrent tasks can be set with daily schedule, in which you can specify whether you want the task to be set for all days, for only holidays, or for only working days.</li>
<li>You can also set a weekly schedule, in which one or a combination of more than one days of the week can be chosen for this task. For example, you can set a task that need to be done every Sunday and Tuesday.</li>
<li>Monthly schedules can also be set up. For example, you can set a recurrent task to be done on the 2nd and 4th of every month.</li>
<li>The last kind of schedule is yearly, in which on particular dates of every year, a task can be scheduled (e.g., on 4th September of every year).</li>
</ol>
<hr>
<div class="section-heading" align="center">Printing Tasks to PDF</div>
<br>
Starting with Newton 0.2, you can choose to print your tasks that are recorded in the database to a PDF document using the command line.

<br><br>
<b>Usage:</b>
<br><br>
<b>newton</b>
<ul>
<li><b>-o <filename.pdf></b> specify output file name (must end if .pdf) this is the output file to which the task list will be written</li>
<li><b>-f <date></b> specify start date (dd/mm/yyyy or today or tomorrow) this is the start date from which to enumerate tasks</li>
<li><b>-t <date></b> specify end date (dd/mm/yyyy or today or tomorrow) this is the end date until which to enumerate tasks</li>
<li><b>-d <no. of days></b> specify number of days this is the number of days for which to enumerate tasks</li>
<li><b>-w</b> specify whole week following the start date if you specify this, the from date is taken as beginning of week</li>
<li><b>--today</b> print task list for today</li>
<li><b>--tomorrow</b> print task list for tomorrow</li>
<li><b>--help</b> print this usage</li>
</ul>

<br>
<b>Examples:</b>
<br>

<ul>
<li>To print tasks from 12/09/2005 to 03/01/2006 to ./output.pdf, do:<b> newton -o ./output.pdf -f 12/09/2005 -t 03/01/2006</b></li>
<li>To print tasks for 12 days starting 12/09/2005 to ./output.pdf, do:<b> newton -o ./output.pdf -f 12/09/2005 -d 12</b></li>
<li>To print tasks for the week starting 12/09/2005 to ./output.pdf, do:<b> newton -o ./output.pdf -f 12/09/2005 -w</b></li>
<li>To print tasks for today to ./output.pdf, do:<b> newton -o ./output.pdf --today</b></li>
<li>To print tasks for 8 days starting from tomorrow to ./output.pdf, do:<b> newton -o ./output.pdf -f tomorrow -d 8</b></li>
</ul>

