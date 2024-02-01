CXX := g++
OUTPUT := sfmlgame

SFML_DIR := /Users/simone.simonella/Desktop/github/SFML

CXX_FLAGS := -O3 -std=c++17
INCLUDES := -I./jni -I$(SFML_DIR)/include
LDFLAGS := -O3 -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_FILES := $(wildcard jni/*.cpp)
OBJ_FILES := $(patsubst jni/%.cpp,bin/%.o,$(SRC_FILES))

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

bin/%.o: jni/%.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $< -c -o $@

clean:
	rm -f $(OBJ_FILES)
	rm -f ./bin/$(OUTPUT)

run: $(OUTPUT)
	cd bin && ./$(OUTPUT) && cd ..