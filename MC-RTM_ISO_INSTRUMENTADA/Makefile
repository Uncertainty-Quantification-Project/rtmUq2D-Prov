CC=mpiicpc
OPTFLAGS=-O3 -qopenmp -xHost -inline-forceinline -unroll-aggressive -qopt-assume-safe-padding
EXEC=mpi-rtm_iso2d
OBJ=mpi_rtm_iso2d.o rtm_iso2d.o pi_file.o generic_functions.o forward_modeling.o absorbingBoundaryCondition.o stencilDFM.o backward_modeling.o image_conditions.o math_functions.o

DFANALYZER_DIR 	= ./dfa-lib-cpp
test_CXXFLAGS += -w -I$(DFANALYZER_DIR)/include  
test_LDFLAGS  += -lcurl -L$(DFANALYZER_DIR)/lib -ldfanalyzer

all: $(EXEC)

$(EXEC): $(OBJ)
	 $(CC) $(OPTFLAGS) -o $(EXEC) ./OBJECT_FILES/*.o $(test_LDFLAGS) 

%.o: ./SRC/%.c
	$(CC) $(OPTFLAGS) -c $(test_CXXFLAGS) -o $@ $(test_LDFLAGS) $<
	mv *.o ./OBJECT_FILES/

clean:
	rm -f $(EXEC) ./OBJECT_FILES/*.o

dataflow:
	$(CC) $(test_CXXFLAGS)  dataflow.c -o dataflow $(test_LDFLAGS)