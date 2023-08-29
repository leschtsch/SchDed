CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

SRC_DIR = ./src
OBJ_DIR = ./obj
INCL_DIR = ./src/include

all: main.exe

main.exe: $(OBJ_DIR)/main.o $(OBJ_DIR)/io.o $(OBJ_DIR)/argparse.o $(OBJ_DIR)/solve.o $(OBJ_DIR)/tests.o $(OBJ_DIR)/common.o
	g++ $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/io.o $(OBJ_DIR)/argparse.o $(OBJ_DIR)/solve.o $(OBJ_DIR)/tests.o $(OBJ_DIR)/common.o -o main.exe

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCL_DIR)/tests.h $(INCL_DIR)/solve.h $(INCL_DIR)/io.h $(INCL_DIR)/common.h  $(INCL_DIR)/config.h
	g++ $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/io.o: $(SRC_DIR)/io.cpp $(INCL_DIR)/io.h $(INCL_DIR)/common.h
	g++ $(CFLAGS) -c $(SRC_DIR)/io.cpp -o $(OBJ_DIR)/io.o

$(OBJ_DIR)/argparse.o: $(SRC_DIR)/argparse.cpp $(INCL_DIR)/argparse.h $(INCL_DIR)/common.h $(INCL_DIR)/config.h
	g++ $(CFLAGS) -c $(SRC_DIR)/argparse.cpp -o $(OBJ_DIR)/argparse.o

$(OBJ_DIR)/solve.o: $(SRC_DIR)/solve.cpp  $(INCL_DIR)/solve.h $(INCL_DIR)/common.h
	g++ $(CFLAGS) -c $(SRC_DIR)/solve.cpp -o $(OBJ_DIR)/solve.o

$(OBJ_DIR)/tests.o: $(SRC_DIR)/tests.cpp $(INCL_DIR)/tests.h $(INCL_DIR)/solve.h $(INCL_DIR)/common.h $(INCL_DIR)/config.h
	g++ $(CFLAGS) -c $(SRC_DIR)/tests.cpp -o $(OBJ_DIR)/tests.o

$(OBJ_DIR)/common.o: $(SRC_DIR)/common.cpp $(INCL_DIR)/common.h
	g++ $(CFLAGS) -c $(SRC_DIR)/common.cpp -o $(OBJ_DIR)/common.o

