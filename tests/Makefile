EXEC := run_tests
MAIN := test_lib
TESTS := test_parser
FIXTURES := arduino-serial-fixture/src/Arduino
LIBS := ../src/textparser


CC := g++
CC_ARGS := -std=c++11 -Wall -Wextra -pedantic -Wno-pmf-conversions \
  -I arduino-serial-fixture/src


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES) $(LIBS))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) $(CC_ARGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CC_ARGS) -o $@ -c $<

%.o: %.cc
	$(CC) $(CC_ARGS) -o $@ -c $<

check: all
	valgrind --error-exitcode=1 --track-origins=yes ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
