
FILES = setconsole

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
CFLAGS = -O2 -fomit-frame-pointer -Wall 


all: $(FILES)

clean:
	rm -f $(FILES) *~ core
