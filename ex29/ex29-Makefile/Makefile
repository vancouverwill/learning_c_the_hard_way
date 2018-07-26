CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

# generate space seperated string of files which match wildcard, i.e. 'src/lib.c main.c'
SOURCES=$(wildcard src/**/*.c src/*.c)
# create a list of objects by swapping .c to .o in the SOURCES var
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libex29-format-case.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests

debug:
	echo "TARGET:" $(TARGET)
	echo "SOURCES:" $(SOURCES)
	echo "OBJECTS:" $(OBJECTS)
	echo "TEST_SRC:" $(TEST_SRC)
	echo "TESTS:" $(TESTS)
	echo "TARGET:" $(TARGET)
	echo "SO_TARGET:" $(SO_TARGET)

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

# create make command on the fly with the name of target directory
$(TARGET): CFLAGS += -fPIC
# on the target difrectory build objects
$(TARGET): build $(OBJECTS)
# create the library archive file with the name target from the objects. here $@ is taking the name of the command run in this case TARGET		
	ar rcs $@ $(OBJECTS)
# build the library with the name of TARGET				
	ranlib $@

RUN_SO_TARGET:
	 make $(SO_TARGET)

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log 
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true

