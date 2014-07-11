CC=g++
SRC=main.cc parser.cc map.cc cell.cc colors.cc
CFLAGS=-Werror -Wall -std=c++11
OBJ=$(SRC:.cc=.o)
LDFLAGS=
BIN=paramaze

all:
	$(CC) $$(pkg-config --cflags --libs QtCore QtGui) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(SRC)

gui:
	$(CC) $$(pkg-config --cflags --libs QtCore QtGui) -o interface interface.cc colors.cc


