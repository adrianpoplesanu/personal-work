CXX      ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -I src

SRCS := \
	src/main.cpp \
	src/token.cpp \
	src/lexer.cpp \
	src/parser.cpp \
	src/object.cpp \
	src/environment.cpp \
	src/builtins.cpp \
	src/evaluator.cpp

TARGET := monkeycpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET)
