# name of output program
TARGET=defsurfaces

CC=gcc

# projects dirs and configuration files
BINDIR=bin
SRCDIR=src
INCDIR=include
TESTDIR=tests
OBJDIR=obj
DOXCONF=docsgen.conf

CFLAGS=-Wall -g -I$(INCDIR) -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib -L/usr/local/lib

# getting source files and obj names
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TESTS    := $(wildcard $(TESTDIR)/*.c)
TESTBINS := $(TESTS:$(TESTDIR)/%.c=$(BINDIR)/%)
TESTOBJ  := $(TESTS:$(TESTDIR)/%.c=$(OBJDIR)/%.o)

# flags to be used
LFLAGS=-lm -lGL -lGLU -lglut -LGL -lX11 -lX11 -lgsl -lgslcblas

# make main executable
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $^ $(LFLAGS) -o $@

# make obj files	$(CC) $^ $(LFLAGS) -o $@	$(CC) $^ $(LFLAGS) -o $@


$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# compile tests
test: $(TESTBINS)

$(TESTBINS): $(TESTOBJ) $(OBJECTS)
	$(CC) $(filter-out obj/main.o $(filter-out $(patsubst $(BINDIR)/%,$(OBJDIR)/%.o,$@), $(TESTOBJ)), $(OBJECTS) $(TESTOBJ)) -o $@ $(LFLAGS)

$(TESTOBJ): $(TESTS)
	$(CC) $(CFLAGS) -c $(patsubst $(OBJDIR)/%.o,$(TESTDIR)/%.c,$@) -o $@


# generate docs
gendocs: $(SOURCES)
	doxygen $(DOXCONF)

.PHONY: clean
clean:
	rm -f obj/* bin/*
