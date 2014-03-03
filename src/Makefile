CC := gcc
CFLAGS := -c -Wall
INCLUDES := -I../include
SOURCES := nmem.c nproc.c nterm.c nprog.c
OBJECTS := $(SOURCES:.c=.o)
NEANDERLIB := ../lib/libneanderc.a
OUT := ../bin/neanderc


.SUFFICES: .c

all: $(NEANDERLIB)

$(NEANDERLIB): $(OBJECTS) neanderclib neanderc

neanderc: neander.c
	@echo "Generating ../bin/neanderc"
	$(CC) $(INCLUDES) neander.c  $(NEANDERLIB) -o $(OUT)

neanderclib:
	@echo "Generating ../lib/libneanderc.a"
	ar rcs $(NEANDERLIB) $(OBJECTS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(NEANDERLIB) $(OUT)

