#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/random.h>

#include "macros.h"

void add_entropy(char data[8])
{

	// Allocate ioctl data and buffer struct
	struct {
		struct rand_pool_info info;
		char buffer[POOL_RADIUS];
	} output;
	int rnd = open(DEV_RANDOM, O_WRONLY);

	output.info.entropy_count = POOL_RADIUS << 3;
	output.info.buf_size = POOL_RADIUS;
	memcpy(&(output.buffer), data, POOL_RADIUS);

	if (ioctl(rnd, RNDADDENTROPY, &output) == -1)
		printf("%s\n", "ioctl(RNDADDENTROPY) failed!");

	close(rnd);
}
