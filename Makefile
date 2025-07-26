CXX = clang++
CXXFLAGS = -std=c++17 -Wall

# Raylib-specific flags
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
INCLUDES = -I/opt/homebrew/include

TARGET = game
SRC = game.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
