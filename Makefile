########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++20 -Wall -g -O0 -I./src

INPUTFOLDER = input
INPUTFILE = input3.rs

# Makefile settings - Can be customized.
APPNAME = RustC
EXT = .cpp
SRCDIR = src
OBJDIR = obj
DEPDIR = dep

############## Do not change anything from here downwards! #############
SRC = $(shell find $(SRCDIR) -name '*$(EXT)') # Find all .cpp files recursively
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)  # Replace .cpp with .o
DEP = $(SRC:$(SRCDIR)/%$(EXT)=$(DEPDIR)/ %.d)  # Replace .cpp with .d

# UNIX-based OS variables & settings
RM = rm -f        # Use -f to avoid errors when file does not exist
DELOBJ = $(OBJ)
DELDEP = $(DEP)

# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)
WDELDEP = $(SRC:$(SRCDIR)/%$(EXT)=$(DEPDIR)\\%.d)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Create the obj and dep directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

# Creates the directory for the .o and .d files if they don't exist
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	@mkdir -p $(dir $@)    # Ensure directory exists
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT)
	@mkdir -p $(dir $@)    # Ensure directory exists
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Rule to compile and run the app
.PHONY: run
run: $(APPNAME)
	./$(APPNAME) $(INPUTFOLDER)/$(INPUTFILE)

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DELDEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DELDEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(WDELDEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(WDELDEP)
