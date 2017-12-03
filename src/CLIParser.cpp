/*****************************************************************************
* 
* This source file implements the base class for all screen types.
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

   Date         Updater          Comment             Revision
   21-Dec-2005  Gaurav Jain      Initial Version     0.2
*****************************************************************************/
#include "Common.h"

/*
 * Initialize parser object
 */
CLIParser::CLIParser(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++)
		args.push_back(string(argv[i]));

	//initialize the member vars
	outfilename = "";
	fromdate = Date(-1, -1, -1);
	todate = Date(-1, -1, -1);
}

/*
 * parse the command line arguments
 */
int CLIParser::parse(void)
{
	unsigned int i = 0;
	int no_of_days = 1;
	int j;
	while (i < args.size())
	{
		if (strncmp(args[i].c_str(), "-o", 2) == 0) //output file
		{
			i++;
			if (i < args.size())
				outfilename = args[i++];
			else
				return 0; //error
		}
		else if (strncmp(args[i].c_str(), "-f", 2) == 0) //from date
		{
			i++;
			if (i < args.size())
			{
				if (strncmp(args[i].c_str(), "today", 5) == 0)
					fromdate = get_today();
				else if (strncmp(args[i].c_str(), "tomorrow", 8) == 0)
				{
					fromdate = get_today();
					++ fromdate;
				}
				else
					fromdate = Date(args[i]);
				i++;
			}
			else
				return 0; //error
		}
		else if (strncmp(args[i].c_str(), "-t", 2) == 0) //to date
		{
			i++;
			if (i < args.size())
			{
				if (strncmp(args[i].c_str(), "today", 5) == 0)
					todate = get_today();
				else if (strncmp(args[i].c_str(), "tomorrow", 8) == 0)
				{
					todate = get_today();
					++ todate;
				}
				else
					todate = Date(args[i]);
				i++;
			}
			else
				return 0; //error
		}
		else if (strncmp(args[i].c_str(), "-d", 2) == 0) //no of days
		{
			i++;
			if (i < args.size())
				no_of_days = atoi(args[i++].c_str());
			else
				return 0; //error
		}
		else if (strncmp(args[i].c_str(), "-w", 2) == 0) //week starting date
		{
			i++;
			no_of_days = 7;
		}
		else if (strncmp(args[i].c_str(), "--today", 7) == 0) //today
		{
			i++;
			fromdate = get_today();
			todate = fromdate;
		}
		else if (strncmp(args[i].c_str(), "--tomorrow", 10) == 0) //tomorrow
		{
			i++;

			fromdate = get_today();
			++ fromdate;
			todate = fromdate;
		}
		else if (strncmp(args[i].c_str(), "--help", 6) == 0) //show usage
		{
			i++;
			printUsage();
			return 1;
		}
		else
		{
			return 0;
		}
	}
if (fromdate.is_valid() && !todate.is_valid() && no_of_days > 0)
	{
		todate = fromdate;
		for (j = 1; j < no_of_days; j++)
			++ todate;
	}

	if (outfilename.length() > 0 && fromdate.is_valid() && todate.is_valid())
		return 1;

	return 0;
}

/*
 * take action on the command line
 * arguments
 */
int CLIParser::execute(void)
{
	if (-1 == g_task_list.loadTasks())
		return 0;

	char template_str[] = "/tmp/newtonXXXXXX";
	char *dirname = mkdtemp(template_str);

	char *cwd = getcwd(NULL, 0);
	chdir(dirname);
	FILE *fp = fopen("output.tex", "w");

	generateTexOutput(fp);

	fclose(fp);

	char latex_cmd_str[MAX_COMMAND_LINE_LENGTH];
	char *basedir = getenv("NEWTON_BASE_DIR");
	char logfilename[MAX_COMMAND_LINE_LENGTH];
	strcpy(logfilename, basedir);
	strcat(logfilename, "/newton.log");

	/* print date into the log file */
	char date_cmd_str[MAX_COMMAND_LINE_LENGTH];
	strcpy(date_cmd_str, "date >>");
	strcat(date_cmd_str, logfilename);
	system(date_cmd_str);

	/* redirect the logs into the log file */
	strcpy(latex_cmd_str, "pdflatex output.tex >>");
	strcat(latex_cmd_str, logfilename);
	system(latex_cmd_str);

	chdir(cwd);

	char copy_cmd_str[MAX_COMMAND_LINE_LENGTH];
	strcpy(copy_cmd_str, "cp ");
	strcat(copy_cmd_str, dirname);
	strcat(copy_cmd_str, "/");
	strcat(copy_cmd_str, "output.pdf");
	strcat(copy_cmd_str, " ");
	strcat(copy_cmd_str, outfilename.c_str());
	int retval = system(copy_cmd_str);

	if (retval == -1)
		return 0;

	return 1;
}

/*
 * print the usage of the command line
 * arguments
 */
