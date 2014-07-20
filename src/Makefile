CC=g++
SRC=main.cc parser.cc map.cc cell.cc colors.cc
CFLAGS=-Werror -Wall -std=c++11 -g
OBJ=$(SRC:.cc=.o)
LDFLAGS=
BIN=../paramaze

all:
	$(CC) $$(pkg-config --cflags --libs QtCore QtGui) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(SRC)

gui:
	$(CC) $$(pkg-config --cflags --libs QtCore QtGui) -o interface interface.cc colors.cc

generator:
	$(CC) $$(pkg-config --cflags --libs QtCore QtGui) $(CFLAGS) $(LDFLAGS) -o gene mainmg.cc mazegenerator.cc cell.cc colors.cc map.cc
