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
	@echo " $(CC) $^ -o $(TARGET) $(LFLAGS)"; $(CC) $^ -o $(TARGET) $(LFLAGS); 
	@rm -rf $(SRCDIR)/lex.yy.c

$(BUILDDIR)/lex.yy.o: $(SRCDIR)/lex.yy.c
	@mkdir -p $(BUILDDIR)
	@$(CC) $(CFLAGS) $(INCFLAG) -o $@ $<;

$(SRCDIR)/lex.yy.c:
	$(LEX) $(SRCDIR)/$(LEXFILE)
	@mv lex.yy.c $(SRCDIR)/

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<"; $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<;
	
# DUMMY ENTRIES
clean:
	@echo "Cleaning..."
	@echo "$(RM) -rf $(BUILDDIR) $(TARGET)"; $(RM) -rf $(BUILDDIR) $(TARGET)

.PHONY: clean

