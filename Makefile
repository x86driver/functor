TARGET=functor
CFLAGS = -Wall -Wextra -Weffc++ -g

all:$(TARGET)

functor:functor.cpp functor.h
	g++ $(CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET) *.o
