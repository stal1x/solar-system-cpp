##############################################################################
#
#  Sample Makefile for C++ OpenGL applications
#    Works for single and multiple file programs.
#    Works on several different versions of Unix.
#    written by Robert Duvall
#
##############################################################################


##############################################################################
# Application specific variables --- change these to customize your compile
# EXEC      name of the executable file
# SRC_FILES space separated list of all source code files that must be linked
#           to create the executable (i.e., not template files)
# INC_FILES space separated list of header and template files --- add to this
#	    list only if you have files that do not have a corresponding .cpp
#   	    files listed in SRC_FILES
# ARCH	    system on which you are compiling
#           Possible values: CPS, ACPUB, LINUX, CYGWIN, SGI, OSX
# COURSE    current course you are in
##############################################################################
EXEC   	  = demo
SRC_FILES = main.cpp
INC_FILES = $(SRC_FILES:%.cpp=%.h)
ARCH	  = OSX
COURSE	  = cps124


##############################################################################
# Where to find course related header files (and their libraries) 
# --- typically only need to set this at the start of the semester
# SYSINC_DIR space separated list of system directories where to find headers
# SYSLIB_DIR space separated list of system directories where to find libraries
# SYSLIB_LIB space separated list of system libraries needed
# SYSLIB_RUN space separated list of system libraries needed at runtime
# COURSE_DIR space separated list of course directories where to find files
# COURSE_LIB space separated list of course libraries needed
# CCC_DIR    directory where to find the compiler
##############################################################################

# Where to find OpenGL headers
SYSINC_CPS_DIR 	   = /usr/local
SYSINC_ACPUB_DIR   = /afs/acpub/project/cps/pkgs/opengl
SYSINC_LINUX_DIR   = /usr/local /usr/dt
SYSINC_CYGWIN_DIR  = /usr
SYSINC_SGI_DIR     = /usr/local
SYSINC_OSX_DIR     = 
SYSINC_DIR         = $(SYSINC_$(ARCH)_DIR:%=-I%/include)

# Where to find OpenGL libraries
SYSLIB_CPS_DIR 	   = $(SYSINC_CPS_DIR:%=%/lib)
SYSLIB_ACPUB_DIR   = /usr/openwin/lib $(SYSINC_ACPUB_DIR:%=%/lib)
SYSLIB_LINUX_DIR   = $(SYSINC_LINUX_DIR:%=%/lib)
SYSLIB_CYGWIN_DIR  = /usr/w32api/lib
SYSLIB_SGI_DIR     = /usr/freeware/lib32
SYSLIB_OSX_DIR     = 
SYSLIB_DIR         = $(SYSLIB_$(ARCH)_DIR:%=-L%)

# Where to find OpenGL libraries at runtime
SYSLIB_CPS_RUN 	   = $(SYSLIB_CPS_DIR)
SYSLIB_ACPUB_RUN   = $(SYSLIB_ACPUB_DIR)
SYSLIB_LINUX_RUN   = 
SYSLIB_CYGWIN_RUN  = 
SYSLIB_SGI_RUN     =
SYSLIB_OSX_RUN	   = $(SYSLIB_SGI_DIR)
SYSLIB_RUN         = $(SYSLIB_$(ARCH)_RUN:%=-R%)
# What system libraries to link to
SYSLIB_CPS_LIB 	   = -lglut -lGLU -lGL -lXi -lXext -lX11
SYSLIB_ACPUB_LIB   = $(SYSLIB_CPS_LIB) -lXmu -lm
SYSLIB_LINUX_LIB   = $(SYSLIB_CPS_LIB)
SYSLIB_CYGWIN_LIB  = -lglui -lglut32 -lglu32 -lopengl32
SYSLIB_SGI_LIB     = $(SYSLIB_ACPUB_LIB)
SYSLIB_OSX_LIB     = -framework OpenGL -framework GLUT -framework AGL
SYSLIB_LIB	   = $(SYSLIB_$(ARCH)_LIB)

# Where to find course specific libraries (and what they are)
COURSE_CPS_DIR 	   = /usr/project/courses/$(COURSE)
COURSE_ACPUB_DIR   = /afs/acpub/project/cps/courses/$(COURSE)
COURSE_LINUX_DIR   = /usr/local/$(COURSE)
COURSE_CYGWIN_DIR  = 
COURSE_SGI_DIR     = 
COURSE_OSX_DIR     = 
COURSE_DIR         = $(COURSE_$(ARCH)_DIR)
# What course specific libraries to link to
COURSE_LIB   	   = 

