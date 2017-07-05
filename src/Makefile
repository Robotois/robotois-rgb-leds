CC=g++

COMPILE_FLAGS = -g -std=c++11 -Wall -c
LINKER_FLAGS = -g
LIBS = -l bcm2835 -l rt

OBJECTS = \
	test.o \
	RGBModule.o \
	# AccurateTiming.o \

#OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: rgb.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS) $(LIBS)

main.o: test.cpp
	$(CC) $(COMPILE_FLAGS) test.cpp
rgb.o: RGBModule.cpp RGBModule.h
	$(CC) $(COMPILE_FLAGS) RGBModule.cpp
# timer.o: Libraries/Timer/AccurateTiming.cpp Libraries/Timer/AccurateTiming.h
# 	$(CC) $(COMPILE_FLAGS) Libraries/Timer/AccurateTiming.cpp

clean:
	$(RM) $(OBJECTS) runner
