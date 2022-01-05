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

app: src/*.c src/imageProcessor/*.c src/framebuffer/*.c
	gcc src/*.c src/imageProcessor/imageProcessor.c src/framebuffer/framebuffer.c -lm -o bar

