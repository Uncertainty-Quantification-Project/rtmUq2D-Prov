DFANALYZER_DIR 	?= /home/liliane/Downloads/dataflow_analyzer-master/library/dfa-lib-cpp
LDFLAGS  += -lcurl -L$(DFANALYZER_DIR)/lib -ldfanalyzer

CC=g++
CFLAGS=-I.

hellomake: dfanalyzer_test.o dfanalyzer_test.o
     $(CC) -o dfanalyzer_test dfanalyzer_test.cpp