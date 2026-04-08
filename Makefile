CXX := c++
CXXFLAGS := -std=c++26 -O3 -Wall -Wextra -Wpedantic -Wconversion -Isrc/include -MMD -MP
LDFLAGS := 

TARGET := build/baa
SRCS := $(wildcard src/*.cc)
OBJS := $(patsubst src/%.cc, build/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all build run clean test

all: build

build: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.cc
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	@-./$(TARGET)

test: build
	@-./$(TARGET) --test

clean:
	@rm -rf build

-include $(DEPS)