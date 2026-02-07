TARGET = codi

all: $(TARGET)

$(TARGET): main.cpp
	g++ main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