void CLIParser::printUsage(void)
{
	printf("Usage: newton \n"
		"  -o <filename.pdf> \tspecify output file name (must end if .pdf)\n"
		"                    \tthis is the output file to which the task list will be written\n"
		"  -f <date>         \tspecify start date (dd/mm/yyyy or today or tomorrow)\n"
		"                    \tthis is the start date from which to enumerate tasks\n"
		"  -t <date>         \tspecify end date (dd/mm/yyyy or today or tomorrow)\n"
		"                    \tthis is the end date until which to enumerate tasks\n"
		"  -d <no. of days>  \tspecify number of days\n"
		"                    \tthis is the number of days for which to enumerate tasks\n"
		"  -w                \tspecify whole week following the start date\n"
		"                    \tif you specify this, the from date is taken as beginning of week\n"
		"  --today           \tprint task list for today\n"
		"  --tomorrow        \tprint task list for tomorrow\n"
		"  --help            \tprint this usage\n"
		"\n"
		"  Examples:\n"
		"  To print tasks from 12/09/2005 to 03/01/2006 to ./output.pdf, do:\n"
		"  \tnewton -o ./output.pdf -f 12/09/2005 -t 03/01/2006\n"
		"\n"
		"  To print tasks for 12 days starting 12/09/2005 to ./output.pdf, do:\n"
		"  \tnewton -o ./output.pdf -f 12/09/2005 -d 12\n"
		"\n"
		"\tTo print tasks for the week starting 12/09/2005 to ./output.pdf, do:\n"
		"  \tnewton -o ./output.pdf -f 12/09/2005 -w\n"
		"\n"
		"  To print tasks for today to ./output.pdf, do:\n"
		"  \tnewton -o ./output.pdf --today\n"
		"\n"
		"  To print tasks for 8 days starting from tomorrow to ./output.pdf, do:\n"
		"  \tnewton -o ./output.pdf -f tomorrow -d 8\n"
		"\n");
}

/*
 * print an error message
 */
void CLIParser::errorMessage(void)
{
	printf("Error encountered.  Refer the logfile newton.log for details\n");
}

void CLIParser::successMessage(void)
{
	printf("%s output file successfully created\n", outfilename.c_str());
}

/*
 * generate TeX output from the task list
 */
void CLIParser::generateTexOutput(FILE *fp)
{
	int i;
	char header[] = "\\documentclass[a4paper, 10pt]{article}\n"
			"\\author{Gaurav Jain}\n"
			"\\title{Task List}\n"
			"\\markright{Task List}\n"
			"\\pagestyle{empty}\n"
			"\\usepackage{verbatim}\n"
			"\\usepackage{array}\n"
			"\\usepackage{longtable}\n"
			"\\usepackage{geometry}\n"
			"\\geometry{margin=.5in,top=1in,bottom=1in,left=.5in,right=.5in,noheadfoot}\n"
			"\\begin{document}\n";
	char title[1000];
	char fromdate_str[100], todate_str[100];
	get_yearday_string(fromdate, fromdate_str);
	get_yearday_string(todate, todate_str);
	
	if (fromdate < todate)
		sprintf(title, "\\section *{\\begin{center} %s %d - %s %d \\end{center}}\n", fromdate_str, fromdate.year, todate_str, todate.year);
	else
		sprintf(title, "\\section *{\\begin{center} Task List \\end{center}}\n");

	char begin_table[] = "\\begin{longtable}{p{3cm}m{10cm}}\n";
	char end_table[] = "\\end{longtable}\n";
	char hline[] = "\\hline\n";
	char trailer[] = "\\end{document}\n";

	/* start generating the output */

	fprintf(fp, header);
	fprintf(fp, title);
	fprintf(fp, begin_table);
	fprintf(fp, hline);

	Date curr_date = fromdate;
	while (curr_date <= todate)
	{
		DayTasks day_tasks = DayTasks(curr_date.date, curr_date.month, curr_date.year);
		DayTasks all_tasks = day_tasks.generateAllTasks();

		char day_column[100];
		sprintf(day_column, "\\textbf{%s %d/%d/%d}\n", curr_date.day_of_week_str.c_str(), curr_date.date, curr_date.month, curr_date.year);
		char begin_entry[] = "& \\raggedright\n"; 
		char begin_list[] = "\\begin{itemize}\n";
		char end_list[] = "\\end{itemize}\n";
		char end_entry[] = "\\tabularnewline\n";
		char no_items_entry[] = "\\hspace{.5cm} \\emph{No Tasks}\n";
		char taskname[1000];

		/* generate output */
		fprintf(fp, day_column);
		fprintf(fp, begin_entry);
		if (all_tasks.no_of_tasks > 0)
		{
			fprintf(fp, begin_list);
			for (i = 0; i < all_tasks.no_of_tasks; i++)
			{
				sprintf(taskname, "\\item %s\n", all_tasks.tasks[i].task_name.c_str());
				fprintf(fp, taskname);
			}
			fprintf(fp, end_list);
		}
		else
		{
			fprintf(fp, no_items_entry);
		}
		fprintf(fp, end_entry);
		fprintf(fp, hline);

		++ curr_date;
	}

	fprintf(fp, end_table);
	fprintf(fp, trailer);

	/* done */
}
