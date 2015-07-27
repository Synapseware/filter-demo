
TARGET = filter

all:
	g++ $(TARGET).cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
