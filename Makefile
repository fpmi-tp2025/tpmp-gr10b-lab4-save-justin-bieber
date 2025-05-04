
CXX = g++
CXXFLAGS = -std=c++20 -I./src -Wall
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/salon

SOURCES := $(shell find $(SRCDIR) -name "*.cpp") main.cpp
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -lsqlite3 -o $@

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: clean
