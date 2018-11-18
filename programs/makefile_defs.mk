## output file name
MAIN=main

## suffixes used:
#.SUFFIXES: .cpp .o .x .h

## software directories
#### include: *.h  obj: *.o  lib: *.a  src: *.cpp
SOFT=../software
IDIR=$(SOFT)/include
ODIR=$(SOFT)/build
LDIR=$(SOFT)/lib
SDIR=$(SOFT)/src

## compiler and compiler flags
CC=g++
CFLAGS=-g -std=c++11
AFLAGS=-I$(IDIR) #-fast -W -Wall -WShadow -Wconversion

## additional libraries to link
LIBS=

## dependecies
#### pattern substition adds folder location to *.h files
_DEPS=coshfunc.h analysis.h system.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

## object files
#### pattern substition adds folder location to *.o files
_OBJ=coshfunc.o analysis.o system.o main.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

