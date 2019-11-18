EXEC = main

SOURCES = $(filter-out src/$(EXEC).cpp, $(wildcard src/*.cpp))
HEADERS = $(wildcard headers/*.hpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

CXX = g++
CXXFLAGS = -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic -I build -I header

$(EXEC): $(OBJECTS) $(HEADERS) build/$(EXEC).o
	$(CXX) $(CXXFLAGS) $(OBJECTS) build/$(EXEC).o -o $(EXEC)

build/$(EXEC).o: src/$(EXEC).cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJECTS): build/%.o: src/%.cpp header/%.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm build/*
	rm main
