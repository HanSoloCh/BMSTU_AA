CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion
TESTFLAGS = --coverage -lcheck -lm -lsubunit
INC= -I inc

SRC = $(wildcard src/*.c)
TESTSRC = $(wildcard unit_tests/*.c)
HEADERS = $(wildcard inc/*.h)

MAIN = src/main.c

READY_DIR = ready

OBJDIR = out
OBJ = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC))
TESTOBJ = $(patsubst unit_tests/%.c, $(OBJDIR)/%.o, $(TESTSRC))

MAIN_TARGET = app.exe 
DEBUG_TARGET = debug.exe
TEST_TARGET = test.exe

.PHONY: build
build: $(MAIN_TARGET)

.PHONY: release
release: CFLAGS += -O3 -lm
release: $(MAIN_TARGET)

.PHONY: debug
debug: CFLAGS += -g3 -O0 -lm
debug: $(MAIN_TARGET)
	mv $^ $(DEBUG_TARGET)
	
.PHONY: clean
clean:
	rm -rf *.exe *.gcov *.gcda $(OBJDIR)
	
.PHONY: test
test: CFLAGS += -g -O0 --coverage -DTEST
test: $(TEST_TARGET)
	@./$(TEST_TARGET)
	@./coverage.sh

$(MAIN_TARGET): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	
$(TEST_TARGET): $(OBJDIR) $(OBJ) $(TESTOBJ)
	$(CC) $(CFLAGS) $(OBJ) $(TESTOBJ) -o $@ $(TESTFLAGS)

$(OBJDIR):
	@mkdir -p out
	
$(OBJDIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(INC) -c $< -o $@ $(CFLAGS) 

$(OBJDIR)/%.o: unit_tests/%.c $(HEADERS)
	$(CC) $(INC) -c $< -o $@ $(CFLAGS) $(TESTFLAGS)
	
	
$(READY_DIR)/stud-unit-test-report-prev.json:
	

$(READY_DIR)/stud-unit-test-report.json: $(READY_DIR)
	cp cov/stud-unit-test-report-prev.json $@

$(READY_DIR)/app-cli-debug: debug $(READY_DIR)
	mv $(DEBUG_TARGET) $@

$(READY_DIR)/report.pdf: $(READY_DIR)
	cp doc/report.pdf ready/report.pdf

$(READY_DIR):
	@mkdir -p ./ready

	
	


