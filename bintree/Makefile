EXEC = main
LOG = $(EXEC).log

SOURCES = $(filter-out src/$(EXEC).cpp, $(wildcard src/*.cpp))
HEADERS = $(wildcard headers/*.hpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

CXX = g++
CXXFLAGS = -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic -I build -I header

$(EXEC): $(OBJECTS) $(HEADERS) build/$(EXEC).o
	rm $(LOG) &> /dev/null
	$(CXX) $(CXXFLAGS) $(OBJECTS) build/$(EXEC).o -o $(EXEC) &>> $(LOG)

build/$(EXEC).o: src/$(EXEC).cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ &>> $(LOG)

$(OBJECTS): build/%.o: src/%.cpp header/%.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ &>> $(LOG)

clean:
	rm $(LOG) &> /dev/null
	rm build/* &> /dev/null
	rm $(EXEC) &> /dev/null