CCC_CPS_DIR        = 
CCC_ACPUB_DIR      = 
CCC_LINUX_DIR      = 
CCC_CYGWIN_DIR     = 
CCC_SGI_DIR        = /usr/local/bin/
CCC_OSX_DIR        = 
COMPILER           = $(CCC_$(ARCH)_DIR)g++

DEBUG_CPS	   = -g
DEBUG_ACPUB        = $(DEBUG_CPS)
DEBUG_LINUX        = $(DEBUG_CPS)
DEBUG_CYGWIN       = $(DEBUG_CPS)
DEBUG_SGI          = $(DEBUG_CPS)
DEBUG_OSX          = $(DEBUG_CPS)
DEBUG              = $(DEBUG_$(ARCH))

COMPILE_FLAGS_CPS    = -Wall
COMPILE_FLAGS_ACPUB  = $(COMPILE_FLAGS_CPS) -Wno-unknown-pragmas
COMPILE_FLAGS_LINUX  = $(COMPILE_FLAGS_CPS)
COMPILE_FLAGS_CYGWIN = $(COMPILE_FLAGS_CPS)
COMPILE_FLAGS_SGI    = $(COMPILE_FLAGS_CPS)
COMPILE_FLAGS_OSX    = $(COMPILE_FLAGS_CPS)
COMPILE_FLAGS 	     = $(COMPILE_FLAGS_$(ARCH))

LINK_FLAGS_CPS     = 
LINK_FLAGS_ACPUB   = 
LINK_FLAGS_LINUX   = 
LINK_FLAGS_CYGWIN  = 
LINK_FLAGS_SGI	   = 
LINK_FLAGS_OSX	   = -prebind -flat_namespace
LINK_FLAGS         = $(LINK_FLAGS_$(ARCH))

EXEC_SUFFIX_CPS    = 
EXEC_SUFFIX_ACPUB  = 
EXEC_SUFFIX_LINUX  = 
EXEC_SUFFIX_CYGWIN = .exe 
EXEC_SUFFIX_OSX    = 
EXEC_SUFFIX_SGI    = 
EXEC_SUFFIX	   = $(EXEC_SUFFIX_$(ARCH))


##############################################################################
# Compiler specifications
# These match the variable names given in /usr/share/lib/make/make.rules
# so that make's generic rules work to compile our files.
# gmake prefers CXX and CXXFLAGS for c++ programs
##############################################################################

# Which compiler should be used
CCC     	= $(COMPILER)
CXX		= $(CCC)

# What flags should be passed to the compiler
DEBUG_LEVEL	= $(DEBUG)
CCFLAGS		= $(VERBOSE) $(DEBUG_LEVEL) $(COMPILE_FLAGS)
CXXFLAGS	= $(CCFLAGS)

# What flags should be passed to the C pre-processor
#   In other words, where should we look for files to include - note,
#   you should never need to include compiler specific directories here
#   because each compiler already knows where to look for its system
#   files (unless you want to override the defaults)
CPPFLAGS  	= -I. $(SYSINC_DIR) $(COURSE_DIR:%=-I%/include)

# What flags should be passed to the linker
#   In other words, where should we look for libraries to link with - note,
#   you should never need to include compiler specific directories here
#   because each compiler already knows where to look for its system files.
LDFLAGS   	= $(LINK_FLAGS) -L. $(SYSLIB_DIR) $(COURSE_DIR:%=-L%/lib)

# What libraries should be linked with
LDLIBS    	= $(COURSE_LIB) $(SYSLIB_LIB)

# All source files have associated object files
OFILES		= $(SRC_FILES:%.cpp=%.o)


###########################################################################
# Additional rules make should know about in order to compile our files
###########################################################################
# all is the default rule
all	: $(EXEC)

# exec depends on the object files
$(EXEC) : $(OFILES)
	$(LINK.cc) -o $(EXEC) $(OFILES) $(LDLIBS)

# depend figures out header file dependecies,
# use each time you add a new header file
depend:
	makedepend -- $(CXXFLAGS) -- -Y $(SRC_FILES)

# clean up after you're done
clean	:
	$(RM) *.o $(EXEC)$(EXEC_SUFFIX) core


# compile a single .cpp file into an object (.o) file
# for later linking with other .o files
.cpp.o:
	$(COMPILE.cc) $<

# compile a single .cpp file into an executable file
.cpp:
	$(LINK.cc) $< -o $@ $(LDLIBS)


# DO NOT DELETE THIS LINE -- make depend depends on it.

main.o: cglx.h scene.h
