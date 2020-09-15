EXEC    = cryper

CFLAGS  = -c -Wall -Werror -O3
DBCFLAGS  = -c -g -Wall -Werror -lgcov --coverage 
LDFLAGS =
DBLDFLAGS = -lgcov --coverage
CC= $(PREP) gcc
CSOURCES = $(wildcard src/*.c) $(wildcard pieces/*.c)

VPATH = src

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I src/include

LIBS = 

all: $(CSOURCES) $(EXEC) 

debug:
	@$(MAKE) CFLAGS="$(DBCFLAGS)" LDFLAGS="$(DBLDFLAGS)"


$(EXEC): $(COBJECTS)
	$(CC) $(COBJECTS) $(LDFLAGS) -o $@
	rm -rf *.o
	@echo ''
	@echo 'Finished building target $@'

%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
		rm -rf src/*.o
		rm -rf $(EXEC)


