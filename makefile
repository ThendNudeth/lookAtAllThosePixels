# ----------------------------------------------------------------
# Makefile : GRAPHICS C
# Project restructuring v1.0
# @author N. van Huyssteen
# ----------------------------------------------------------------

# ----------------------------------------------------------------
# Variables: Objects and Options
# ----------------------------------------------------------------

# LIBRARIES     = -lm
# EXECUTABLE    = a.out

# SRCDIR        = src/
# BUILDDIR      = build/
# SFILES        = c
# OFILES        = out

# SOURCES       = $(shell find $(SRCDIR) -name "*.$(SFILES)")
# OBJECTS       = $(patsubst $(SRCDIR)%.$(SFILES), $(BUILDDIR)%.$(OFILES), $(SOURCES))

# FLAGS         = 2>>$(BUILDDIR)err
# CXXFLAGS      = ${DEBUG} ${WARNINGS} ${OPTIMIZE} ${BOUNDS} ${PROFILE}
# WARNINGS      = -Wall -W # -Wno-unused-result -Wno-deprecated
# CXX           = gcc -g -fpermissive -std=gnu++11 # -std=c++0x 

# OPTIMIZE      = -O3
# DEBUG         = #-ggdb

# PROFILE       = # -pg
# BOUNDS        = # -fbounds-checking

# ----------------------------------------------------------------
# Rules
# ----------------------------------------------------------------
mac: src/SDL/makeAWindow/*.c src/SDL/Universe/*.c src/SDL/Dependencies/*.c
	gcc $$(sdl2-config --cflags --libs) src/SDL/makeAWindow/*.c src/SDL/Universe/*.c src/SDL/Dependencies/*.c -I/opt/homebrew/include -L/opt/homebrew/lib -lgsl -lgslcblas -lm -o main
naive: src/SDL/makeAWindow/*.c src/SDL/Universe/*.c
	gcc $$(sdl2-config --cflags --libs) src/SDL/makeAWindow/*.c -o main -D NAIVE
naive2: src/SDL/makeAWindow/*.c src/SDL/Universe/*.c
	gcc $$(sdl2-config --cflags --libs) src/SDL/makeAWindow/*.c -o main -D NAIVE2
# mac: src/SDL/makeAWindow/*.c
# 	gcc -lstdc++ $$(sdl2-config --cflags --libs) src/SDL/makeAWindow/*.c -o main -D HEAP_COLOURS

app: src/*.c src/imageProcessor/*.c src/framebuffer/*.c
	gcc -g src/*.c src/imageProcessor/imageProcessor.c src/framebuffer/framebuffer.c -lm -lncurses -o bar

testla: src/SDL/Linear_Algebra/*.c src/SDL/Dependencies/*.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib src/SDL/Linear_Algebra/*.c src/SDL/Dependencies/*.c -lgsl -lgslcblas -lm -o main

gsl: src/SDL/try_gsl/*.c
	gcc -I/opt/homebrew/include -L/opt/homebrew/lib src/SDL/try_gsl/*.c -lgsl -lgslcblas -lm -o main

clean: 
	rm 

