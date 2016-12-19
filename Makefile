CC=gcc
CFLAGS=-Wall
LIBS=-lm
DEPS = pcb.h mydefs.h aperture.h primitive.h mystrings.h enc_key.h \
xy_extents.h key_array.h apt_dict.h pad_array.h track_array.h \
gerber2file.h arc_array.h via_array.h fill_array.h str_array.h \
ps2file.h ps_strings.h
OBJ = mystrings.o primitive.o pcbread.o enc_key.o \
xy_extents.o key_array.o apt_dict.o pad_array.o track_array.o \
gerber2file.o arc_array.o via_array.o fill_array.o str_array.o \
ps2file.o ps_strings.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

pcbread: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm *.o
	
.PHONY: test

test:
	time ./pcbread -i TEST.PCB -o TEST.DAT 2> out.txt
