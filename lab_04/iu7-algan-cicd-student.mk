CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra -Wvla -Wfloat-equal -Wfloat-conversion
INC = -I inc

SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard inc/*.h)

MAIN = src/main.cpp

READY_DIR = ready

OBJDIR = out
OBJ = $(patsubst src/%.cpp, $(OBJDIR)/%.o, $(SRC))
TESTOBJ = $(patsubst unit_tests/%.c, $(OBJDICC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra -Wvla -Wfloat-equal -Wfloat-conversion
INC = -I inc

SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard inc/*.h)

MAIN = src/main.cpp

READY_DIR = ready

OBJDIR = out
OBJ = $(patsubst src/%.cpp, $(OBJDIR)/%.o, $(SRC))
TESTOBJ = $(patsubst unit_tests/%.c, $(OBJDIR)/%.o, $(TESTSRC))

MAIN_TARGET = app.exe 
DEBUG_TARGET = debug.exe


.PHONY: release
release: CFLAGS += -O3
release: $(MAIN_TARGET)

.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: $(MAIN_TARGET)
	mv $^ $(DEBUG_TARGET)
	
.PHONY: clean
clean:
	rm -rf *.exe *.txt *.db *.gcov *.gcda $(OBJDIR)
	

$(MAIN_TARGET): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lsqlite3 -lstdc++
	
$(TEST_TARGET): $(OBJDIR) $(OBJ) $(TESTOBJ)
	$(CC) $(CFLAGS) $(OBJ) $(TESTOBJ) -o $@ $(TESTFLAGS)

$(OBJDIR):
	@mkdir -p out
	
$(OBJDIR)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(INC) -c $< -o $@ $(CFLAGS) 

	
# pipelines
$(READY_DIR)/stud-unit-test-report-prev.json:
	

$(READY_DIR)/stud-unit-test-report.json: $(READY_DIR)
	cp cov/stud-unit-test-report-prev.json $@

$(READY_DIR)/app-cli-debug: debug $(READY_DIR)
	mv $(DEBUG_TARGET) $@

$(READY_DIR)/report.pdf: $(READY_DIR)
	cp report/report.pdf ready/report.pdf

$(READY_DIR):
	@mkdir -p ./ready
	
	
R)/%.o, $(TESTSRC))

MAIN_TARGET = app.exe 
DEBUG_TARGET = debug.exe


.PHONY: release
release: CFLAGS += -O3
release: $(MAIN_TARGET)

.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: $(MAIN_TARGET)
	mv $^ $(DEBUG_TARGET)
	
.PHONY: clean
clean:
	rm -rf *.exe *.gcov *.gcda $(OBJDIR)
	

$(MAIN_TARGET): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lcurl -lstdc++
	
$(TEST_TARGET): $(OBJDIR) $(OBJ) $(TESTOBJ)
	$(CC) $(CFLAGS) $(OBJ) $(TESTOBJ) -o $@ $(TESTFLAGS)

$(OBJDIR):
	@mkdir -p out
	
$(OBJDIR)/%.o: src/%.cpp $(HEADERS)
	$(CC) $(INC) -c $< -o $@ $(CFLAGS) 

	
# pipelines
$(READY_DIR)/stud-unit-test-report-prev.json:
	

$(READY_DIR)/stud-unit-test-report.json: $(READY_DIR)
	cp cov/stud-unit-test-report-prev.json $@

$(READY_DIR)/app-cli-debug: debug $(READY_DIR)
	mv $(DEBUG_TARGET) $@

$(READY_DIR)/report.pdf: $(READY_DIR)
	cp doc/report.pdf ready/report.pdf

$(READY_DIR):
	@mkdir -p ./ready
	
	
