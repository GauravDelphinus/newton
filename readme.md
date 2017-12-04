README FILE FOR NEWTON
______________________

This file contains important information about the program 'Newton'. Please
go through this file before starting to use the program.  For documentation,
refer https://gauravdelphinus.github.io/newton/

WARRANTY STATEMENT
__________________

Copyright (C) 2005 - 2006  Gaurav Jain

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

CONTACT INFORMATION
___________________

For any queries regarding this program, the author can be reached
at the contact information available the homepage of this software.
Also, for latest updates to this software, you can visit the homepage
for Newton at the following web address:
https://github.com/GauravDelphinus/newton

WHAT IS NEWTON?
_______________

Newton is a Time/Task management software for Unix systems, and has a curses
based text-graphical interface for fast, easy, keyboard based operation.

AND "WHO" IS NEWTON?
__________________

As you may guess, this program is sincerely dedicated to Sir Isaac Newton
(1642 - 1727), the most important mathematician of the human history.  To find
out more about this great mathematician, I have written a summary of his life
in "newton.txt", which is also shipped along with this software.

NEWTON 0.2
_______________________
New Features:
1) Added support for printing a selected set of task list to a printable PDF
   file.  See Command Line Usage for more information

NEWTON 0.1
_______________________

Following are listed the important features of this version of Newton:
1) Newton is primarily a Time/Task management software for Unix users.
2) It provides support for multiple displays, such as Daily View, Weekly View,
   Monthly View in an easily identifiable, colored view.
3) New tasks can be added, and existing tasks can be edited, deleted, or their
   status can be changed to Completed, Pending or Cancelled.  Thus you can
   very easily track how you progress through the most important tasks that
   you need to perform.
4) Holidays and working days can be kept track of, and any day can be easily
   marked as holiday or unmarked.  Saturdays and Sundays default to holidays,
   but can easily be marked as working days.
5) Recurrent tasks can be added, which means, that you can set up "rules" for
   different tasks.  For example, you can set up tasks to be executed every
   Sunday, or on the 4th and 6th of every month, or even on the 8th october
   of every year.  You can even set up daily tasks, and set up tasks to be
   executed on every holiday or on every working day.
5) Navigation among and between the different views is extremely user friendly
   and keyboard shortcuts make this very easy.  You can use the arrow keys
   to move between different entries, and can also use the vi style keyboard
   navigation shortcuts, like 'h', 'j', 'k', 'l' for those who find that more
   comfortable.
6) And many more :-)


COMPILATION AND INSTALLATION
____________________________

Normally Newton is available in source code form, so the user 
must compile it for his environment.  The steps to be followed
for this are listed below.

1) Untar the "newton" folder to any suitable location in your unix
   system.  Let's say you untar all the files into the folder
   /user/gjain/newton
2) Make sure that the following files are present in the folder:

./Makefile
./tasks.db
./src
./src/AddRecurrentTaskScreen.cpp
./src/AddTaskScreen.cpp
./src/CLIParser.cpp
./src/Common.cpp
./src/Date.cpp
./src/DayBox.cpp
./src/DayScreen.cpp
./src/DayTasks.cpp
./src/EditTaskScreen.cpp
./src/GlobalTaskList.cpp
./src/Main.cpp
./src/MonthScreen.cpp
./src/RecurrentTasksScreen.cpp
./src/Screen.cpp
./src/SplashScreen.cpp
./src/WeekScreen.cpp
./obj
./h
./h/AddRecurrentTaskScreen.h
./h/AddTaskScreen.h
./h/CLIParser.h
./h/Common.h
./h/Date.h
./h/DayBox.h
./h/DayScreen.h
./h/DayTasks.h
./h/EditTaskScreen.h
./h/GlobalTaskList.h
./h/MonthScreen.h
./h/RecurrentTasksScreen.h
./h/Screen.h
./h/SplashScreen.h
./h/WeekScreen.h
./baks
./help.txt
./newton.txt
./readme.txt

   If any of the above files are missing, it means you have not got
   the correct archive, or your archive is corrupt.  Re-download the
   archive, and if you still face the same problem, contact me :-)
3) Set the environment variable below:
   export NEWTON_BASE_DIR=/user/gjain/newton

   Note that the above is an example in case the shell is bash.  
   IMPORTANT: It is NECESSARY to have this path set even after 
   compilation, during execution of the program.  So it would be
   good to set this in your ".profile", or the like.
4) Now you are ready for compilation.  Just run make using the Makefile
   present.
   make               --> This would create the object files in ./obj
   make newton        --> This would create the executable ./newton
5) If everything has gone well, you have successfully created the 
   executable "newton" in the path NEWTON_BASE_DIR.  You may add
   this path to the search path, generally "PATH" in your profile,
   so that you can run the program from any directory.
6) In case you face any problems that have not been answered, please
   contact me :-)
   
COMMAND LINE USAGE
------------------
Usage: newton 
  -o <filename.pdf>     specify output file name (must end if .pdf)
                        this is the output file to which the task list will be
written
  -f <date>             specify start date (dd/mm/yyyy or today or tomorrow)
                        this is the start date from which to enumerate tasks
  -t <date>             specify end date (dd/mm/yyyy or today or tomorrow)
                        this is the end date until which to enumerate tasks
  -d <no. of days>      specify number of days
                        this is the number of days for which to enumerate
tasks
  -w                    specify whole week following the start date
                        if you specify this, the from date is taken as
beginning of week
  --today               print task list for today
  --tomorrow            print task list for tomorrow
  --help                print this usage

  Examples:
  To print tasks from 12/09/2005 to 03/01/2006 to ./output.pdf, do:
        newton -o ./output.pdf -f 12/09/2005 -t 03/01/2006

  To print tasks for 12 days starting 12/09/2005 to ./output.pdf, do:
        newton -o ./output.pdf -f 12/09/2005 -d 12

        To print tasks for the week starting 12/09/2005 to ./output.pdf, do:
        newton -o ./output.pdf -f 12/09/2005 -w

  To print tasks for today to ./output.pdf, do:
        newton -o ./output.pdf --today

  To print tasks for 8 days starting from tomorrow to ./output.pdf, do:
        newton -o ./output.pdf -f tomorrow -d 8


SYSTEM REQUIREMENTS
___________________

Any Unix Compatible operating system that supports X-Windows, and support
for screen based displays (that support the curses library).

BUG REPORTS
___________

If you find any bug in this software, please write with details of condition
in which to reproduce bug to me, and I will try my best to provide you with
a fix asap.  Thank you for your support.

REVISION HISTORY
________________

Revision    Date            Authors

0.2         05-Dec-2005     Gaurav Jain (@GauravDelphinus)
0.1         04-Sep-2005     Gaurav Jain (@GauravDelphinus)
