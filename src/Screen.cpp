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
   21-Aug-2005  Gaurav Jain      Initial Version     -
   03-Sep-2005  Gaurav Jain      Numerous Updates    0.1
*****************************************************************************/
#include "Common.h"

/*
 * generic screen initialization with
 * the title, revision and copyright
 * that are shown at the top.
 */
Screen::Screen(string title, string revision, string copyright)
{
    this->title = title;
    this->revision = revision;
    this->copyright = copyright;
}

/*
 * display the top bar of every 
 * screen.
 */
void Screen::display(void)
{
    char title_str[80], revision_str[80], copyright_str[80];
    
    strcpy(title_str, title.c_str());
    strcpy(revision_str, revision.c_str());
    strcpy(copyright_str, copyright.c_str());

    attron(PROGRAM_NAME_ATTR);
    mvprintw(0, 1, title_str);
    attroff(PROGRAM_NAME_ATTR);
    attron(COPYRIGHT_ATTR);
    mvprintw(0, 49, copyright_str);
    attroff(COPYRIGHT_ATTR);
}
