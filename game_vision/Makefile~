PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)

# location of the Boost Python include files and library

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

Object_libs = ./computer_vision_To_python_libs
Shared_lib = ./Debug

# compile mesh classes
TARGET = main

opencv.so: *.o
	cd $(Object_libs) && g++ -shared -Wl,--export-dynamic *.o -L$(BOOST_LIB) -lboost_python -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o  ../$(Shared_lib)/opencv.so `pkg-config --libs opencv` `pkg-config --cflags opencv`

*.o: ./src/*.cpp
	rm -rf $(Object_libs) && mkdir $(Object_libs) && cd $(Object_libs) && g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c ../src/*.cpp  

clean:
	rm -f $(Object_libs)/*.o ./$(Shared_lib)/opencv.so


