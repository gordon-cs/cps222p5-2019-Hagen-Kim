# Makefile for CPS222 Project 5

# Google Test must be cloned and built.  If it's not in the same parent
# directory (..), change GTEST_ROOT to the actual location.
GTEST_ROOT = ../googletest/googletest
GTEST_MAIN = $(GTEST_ROOT)/make/libgtest_main.a

# Compiler flags: extra warnings (-Wall), debugging (-g), and Google Test
# Use C 2011 (required by Google Test, and a good idea anyway)
CXXFLAGS = -std=c++11

# -Wall and -Wextra requests more warnings -- fix them for clean code
# -g compiles for debugging
CPPFLAGS = -I $(GTEST_ROOT)/include -Wall -Wextra -g

all:	project5 test

graph.cc: graph.h
	g++ -o $@ $^

project5: 	graph.o $(SUPPORT_OBJ) project5.o
	g++ -o $@ $^
