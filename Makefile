TARGET=functor
CFLAGS = -Wall -Wextra -Weffc++ -g -std=c++0x

all:$(TARGET)

functor:functor.cpp functor.h
	g++ $(CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET) *.o
