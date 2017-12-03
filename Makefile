##############################################################################
# MAKEFILE FOR MAIN FILES
##############################################################################
##############################################################################
#    Copyright (C) 2003 Gaurav Jain
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##############################################################################
##############################################################################
#   Revision History
#
#   Date         Updater          Revision   Comment
#   21-Aug-2005  Gaurav Jain      -          Initial Version
#   04-Sep-2005  Gaurav Jain      0.1        Numerous changes
##############################################################################

CC=g++
LD=ld

INCLUDE=-I. \
    -I$(NEWTON_BASE_DIR)/h

#CFLAGS=  -c -DLOCAL_DEBUG -DMM_KER -DSIPALG_UT -g -Wall
CFLAGS=  -c -g -Wall 
LIBFLAGS= -lcurses

LDFLAGS= -r
TOTAL = $(CFLAGS) $(INCLUDE)

OBJ_DIR=$(NEWTON_BASE_DIR)/obj
SRC_DIR=$(NEWTON_BASE_DIR)/src

TARGET=$(OBJ_DIR)/newton.o

OBJ=$(OBJ_DIR)/Main.o \
	$(OBJ_DIR)/Date.o \
	$(OBJ_DIR)/DayBox.o \
	$(OBJ_DIR)/AddTaskScreen.o \
	$(OBJ_DIR)/AddRecurrentTaskScreen.o \
	$(OBJ_DIR)/DayScreen.o \
	$(OBJ_DIR)/RecurrentTasksScreen.o \
	$(OBJ_DIR)/DayTasks.o \
	$(OBJ_DIR)/EditTaskScreen.o \
	$(OBJ_DIR)/GlobalTaskList.o \
	$(OBJ_DIR)/MonthScreen.o \
	$(OBJ_DIR)/Screen.o \
	$(OBJ_DIR)/SplashScreen.o \
	$(OBJ_DIR)/WeekScreen.o \
	$(OBJ_DIR)/Common.o \
	$(OBJ_DIR)/CLIParser.o

#top level rule

all:$(TARGET)
$(TARGET):	$(OBJ)
	$(LD)  -o $(OBJ_DIR)/newton.o $(LDFLAGS) $(OBJ)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(TOTAL) $< -o $@

newton:$(OBJ)
	$(CC)  $(LIBFLAGS) -o $@  $^

cleanall:clean
clean:
	rm -f $(OBJ_DIR)/*.o
	rm newton

