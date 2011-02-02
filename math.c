
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <linux/random.h>
#include "macros.h"

/* Algorithms - random number generation */

long ts_nanos(void){
    struct timespec ts;

    SUCCESS(clock_gettime(CLOCK_REALTIME, &ts));
    return ts.tv_nsec;
}

int count_bits_set(long v){
    int c;

    for (c = 0; v; c++) {
        v &= v - 1;
    }
    return c;
}

int random_sleep_bit(int millis){

    long start = ts_nanos();

    usleep(millis);

    long xor = start ^ ts_nanos();
    int set = count_bits_set(xor);

    return set & 1;
}

void generate_random(int length, int sleep_i)
{

	unsigned char byte, offset = 0;
	unsigned long lastflush = 0;

	for (;; ) {
		byte <<= 1;
		if (random_sleep_bit(sleep_i)) {
			byte |= 1;
		}

		if (++offset == 8) {
			offset = 0;

			if (++lastflush == POOL_RADIUS) {
				lastflush = 0;

				char buf[8];
				sprintf(buf, "%d", byte);

				// printf("%s\n", buf);
				add_entropy(buf);
			}
		}
	}
}
