VERSION=0.1

DEBUG= -g #-D_DEBUG #-fprofile-arcs -ftest-coverage # -pg -g
CFLAGS+=-O2 -DVERSION=\"${VERSION}\" $(DEBUG)
LDFLAGS+=$(DEBUG) -lm

OBJS=error.o kernel.o main.o math.o 

all: rng-sandmand

rng-sandmand: $(OBJS)
	$(CC) -lrt -Wall -W $(OBJS) $(LDFLAGS) -o rng-sandmand

install: rng-sandmand
	cp rng-sandmand /usr/local/sbin

clean:
	rm -f $(OBJS) rng-sandmand core *.da *.gcov *.bb*

package: clean
	mkdir rng-sandmand-$(VERSION)
	cp *.c* *.h Makefile Changes readme.txt license.txt rng-sandmand-$(VERSION)
	tar czf rng-sandmand-$(VERSION).tgz rng-sandmand-$(VERSION)
	rm -rf rng-sandmand-$(VERSION)
