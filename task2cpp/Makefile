CXX = g++
CXXFLAGS = -std=c++17 --coverage -g -Wall
LIBS = -lgtest -lgtest_main -pthread
TARGET = testARRAY
COVERAGE_DIR = coverage_report

all: coverage

test: $(TARGET)
	./$(TARGET)

$(TARGET): array.cpp arrayTEST.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) array.cpp arrayTEST.cpp $(LIBS)

# Исправленная цель coverage - убраны конфликтующие флаги
coverage: test
	rm -rf $(COVERAGE_DIR)
	gcovr -r . --html-nested $(COVERAGE_DIR)
	@echo "Coverage report: $(COVERAGE_DIR)/index.html"

# Альтернатива с подробным отчетом
coverage_detailed: test
	rm -rf $(COVERAGE_DIR)
	gcovr -r . --html $(COVERAGE_DIR)/index.html --html-details
	@echo "Detailed coverage report: $(COVERAGE_DIR)/index.html"

# Простой HTML отчет
coverage_simple: test
	rm -rf $(COVERAGE_DIR)
	gcovr -r . --html $(COVERAGE_DIR)/index.html
	@echo "Simple coverage report: $(COVERAGE_DIR)/index.html"

# Консольный отчет
coverage_text: test
	@echo "=== Text Coverage Report ==="
	gcovr -r .

clean:
	rm -f $(TARGET) *.gcno *.gcda *.gcov
	rm -rf $(COVERAGE_DIR)

.PHONY: all test coverage coverage_detailed coverage_simple coverage_text clean
