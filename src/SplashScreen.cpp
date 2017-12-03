/*****************************************************************************
* 
* This source file implements the SplashScreen.
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
   04-Sep-2005  Gaurav Jain      Initial Version   0.1
*****************************************************************************/
#include "Common.h"

/*
 * initialize the splash screen with
 * the given type.
 */
SplashScreen::SplashScreen(int screen_type)
{
	this->screen_type = screen_type;
	switch (screen_type)
	{
		case WELCOME_SCREEN:
			this->title = "Welcome to";
			break;
		case ABOUT_SCREEN:
			this->title = "You're using";
			break;
		case WARRANTY_SCREEN:
			this->title = "Warranty statement";
			break;
		case HELP_SCREEN:
			this->title = "Need Help?";
			break;
		case GOODBYE_SCREEN:
			this->title = "Goodbye from";
			break;
	}
	this->revision = SCREEN_REVISION;
	this->copyright = SCREEN_COPYRIGHT;
	this->homepage = SCREEN_HOMEPAGE;
}

/*
 * generate a centered string
 * of the given total length (out_len),
 * and by centering the in_str sandwitched
 * between spaces.
 */
void SplashScreen::generateCenteredString(char out_str[], const char *in_str, int out_len)
{
	out_str[0] = '\0';
	int in_len = strlen(in_str);
	int i;
	for (i = 0; i < (out_len - in_len)/2; i++)
		strcat(out_str, " ");
	strcat(out_str, in_str);
	int remaining_len = out_len - strlen(out_str);
	for (i = 0; i < remaining_len; i++)
		strcat(out_str, " ");
}

/*
 * dispay the splash screen, and
 * wait for a key press.
 */
void SplashScreen::display(void)
{
    int lastrow, lastcol, startrow, startcol;
    getmaxyx(stdscr, lastrow, lastcol);
    startcol = (lastcol - 63)/2;
    startrow = (lastrow - 19)/2 - 1;
    char title_str[100] = "";
    char revision_str[100] = "";
    char copyright_str[100] = "";
    char homepage_str[100] = "";
    generateCenteredString(title_str, title.c_str(), 63);
    generateCenteredString(revision_str, revision.c_str(), 63);
    generateCenteredString(copyright_str, copyright.c_str(), 63);
    generateCenteredString(homepage_str, homepage.c_str(), 63);

    clear();
    attron(A_BOLD);
    attron(COLOR_PAIR(7));
    mvprintw(startrow++, startcol, "_________________________________________________________________\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attron(COLOR_PAIR(6));
    printw(title_str);
    attroff(COLOR_PAIR(6));
    attron(A_BOLD);
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("                                                               ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("        |\\   |   ___              |        ___     ___         ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("        | \\  |  /   \\  |   |   | _|___    /   \\  |/   \\        ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("        |  \\ | |     | |   |   |  |      |     | |     |       ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(4));
    printw("        |   \\| |\\___/  |   |   |  |      |     | |     |       ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(4));
    printw("        |    |  \\____   \\_/ \\_/    \\___/  \\___/  |     |       ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(3));
    attroff(A_BOLD);
    printw(revision_str);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(5));
    attroff(A_BOLD);
    printw(copyright_str);
    attron(A_BOLD);
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    if (screen_type == HELP_SCREEN)
    {
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(6));
    attroff(A_BOLD);
    printw(homepage_str);
    attron(A_BOLD);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(7));
    printw("|\n");
    }
    else if ((screen_type == WARRANTY_SCREEN) || (screen_type ==
                WELCOME_SCREEN))
    {
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attroff(A_BOLD);
    attron(COLOR_PAIR(2));
    printw(" Newton is protected under the ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    attron(A_BOLD);
    printw("GNU General Public License      ");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");

    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    printw(" and comes with ABSOLUTELY NO WARRANTY. This is free software  ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");

    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    printw(" and you are free to redistribute it under certain conditions. ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");

    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    printw(" See the GNU General Public License for more details.          ");
    attron(A_BOLD);
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(7));
    printw("|\n");
    }
#if 0
    mvprintw(startrow++, startcol, "|                                                             |\n");
#endif
    mvprintw(startrow++, startcol, "|_______________________________________________________________|\n");
    attroff(COLOR_PAIR(7));
    attroff(A_BOLD);

    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key ...\n");
    getch();
    clear();
}
