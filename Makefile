#name of the output executable
TARGET = PMS

#compiler to use
CC = g++

CFLAGS = -Wall -Wextra -pedantic -std=c++17

OBJ = PMS.o

#building the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

#compiling .cpp files into .o files  
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

#clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET) 
