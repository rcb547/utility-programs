SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o
.DEFAULT_GOAL := allclean

executable =  $(exedir)/mvglobal.exe

includes += -I$(srcdir)
includes += -I$(cpputilssrc)

#cxxflags  += -DUSEGLOBALSTACKTRACE
cxxflags   += 
libs       = 

objects += $(cpputilssrc)/general_utils.o
objects += $(cpputilssrc)/file_utils.o
objects += $(srcdir)/mvglobal.o

%.o : %.cpp
	@echo ' '
	@echo 'Compiling ' $<
	$(cxx) -c $(includes) $(cxxflags) $< -o $@

compile: $(objects)

link: $(objects)
	mkdir -p $(exedir)
	@echo ' '
	@echo Linking
	$(cxx) $(objects) $(libs) -o $(executable)
	chmod g+rx $(executable)
	chmod o+rx $(executable)

clean:
	@echo ' '
	@echo Cleaning
	rm -f $(objects)
	rm -f $(executable)

all: compile link
allclean: clean compile link

