CXX      ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pthread -I src

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

.PHONY: all clean test test-parallel test-sequential test-compare

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

test: $(TARGET)
	./$(TARGET) tests/parallel_threads.monkey

test-parallel: $(TARGET)
	./$(TARGET) tests/parallel_threads.monkey

test-sequential: $(TARGET)
	./$(TARGET) tests/sequential_fib.monkey

# Same fib(24)+fib(24) work; compare wall-clock (real) — parallel should be ~faster on multi-core.
test-compare: $(TARGET)
	@echo "=== parallel (spawn + join) ==="
	@/usr/bin/time -p ./$(TARGET) tests/parallel_threads.monkey
	@echo ""
	@echo "=== sequential (let t1 = fib(24); let t2 = fib(24);) ==="
	@/usr/bin/time -p ./$(TARGET) tests/sequential_fib.monkey

clean:
	rm -f $(TARGET)
