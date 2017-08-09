
PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)

# location of the Boost Python include files and library

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

# compile mesh classes
TARGET = main

main.so: *.o
	g++ -shared -Wl,--export-dynamic *.o -L$(BOOST_LIB) -lboost_python -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o ../game_controller/main.so `pkg-config --libs opencv` `pkg-config --cflags opencv`

*.o: ./src/*.cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c ./src/*.cpp

