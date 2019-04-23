# # Makefile for CPS 222 Project 3
#
# # Google Test must be cloned and built.  If it's not in the same parent
# # directory (..), change GTEST_ROOT to the actual location.
# GTEST_ROOT = ../googletest/googletest
# GTEST_MAIN = $(GTEST_ROOT)/make/gtest_main.a
#
# # Compiler flags: C+ 2011 features, extra warnings (-Wall), debugging (-g),
# #                 and Google Test
# CPPFLAGS = --std=c++11 -Wall -g -I $(GTEST_ROOT)/include


# Build program for manual testing
all:	project5 test


project5: project5.o graph.o
	g++ -o $@ $^

graph.o: graph.h

test: project5
						./project5 < test.in


# %.o: %.cc
# 	 	g++ -c $<
