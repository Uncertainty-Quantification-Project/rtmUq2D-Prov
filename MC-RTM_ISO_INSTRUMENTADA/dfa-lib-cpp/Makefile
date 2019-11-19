######################################################################
# Environment variables

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/lib
MACOS 		   ?= 0
target     := lib/libdfanalyzer.so
targettest     := example.o

DFANALYZER_DIR 	= .
test_CXXFLAGS += -w -I$(DFANALYZER_DIR)/include  
test_LDFLAGS  += -lcurl -L$(DFANALYZER_DIR)/lib -ldfanalyzer


###############################################################################
# File management.  This is where the source, header, and object files are
# defined

#
# source files
srcfiles :=  $(wildcard src/*.cpp)

testfiles :=  $(wildcard tests/*.cpp)

CXXFLAGS := -I./include -g -fPIC -std=c++11
ifeq (${MACOS}, 1) 
	CXXFLAGS += -w -std=c++11
endif

LDFLAGS  := -lcurl -shared -fPIC

CXX      := icpc

#
# object files
objects		:= $(patsubst %.cpp, %.o, $(srcfiles))
objectstest		:= $(patsubst %.cpp, %.o, $(testfiles))
###############################################################################


.PHONY: dust clean distclean

###############################################################################
# Target:
#


if($(PREFIX)x == x)

all: clean $(target)

# Production rules:  how to make the target - depends on library configuration
$(target): $(objects)
	@echo "Linking "$@"..."
	@$(CXX) $(CXXFLAGS) $(objects) -o $@ $(LDFLAGS)

all_test: clean_test $(targettest)

# Production rules:  how to make the target - depends on library configuration
$(targettest): $(objectstest)
	@echo "Linking "$@"..."
	@echo "@$(CXX) $(CXXFLAGS) $(objectstest) $(test_CXXFLAGS) -o $@ $(test_LDFLAGS)"

	@$(CXX) $(CXXFLAGS) $(objectstest) $(test_CXXFLAGS) -o $@ $(test_LDFLAGS)



# Useful rules.
dust:
	@echo "Deleting old objects files"
	@rm -rf out*.m job_output.txt output.txt* *.gmv.* *.plt.* out*.xdr* out*.xda* PI* complete .depend .libs

clean: dust
	@rm -f $(objects) $(target)

clean_test:
	@rm -f $(objectstest) $(targettest)

clobber: clean 
	@rm -f $(target)

distclean: clean
	@rm -rf *.o .libs .depend

echo:
	@echo srcfiles = $(srcfiles)
	@echo objects = $(objects)
	@echo target = $(target)
	@echo testfiles = $(testfiles)
	@echo objectstest = $(objectstest)
	@echo targettest = $(targettest)


%.o: %.cpp $(DEPS)
	@echo "Compiling "$<"..."
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

###############################################################################

