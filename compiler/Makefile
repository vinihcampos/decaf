# ----------------------
# MACROS
# ----------------------

# DIRS
INCDIR = include
BINDIR = bin
SRCDIR = src
BUILDDIR = build
# LIB OPTIONS
# TARGET
LEXFILE = lexical.lex
LEXFILE_C = lex.yy.c
TARGET = $(BINDIR)/lexical_analyzer
# EXTENSIONS
SRCEXT = c
HEADEREXT = h
# SOURCES LIST
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# OBJECTS
OBJS = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))  
# COMPILER
CC = gcc
LEX = @lex 
# FOR CLEANING
RM = /bin/rm
# WARNING FLAG
WARN = -Wall
# DEBUG FLAGS
DEBUG = -g
# LINKING FLAGS
LIBFLAG = -lfl
INCFLAG = -I $(INCDIR)
LFLAGS = $(DEBUG) $(WARN) $(INCFLAG) $(LIBFLAG)
# COMPILATION FLAGS
CFLAGS = $(DEBUG) -c $(WARN)

# ----------------------
# ENTRIES
# ----------------------

$(TARGET): $(BUILDDIR)/lex.yy.o $(OBJS)
	@echo "Linking..."
	@mkdir -p $(BINDIR)
	@echo " $(CC) $^ -o $(TARGET) $(LFLAGS)"; $(CC) $^ -o $(TARGET) $(LFLAGS); 
	@rm -rf $(SRCDIR)/$(LEXFILE_C)

$(BUILDDIR)/lex.yy.o: $(SRCDIR)/$(LEXFILE_C)
	@mkdir -p $(BUILDDIR)
	@$(CC) $(CFLAGS) $(INCFLAG) -o $@ $<;

$(SRCDIR)/$(LEXFILE_C):
	$(LEX) $(SRCDIR)/$(LEXFILE)
	@mv $(LEXFILE_C) $(SRCDIR)/

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<"; $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<;
	
# DUMMY ENTRIES
clean:
	@echo "Cleaning..."
	@echo "$(RM) -rf $(BUILDDIR) $(TARGET)"; $(RM) -rf $(BUILDDIR) $(TARGET)
	@rm -rf $(SRCDIR)/$(LEXFILE_C) 

.PHONY: clean

